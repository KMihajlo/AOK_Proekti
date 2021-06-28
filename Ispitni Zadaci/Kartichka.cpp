#include<iostream>
#include<string.h>
using namespace std;
class OutOfBoundException
{
private:
    char msg[100];
public:
    OutOfBoundException(char *msg = "")
    {
        strcpy(this->msg, msg);
    }
    void print()
    {
        cout << msg << endl;
    }
};
class Karticka{
   protected:
       char smetka[16];
       int pin;
       bool povekjePin;
   public:
    Karticka(){}
    Karticka(char* smetka,int pin){
       strcpy(this->smetka,smetka);
       this->pin=pin;
       this->povekjePin=false;
     }
     // дополниете ја класата
     virtual int tezinaProbivanje()
     {
         int tmp = pin, count = 0;
         while(tmp!=0)
         {
             tmp = tmp / 10;
             count++;
         }
         return count;
     }
     virtual ~Karticka(){}
     friend ostream &operator<<(ostream &out, Karticka &k)
     {
         out << k.smetka << ": " << k.tezinaProbivanje() << endl;
         return out;
     }
     bool getDopolnitelenPin()
     {
         return povekjePin;
     }
     char *getSmetka()
     {
         return smetka;
     }
};

//вметнете го кодот за SpecijalnaKarticka

class SpecijalnaKarticka : public Karticka
{
private:
    int *dopolnitelniPIN;
    int brojPin;
    const static int P = 4;
public:
    /*SpecijalnaKarticka()
    {
        this->dopolnitelniPIN = NULL;
        this->brojPin = 0;
    }*/
    SpecijalnaKarticka(char* smetka,int pin)
    :Karticka(smetka, pin)
    {
        this->povekjePin = true;
        this->brojPin = 0;
        this->dopolnitelniPIN = new int[brojPin];
    }
    SpecijalnaKarticka(SpecijalnaKarticka &s)
    {
        strcpy(this->smetka, s.smetka);
        this->pin = s.pin;
        this->povekjePin = s.povekjePin;
        this->brojPin = s.brojPin;
        this->dopolnitelniPIN = new int[s.brojPin];
        for(int i = 0; i < s.brojPin; i++)
        {
            this->dopolnitelniPIN[i] = s.dopolnitelniPIN[i];
        }
    }
    SpecijalnaKarticka &operator=(SpecijalnaKarticka &s)
    {
        if(this!=&s)
        {
            strcpy(this->smetka, s.smetka);
            this->pin = s.pin;
            this->povekjePin = s.povekjePin;
            this->brojPin = s.brojPin;
            delete [] dopolnitelniPIN;
            this->dopolnitelniPIN = new int[s.brojPin];
            for(int i = 0; i < s.brojPin; i++)
            {
                this->dopolnitelniPIN[i] = s.dopolnitelniPIN[i];
            }
        }
        return *this;
    }
    SpecijalnaKarticka& operator+=(int novPin)
    {
        if(this->brojPin == P)
        {
            throw OutOfBoundException("Brojot na pin kodovi ne moze da go nadmine dozvolenoto");
        }
        int *tmp = new int[brojPin+1];
        for(int i = 0; i < brojPin; i++)
        {
            tmp[i] = dopolnitelniPIN[i];
        }
        tmp[brojPin++] = novPin;
        delete [] dopolnitelniPIN;
        dopolnitelniPIN = tmp;
        return *this;
    }
    ~SpecijalnaKarticka()
    {
        delete [] dopolnitelniPIN;
    }
    int tezinaProbivanje()
    {
        return Karticka::tezinaProbivanje() + brojPin;
    }
    friend ostream &operator<<(ostream &out, SpecijalnaKarticka &s)
     {
         out << s.smetka << ": " << s.tezinaProbivanje() << endl;
         return out;
     }
};

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako kartickata ima dopolnitelni pin kodovi
        if (karticki[i]->getDopolnitelenPin()){
            this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
        }
        else this->karticki[i]=new Karticka(*karticki[i]);
      }
      this->broj=broj;
    }
    ~Banka(){
    for (int i=0;i<broj;i++) delete karticki[i];
    }

    //да се дополни класата

    static void setLIMIT(int newLimit)
    {
        LIMIT = newLimit;
    }
    void pecatiKarticki()
    {
        cout << "Vo bankata " << naziv << " moze da se probijat kartickite:" << endl;
        for(int i = 0; i < broj; i++)
        {
            if(karticki[i]->tezinaProbivanje() <= LIMIT)
            {
                cout << *karticki[i] << endl;
            }
        }
    }
    void dodadiDopolnitelenPin(char *smetka, int novPin)
    {
        for(int i = 0; i < broj; i++)
        {
            if(strcmp(karticki[i]->getSmetka(), smetka) == 0)
            {
                SpecijalnaKarticka *s = dynamic_cast<SpecijalnaKarticka *>(karticki[i]);
                if(s!=0)
                {
                    karticki[i] += novPin;
                }
            }
        }
    }
};
int Banka::LIMIT = 7;


int main(){

Karticka **niza;
int n,m,pin;
char smetka[16];
bool daliDopolnitelniPin;
cin>>n;
niza=new Karticka*[n];
for (int i=0;i<n;i++){
   cin>>smetka;
   cin>>pin;
   cin>>daliDopolnitelniPin;
   if (!daliDopolnitelniPin)
    niza[i]=new Karticka(smetka,pin);
   else
    niza[i]=new SpecijalnaKarticka(smetka,pin);
}

Banka komercijalna("Komercijalna",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;
for (int i=0;i<m;i++){
   cin>>smetka>>pin;

    try{
        komercijalna.dodadiDopolnitelenPin(smetka,pin);
    }
    catch(OutOfBoundException &o)
    {
        o.print();
    }
}

Banka::setLIMIT(5);

komercijalna.pecatiKarticki();

}
