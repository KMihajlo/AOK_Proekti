#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;
class Pica
{
private:
    char ime[15];
    int cena;
    char *sostojki;
    int namaluvanjeNaCenata;
public:
    Pica(){}
    Pica(char *ime, int cena, char *sostojki, int broj)
    {
        strcpy(this->ime, ime);
        this->cena = cena;
        this->sostojki = new char [strlen(sostojki)];
        strcpy(this->sostojki, sostojki);
        namaluvanjeNaCenata = broj;
    }
    Pica(const Pica &p)
    {
        strcpy(this->ime, p.ime);
        this->cena = p.cena;
        this->sostojki = new char [strlen(p.sostojki)];
        strcpy(this->sostojki, p.sostojki);
        namaluvanjeNaCenata = p.namaluvanjeNaCenata;
    }
    ~Pica()
    {
        delete [] sostojki;
    }
    void pecati()
    {
        cout << ime << " - " << sostojki << ", " << cena;
        if(namaluvanjeNaCenata>0)
        {
            int dc = cena - (cena * namaluvanjeNaCenata / 100);
            cout << ' ' << dc;
        }
        cout << endl;
    }
    bool istiSe(Pica p)
    {
        if(strcmp(sostojki, p.sostojki) == 0)
        {
            return true;
        }
        else
            return false;
    }
    Pica & operator=(const Pica &pr)
    {
        if(this != &pr)
        {
            delete [] sostojki;
            strcpy(this->ime, pr.ime);
            this->cena = pr.cena;
            this->sostojki = new char [strlen(pr.sostojki)];
            strcpy(this->sostojki, pr.sostojki);
            namaluvanjeNaCenata = pr.namaluvanjeNaCenata;
        }
        return *this;
    }
    int getCena()
    {
        return namaluvanjeNaCenata;
    }
};
class Picerija
{
private:
    char ime[15];
    Pica *p;
    int brojNaPici;
public:
    Picerija(){}
    Picerija(char *ime, int brojNaPici)
    {
        this->brojNaPici = brojNaPici;
        strcpy(this->ime, ime);
        p = new Pica[brojNaPici];
    }
    ~Picerija()
    {
        delete [] p;
    }
    void dodadi(Pica pr)
    {
        for(int i = 0; i < brojNaPici; i++)
        {
            if(p[i].istiSe(pr) == true)
            {
                cout << "Nemozhe da se dodade pica so isti sostojki" << endl;
            }
            else
            {
                brojNaPici++;
                p[brojNaPici-1] = pr;
            }
        }

    }
    void piciNaPromocija()
    {
        for(int i = 0; i < brojNaPici; i++)
        {
            if(p[i].getCena() != 0)
            {
                p[i].pecati();
            }
        }
    }
    void pecati()
    {
        for(int i = 0; i < brojNaPici; i++)
        {
            p[i].pecati();
        }
    }
};
int main()
{
    int n, cena, var;
    char ime[20], imenapicerija[15], sostojki[100];
    cin >> imenapicerija >> n;
    Pica pici[n];
    Picerija p(imenapicerija, n);
    for(int i = 0; i < n; i++)
    {
        cin >> ime >> cena;
        cin.get();
        cin.getline(sostojki, 100);
        cin >> var;
        pici[i] = Pica(ime, cena, sostojki, var);
        p.dodadi(pici[i]);
    }
    p.pecati();
    //Pica primer("test", 150, "test2", 10)
    //p.dodadi()
    return 0;
}
