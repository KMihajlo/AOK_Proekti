#include <iostream>
#include <cstring>
using namespace std;

//Vasiot kod ovde....

class Nedviznina
{
protected:
    char *adresa;
    int kvadratura;
    int cenaKvadrat;
public:
    Nedviznina()
    {
        this->adresa = new char[0];
    }
    /*Nedviznina(char *adresa, int kvadratura, int cenaKvadrat)
    {
        this->adresa = new char[strlen(adresa)+1];
        strcpy(this->adresa, adresa);
        this->kvadratura = kvadratura;
        this->cenaKvadrat = cenaKvadrat;
    }*/
    Nedviznina(const Nedviznina &n)
    {
        this->adresa = new char[strlen(n.adresa)+1];
        strcpy(this->adresa, n.adresa);
        this->kvadratura = n.kvadratura;
        this->cenaKvadrat = n.cenaKvadrat;
    }
    Nedviznina &operator=(Nedviznina &n)
    {
        if(this!=&n)
        {
            delete [] adresa;
            this->adresa = new char[strlen(n.adresa)+1];
            strcpy(this->adresa, n.adresa);
            this->kvadratura = n.kvadratura;
            this->cenaKvadrat = n.cenaKvadrat;
        }
        return *this;
    }
    ~Nedviznina()
    {
        delete [] adresa;
    }
    int cena()
    {
        return this->kvadratura * cenaKvadrat;
    }
    void pecati()
    {
        cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po kvadrat: " << cenaKvadrat << endl;
    }
    float danokNaImot()
    {
        return cena()*0.05;
    }
    friend istream& operator>>(istream &in, Nedviznina &n)
    {
        return in >> n.adresa >> n.kvadratura >> n.cenaKvadrat;
    }
    char *getAdresa()
    {
        return adresa;
    }
};
class Vila : public Nedviznina
{
private:
    int danokNaLuksuz;
public:
    Vila(){}
    void pecati()
    {
        cout << adresa << ", Kvadratura: " << kvadratura << ", Cena po kvadrat: " << cenaKvadrat << ", Danok na luksuz: " << danokNaLuksuz << endl;
    }
    float danokNaImot()
    {
        return Nedviznina::danokNaImot() + (cena() / danokNaLuksuz);
    }
    friend istream&operator>>(istream &in, Vila &v)
    {
        in >> v.adresa >> v.kvadratura >> v.cenaKvadrat;
        in >> v.danokNaLuksuz;
        return in;
    }
};
int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}
