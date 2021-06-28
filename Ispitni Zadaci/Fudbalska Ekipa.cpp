#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde

class FudbalskaEkipa
{
protected:
    char ime[100];
    int golovi[10];
public:
    FudbalskaEkipa(){}
    FudbalskaEkipa(char *ime, int *golovi)
    {
        strcpy(this->ime, ime);
        for(int i = 0; i < 10; i++)
        {
            this->golovi[i] = golovi[i];
        }
    }
    FudbalskaEkipa&operator+=(int gol)
    {
        for(int i = 0; i < 9; i++)
        {
            golovi[i] = golovi[i+1];
        }
        golovi[9] = gol;
        return *this;
    }
    friend ostream &operator <<(ostream &out, FudbalskaEkipa &f)
    {
        out << f.getIme()<<endl;
        out << f.ime << endl;
        out << f.uspeh() << endl;
        return out;
    }
    virtual char *getIme() = 0;
    virtual int uspeh() = 0;
};
bool operator>(FudbalskaEkipa &f1, FudbalskaEkipa &f2)
{
    if(f1.uspeh() > f2.uspeh())
        return true;
    else
        return false;
}
class Klub : public FudbalskaEkipa
{
private:
    char imeKlub[100];
    int tituli;
public:
    Klub(){}
    Klub(char *ime, int *golovi, char *imeKlub, int tituli)
    : FudbalskaEkipa(ime, golovi)
    {
        strcpy(this->imeKlub, imeKlub);
        this->tituli = tituli;
    }
    Klub &operator+=(int gol)
    {
        for(int i = 0; i < 9; i++)
        {
            golovi[i] = golovi[i+1];
        }
        golovi[9] = gol;
        return *this;
    }
    friend ostream &operator <<(ostream &out, Klub &k)
    {
        out << k.imeKlub << endl;
        out << k.ime << endl;
        out << k.uspeh() << endl;
        return out;
    }
    int uspeh()
    {
        int sum = 0;
        for(int i = 0; i < 10; i++)
        {
            sum += golovi[i];
        }
        sum *= 3;
        return sum + (tituli*1000);
    }
    char *getIme()
    {
        return imeKlub;
    }
};
class Reprezentacija : public FudbalskaEkipa
{
private:
    char imeDrzava[100];
    int nastapi;
public:
    Reprezentacija(){}
    Reprezentacija(char *ime, int *golovi, char *imeDrzava, int nastapi)
    : FudbalskaEkipa(ime, golovi)
    {
        strcpy(this->imeDrzava, imeDrzava);
        this->nastapi = nastapi;
    }
    Reprezentacija &operator+=(int gol)
    {
        for(int i = 0; i < 9; i++)
        {
            golovi[i] = golovi[i+1];
        }
        golovi[9] = gol;
        return *this;
    }
    friend ostream &operator <<(ostream &out, Reprezentacija &r)
    {
        out << r.imeDrzava << endl;
        out << r.ime << endl;
        out << r.uspeh() << endl;
        return out;
    }
    int uspeh()
    {
        int sum = 0;
        for(int i = 0; i < 10; i++)
        {
            sum += golovi[i];
        }
        sum *= 3;
        return sum + (nastapi*50);
    }
    char *getIme()
    {
        return imeDrzava;
    }
};
void najdobarTrener(FudbalskaEkipa **ekipi, int n)
{
    int tmp = 0;
    int id = 0;
    for(int i = 0; i < n; i++)
    {
        if(ekipi[i]->uspeh() > tmp)
        {
            tmp = ekipi[i]->uspeh();
            id = i;
        }
    }
    cout << *ekipi[id] << endl;
}
int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
