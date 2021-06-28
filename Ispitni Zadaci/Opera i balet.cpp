#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код
class Delo
{
private:
    char ime[50];
    int godina;
    char poteklo[50];
public:
    Delo(char *ime = "", int godina = 0, char *poteklo = "")
    {
        strcpy(this->ime, ime);
        this->godina = godina;
        strcpy(this->poteklo, poteklo);
    }
    Delo &operator=(Delo &d)
    {
        if(this!=&d){
        strcpy(this->ime, d.ime);
        this->godina = d.godina;
        strcpy(this->poteklo, d.poteklo);
        }
        return *this;
    }
    char *getIme()
    {
        return ime;
    }
    int getGodina()
    {
        return godina;
    }
    char *getPoteklo()
    {
        return poteklo;
    }
};
bool operator==(Delo d1, Delo &d2)
{
    if(strcmp(d1.getIme(), d2.getIme()) == 0)
    {
        return true;
    }
    else
        return false;
}
class Pretstava
{
protected:
    Delo d;
    int karti;
    char data[15];
public:
    Pretstava(){}
    Pretstava(Delo d, int karti, char *data)
    {
        this->d = d;
        this->karti = karti;
        strcpy(this->data, data);
    }
    Delo getDelo()
    {
        return d;
    }
    int getKarti()
    {
        return karti;
    }
    virtual int cena()
    {
        int m = 0, n = 0;
        if(d.getGodina() >= 1900)
            m = 50;
        else if(d.getGodina() >= 1800&&d.getGodina() < 1900)
            m = 75;
        else
            m = 100;
        if(strcmp(d.getPoteklo(), "Italija")==0)
            n = 100;
        else if(strcmp(d.getPoteklo(), "Rusija")==0)
            n = 150;
        else
            n = 80;
        return m + n;
    }
};
class Balet : public Pretstava
{
private:
public:
    static int cenaBalet;
    static void setCenaBalet(int newCena)
    {
        cenaBalet = newCena;
    }
    Balet(Delo d, int karti, char *data)
    :Pretstava(d, karti, data){}
    int cena()
    {
        return cenaBalet + Pretstava::cena();
    }
};
class Opera : public Pretstava
{
private:
public:
    Opera(){}
    Opera(Delo d, int karti, char *data)
    :Pretstava(d, karti, data){}
};
int Balet::cenaBalet = 150;
int prihod(Pretstava **p, int n)
{
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum = sum + (p[i]->cena()*p[i]->getKarti());
    }
    return sum;
}
int brojPretstaviNaDelo(Pretstava **p, int n, Delo &d)
{
    int count = 0;
    for(int i = 0; i < n; i++)
    {
        if(p[i]->getDelo() == d)
            count++;
    }
    return count;
}
//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}
