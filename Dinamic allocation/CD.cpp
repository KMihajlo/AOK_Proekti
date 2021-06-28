#include <iostream>
#include <cstring>
using namespace std;
enum tip
{
    pop, rap, rok
};
class Pesna
{
private:
    char *ime;
    int vremetraenje;
    tip t;
public:
    //Pesna(){}
    Pesna(char *ime = "", int vremetraenje = 0, tip t = rap)
    {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime, ime);
        this->vremetraenje = vremetraenje;
        this->t = t;
    }
    ~Pesna()
    {
        delete [] ime;
    }
    Pesna(const Pesna &p)
    {
        this->ime = new char[strlen(p.ime)+1];
        strcpy(this->ime, p.ime);
        this->vremetraenje = p.vremetraenje;
        t = p.t;
    }
    Pesna &operator =(const Pesna &p)
    {
        if(this != &p)
        {
            delete [] ime;
            this->ime = new char[strlen(p.ime)+1];
            strcpy(this->ime, p.ime);
            this->vremetraenje = p.vremetraenje;
            t = p.t;
        }
        return *this;
    }
    int getVremetraenje()
    {
        return vremetraenje;
    }
    tip getTip()
    {
        return t;
    }
    void pecati()
    {
        cout << "\"" << ime << "\"" << "-" << vremetraenje << "min" << endl;
    }
};
class CD
{
private:
    Pesna pesni[10];
    int brojPesni;
    int maxVremetraenje;
public:
    CD(){}
    CD(int maxVremetraenje)
    {
        this->brojPesni = 0;
        this->maxVremetraenje = maxVremetraenje;
    }
    ~CD(){}
    CD(const CD &c)
    {
        this->brojPesni = c.brojPesni;
        for(int i = 0; i < brojPesni; i++)
        {
            this->pesni[i] = c.pesni[i];
        }
        this->maxVremetraenje = c.maxVremetraenje;
    }
    int getBroj()
    {
        return brojPesni;
    }
    Pesna getPesna(int i)
    {
        return pesni[i];
    }
    void dodadiPesna(Pesna p)
    {
        int maxsum;
        for(int i = 0; i < brojPesni; i++)
        {
            maxsum = maxsum + pesni[i].getVremetraenje();
        }
        if(brojPesni < 10 || (maxsum + p.getVremetraenje()) <= maxVremetraenje)
        {
            pesni[brojPesni] = p;
            brojPesni++;
        }
    }
    void pecatiPesniPoTip(tip t)
    {
        for(int i = 0; i < brojPesni; i++)
        {
            if(pesni[i].getTip() == t)
            {
                pesni[i].pecati();
            }
        }
    }
};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}
