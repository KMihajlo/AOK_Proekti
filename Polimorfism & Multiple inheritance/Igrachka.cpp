#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Igrachka
{
public:
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    //Дополнително барање 1
    virtual float getPlostina() = 0;
};

class Forma
{
protected:
    char boja[100];
    int gustina;
public:
    //да се имплементираат потребните методи
    Forma(){}
    Forma(char *boja, int gustina)
    {
        strcpy(this->boja, boja);
        this->gustina = gustina;
    }
};

class Topka : public Forma, public Igrachka
{
private:
    int radius;
public:
    Topka(){}
    Topka(char *boja, int gustina, int radius) : Forma(boja, gustina)
    {
        this->radius = radius;
    }
    float getVolumen()
    {
        return (4/3.0) * 3.14 * pow(this->radius, 3);
    }
    float getMasa()
    {
        return getVolumen() * this->gustina;
    }
    float getPlostina()
    {
        return 4.0 * 3.14 * pow(this->radius, 2);
    }
};
class Kocka : public Forma, public Igrachka
{
private:
    int visina;
    int shirina;
    int dlabochina;
public:
    Kocka(){}
    Kocka(char *boja, int gustina, int visina, int shirina, int dlabochina) : Forma(boja, gustina)
    {
        this->visina = visina;
        this->shirina = shirina;
        this->dlabochina = dlabochina;
    }
    float getVolumen()
    {
        return this->visina * this->shirina * this->dlabochina;
    }
    float getMasa()
    {
        return getVolumen() * this->gustina;
    }
    float getPlostina()
    {
        return (2*visina*shirina)+(2*visina*dlabochina)+(2*shirina*dlabochina);
    }
};

int main()
{
    int n, tip, shirina, visina, gustina, dlabochina, radius;
    char boja[100];
    cin >> n;
    // vnesi informacii za kupche
    Igrachka **kupche = new Igrachka*[n];
    for(int i = 0; i < n; i++)
    {
        cin >> tip;
        if(tip == 1)
        {
            cin >> boja >> gustina >> radius;
            kupche[i] = new Topka(boja, gustina, radius);
        }
        if(tip == 2)
        {
            cin >> boja >> gustina >> visina >> shirina >> dlabochina;
            kupche[i] = new Kocka(boja, gustina, visina, shirina, dlabochina);
        }
    }
    // vnesi informacii za igrachkata na Petra
    cin >> boja >> gustina >> visina >> shirina >> dlabochina;
    Kocka petra(boja, gustina, visina, shirina, dlabochina);
    // baranje 1
    float vkupnaMasa = 0, max = -1.0, min = 100000.0;
    for(int i = 0; i < n; i++)
    {
        vkupnaMasa += kupche[i]->getMasa();
        if(kupche[i]->getVolumen() > max)
        {
            max = kupche[i]->getVolumen();
        }
        if(kupche[i]->getPlostina() < min)
        {
            min = kupche[i]->getPlostina();
        }
    }
    if(vkupnaMasa > petra.getMasa())
    {
        cout << "DA" << endl;
    }
    else
        cout << "NE" << endl;
    // baranje 2
    cout << "Razlikata e: " << max - petra.getVolumen();
    // Дополнително барање 2
    cout << "Razlikata e: " << min - petra.getPlostina();
    delete [] kupche;
    return 0;
}
