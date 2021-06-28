#include <iostream>
#include <cstring>
using namespace std;
// vashiot kod ovde
class Vozac
{
protected:
    char ime[100];
    int vozrast;
    int brojTrki;
    bool daliVeteran;
public:
    Vozac(char *ime = "", int vozrast = 0, int brojTrki = 0, bool daliVeteran = false)
    {
        strcpy(this->ime, ime);
        this->vozrast = vozrast;
        this->brojTrki = brojTrki;
        this->daliVeteran = daliVeteran;
    }
    virtual float danok() = 0;
    virtual float Zarabotuvachka() = 0;
    friend ostream &operator<<(ostream &out, Vozac &v)
    {
        out << v.ime << endl << v.vozrast << endl << v.brojTrki << endl;
        if(v.daliVeteran == true)
        {
            out << "VETERAN" << endl;
        }
        return out;
    }
};
bool operator==(Vozac &v1, Vozac &v2)
{
    if(v1.Zarabotuvachka() == v2.Zarabotuvachka())
        return true;
    else
        return false;
}
class Avtomobilist : public Vozac
{
private:
    float cena;
public:
    Avtomobilist(char *ime = "", int vozrast = 0, int brojTrki = 0, bool daliVeteran = false, float cena = 0.0)
    : Vozac(ime, vozrast, brojTrki, daliVeteran)
    {
        this->cena = cena;
    }
    float Zarabotuvachka()
    {
        return cena/5;
    }
    float danok()
    {
        if(brojTrki > 10)
        {
            return 0.15 * Zarabotuvachka();
        }
        else
        {
            return 0.10 * Zarabotuvachka();
        }
    }
};
class Motociklist : public Vozac
{
private:
    int mokjnost;
public:
    Motociklist(char *ime = "", int vozrast = 0, int brojTrki = 0, bool daliVeteran = false, int mokjnost = 0)
    : Vozac(ime, vozrast, brojTrki, daliVeteran)
    {
        this->mokjnost = mokjnost;
    }
    float Zarabotuvachka()
    {
        return mokjnost*20;
    }
    float danok()
    {
        if(daliVeteran)
        {
            return 0.25 * Zarabotuvachka();
        }
        else
        {
            return 0.20 * Zarabotuvachka();
        }
    }
};
int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *v)
{
    int tmp = 0;
    for(int i = 0; i < n; i++)
    {
        if(vozaci[i]->Zarabotuvachka()==v->Zarabotuvachka())
            tmp++;
    }
    return tmp;
}
int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}
