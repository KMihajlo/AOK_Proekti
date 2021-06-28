#include <iostream>
#include <cstring>
using namespace std;
class Automobile
{
private:
    char *marka;
    int *registracija;
    int maxBrzina;
public:
    Automobile()
    {
        this->marka = NULL;
        registracija = new int[5];
        maxBrzina = 0;
    }
    Automobile(char *marka, int *registracija, int maxBrzina)
    {
        this->marka = new char[strlen(marka)+1];
        strcpy(this->marka, marka);
        this->registracija = new int[5];
        for(int i = 0; i < 5; i++)
        {
            this->registracija[i] = registracija[i];
        }
        this->maxBrzina = maxBrzina;
    }
    ~Automobile()
    {
        delete [] marka;
        delete [] registracija;
    }
    Automobile(const Automobile &a)
    {
        this->marka = new char[strlen(a.marka)+1];
        strcpy(this->marka, a.marka);
        this->registracija = new int[5];
        for(int i = 0; i < 5; i++)
        {
            this->registracija[i] = a.registracija[i];
        }
        this->maxBrzina = a.maxBrzina;
    }
    Automobile &operator =(const Automobile &a)
    {
        if(this!=&a)
        {
            delete [] marka;
            delete [] registracija;
            this->marka = new char[strlen(a.marka)+1];
            strcpy(this->marka, a.marka);
            this->registracija = new int[5];
            for(int i = 0; i < 5; i++)
            {
                this->registracija[i] = a.registracija[i];
            }
            this->maxBrzina = a.maxBrzina;
        }
        return *this;
    }
    int getMaximumBrzina()
    {
        return maxBrzina;
    }
    bool operator==(const Automobile &a)
    {
        for(int i = 0; i < 5; i++)
        {
            if(registracija[i] != a.registracija[i])
                return false;
        }
        return true;
    }
    friend ostream &operator<<(ostream &out, const Automobile &a)
    {
        out << "Marka: " << a.marka << " Registracija[ ";
        for(int i = 0; i < 5; i++)
        {
            out << a.registracija[i] << " ";
        }
        out << "]" << endl;
        return out;
    }
};
class RentACar
{
private:
    char ime[100];
    Automobile *koli;
    int brojKoli;
public:
    RentACar()
    {
        koli = new Automobile[0];
        brojKoli = 0;
    }
    RentACar(char *ime)
    {
        strcpy(this->ime, ime);
        this->brojKoli = 0;
        this->koli = new Automobile[brojKoli];
    }
    ~RentACar()
    {
        delete [] koli;
    }
    RentACar(const RentACar &r)
    {
        strcpy(this->ime, r.ime);
        this->brojKoli = r.brojKoli;
        this->koli = new Automobile[brojKoli];
        for(int i = 0; i < brojKoli; i++)
        {
            this->koli[i] = r.koli[i];
        }
    }
    RentACar &operator=(const RentACar &r)
    {
        if(this!=&r)
        {
            delete [] this->koli;
            strcpy(this->ime, r.ime);
            this->brojKoli = r.brojKoli;
            this->koli = new Automobile[brojKoli];
            for(int i = 0; i < brojKoli; i++)
            {
                this->koli[i] = r.koli[i];
            }
        }
        return *this;
    }
    RentACar &operator+=(const Automobile &a)
    {
        Automobile *tmp = new Automobile[brojKoli+1];
        for(int i = 0; i < brojKoli; i++)
        {
            tmp[i] = koli[i];
        }
        tmp[brojKoli++] = a;
        delete [] koli;
        koli = tmp;
        return *this;
    }
    RentACar &operator -=(const Automobile &a)
    {
        int k = 0, var = 0;
        for(int i = 0; i < brojKoli; i++)
        {
            if(koli[i] == a)
            {
                continue;
            }
            else
                koli[k++] = koli[i];
        }
        brojKoli = k;
        return *this;
    }
    void pecatiNadBrzina(int n)
    {
        for(int i = 0; i < brojKoli; i++)
        {
            if(koli[i].getMaximumBrzina() > n)
                cout << koli[i];
        }
    }
};
int main() {
    RentACar agencija("FINKI-Car");
    int n;
    cin>>n;

    for (int i=0; i<n; i++) {
        char marka[100];
        int regisracija[5];
        int maximumBrzina;

        cin>>marka;

        for (int i=0; i<5; i++)
            cin>>regisracija[i];

        cin>>maximumBrzina;

        Automobile nov=Automobile(marka,regisracija,maximumBrzina);

        //dodavanje na avtomobil
        agencija+=nov;

    }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0; i<5; i++)
        cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}
