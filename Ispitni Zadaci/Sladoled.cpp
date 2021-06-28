#include <iostream>
#include <cstring>
using namespace std;
class IceCream
{
private:
    char *ime;
    char sostav[100];
    float cena;
    int popust;
public:
    IceCream()
    {
        ime = NULL;
    }
    IceCream(char *ime, char *sostav, float cena)
    {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        strcpy(this->sostav, sostav);
        this->cena = cena;
        this->popust = 0;
    }
    ~IceCream()
    {
        delete [] ime;
    }
    IceCream(const IceCream &p)
    {
        this->ime = new char[strlen(p.ime)+1];
        strcpy(this->ime, p.ime);
        strcpy(this->sostav, p.sostav);
        this->cena = p.cena;
        this->popust = p.popust;
    }
    IceCream & operator=(const IceCream &p)
    {
        if(this != &p)
        {
            delete [] ime;
            this->ime = new char[strlen(p.ime)+1];
            strcpy(this->ime, p.ime);
            strcpy(this->sostav, p.sostav);
            this->cena = p.cena;
            this->popust = p.popust;
        }
        return *this;
    }
    friend ostream &operator<< (ostream &out, const IceCream & a)
    {
        cout << a.ime << ": " << a.sostav << " " << a.cena << " ";
        if(a.popust > 0)
            out << "(" << a.cena -((a.popust / (float)100) * a.cena) << ")";
        return out;
    }
    void setDiscount(int discount)
    {
        if(discount >= 0 && discount <= 100)
            this->popust = discount;
    }
     void setName(char* name)
     {
         ime = new char[strlen(name)+1];
         strcpy(ime, name);
     }
     IceCream& operator++() {
        popust += 5;
        return *this;
    }
    IceCream operator+(const char* extra) {

        char* newName = new char[strlen(ime) + strlen(extra) + 4];
        strcat(newName, ime);
        strcat(newName, " + ");
        strcat(newName, extra);

        IceCream res(newName, sostav, cena + 10);
        res.setDiscount(popust);
        return res;
    }
};
class IceCreamShop
{
private:
    char ime[50];
    IceCream *sladoledi;
    int brojSladoledi;
public:
    IceCreamShop()
    {
        sladoledi = NULL;
    }
    IceCreamShop(char *ime)
    {
        sladoledi = new IceCream[0];
        brojSladoledi = 0;
        strcpy(this->ime, ime);
    }
    ~IceCreamShop()
    {
        delete [] sladoledi;
    }
    IceCreamShop(const IceCreamShop &p)
    {
        strcpy(this->ime, p.ime);
        this->brojSladoledi = p.brojSladoledi;
        this->sladoledi = new IceCream[brojSladoledi];
        for(int i = 0; i < brojSladoledi; i++)
        {
            sladoledi[i] = p.sladoledi[i];
        }
    }
    IceCreamShop & operator=(const IceCreamShop &p)
    {
        if(this!=&p)
        {
            delete [] sladoledi;
            strcpy(this->ime, p.ime);
            this->brojSladoledi = p.brojSladoledi;
            this->sladoledi = new IceCream[brojSladoledi];
            for(int i = 0; i < brojSladoledi; i++)
            {
                sladoledi[i] = p.sladoledi[i];
            }
        }
    }
    IceCreamShop& operator+= (IceCream &ic) {
        IceCream *tmp = sladoledi;
        sladoledi = new IceCream[brojSladoledi + 1];
        for (int i = 0; i < brojSladoledi; ++i) {
            sladoledi[i] = tmp[i];
        }
        sladoledi[brojSladoledi] = ic;
        ++brojSladoledi;
        delete [] tmp;
        return *this;
    }
    friend ostream& operator<<(ostream &out, const IceCreamShop &ics) {
        cout << ics.ime << endl;
        for (int i = 0; i < ics.brojSladoledi; ++i) {
            out << ics.sladoledi[i] << endl;
        }
        return out;
    }
};
int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
	cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        //cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}
