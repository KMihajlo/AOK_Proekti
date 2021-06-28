#include <iostream>
#include <cstring>
using namespace std;

// вашиот код треба да биде тука

class Transport
{
protected:
    char destinacija[20];
    int osnovnaCena;
    int rastojanie;
public:
    Transport(const char *destinacija = "", int osnovnaCena = 0, int rastojanie = 0) {
        strcpy(this->destinacija, destinacija);
        this->osnovnaCena = osnovnaCena;
        this->rastojanie = rastojanie;
    }
    Transport &operator=(const Transport &t)
    {
        if(this!=&t)
        {
            strcpy(this->destinacija, t.destinacija);
            this->osnovnaCena = t.osnovnaCena;
            this->rastojanie = t.rastojanie;
        }
        return *this;
    }
    virtual float cenaTransport() = 0;
    char *getDestinacija()
    {
        return destinacija;
    }
    int getOsnovnaCena()
    {
        return osnovnaCena;
    }
    int getRastojanie()
    {
        return rastojanie;
    }
};
bool operator<(Transport &t1, Transport &t2)
{
    if(t1.getRastojanie() < t2.getRastojanie())
        return true;
    else
        return false;
}
class AvtomobilTransport : public Transport
{
private:
    bool PlatenShofer;
public:
    AvtomobilTransport(const char *destinacija = "", int osnovnaCena = 0, int rastojanie = 0, bool PlatenShofer = false)
    : Transport(destinacija, osnovnaCena, rastojanie)
    {
        this->PlatenShofer = PlatenShofer;
    }
    float cenaTransport()
    {
        if(PlatenShofer)
            return osnovnaCena * 1.2;
        else
            return osnovnaCena;
    }
    AvtomobilTransport &operator=(const AvtomobilTransport &t)
    {
        if(this!=&t)
        {
            Transport::operator=(t);
            this->PlatenShofer = t.PlatenShofer;
        }
        return *this;
    }
};
class KombeTransport : public Transport
{
private:
    int brojLugje;
public:
    KombeTransport(const char *destinacija = "", int osnovnaCena = 0, int rastojanie = 0, int brojLugje = 0)
    : Transport(destinacija, osnovnaCena, rastojanie)
    {
        this->brojLugje = brojLugje;
    }
    float cenaTransport()
    {
        return osnovnaCena - (brojLugje * 200);
    }
    KombeTransport &operator=(const KombeTransport &t)
    {
        if(this!=&t)
        {
            Transport::operator=(t);
            this->brojLugje = t.brojLugje;
        }
        return *this;
    }
};
void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport &t)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(ponudi[i]->cenaTransport() > ponudi[j]->cenaTransport())
            {
                Transport *tmp = ponudi[i];
                ponudi[i] = ponudi[j];
                ponudi[j] = tmp;
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        if(ponudi[i]->cenaTransport() > t.cenaTransport())
        {
            cout << ponudi[i]->getDestinacija() << " " << ponudi[i]->getRastojanie() << " " << ponudi[i]->cenaTransport() << endl;
        }
    }
}
int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
