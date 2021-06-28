#include <iostream>
#include <cstring>
using namespace std;
class Lekar
{
protected:
    int faksimil;
    char ime[10];
    char prezime[10];
    double plata;
public:
    Lekar(){}
    Lekar(int faksimil, char *ime, char *prezime, double plata)
    {
        this->faksimil = faksimil;
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->plata = plata;
    }
    Lekar(const Lekar &l)
    {
        this->faksimil = l.faksimil;
        strcpy(this->ime, l.ime);
        strcpy(this->prezime, l.prezime);
        this->plata = l.plata;
    }
    Lekar& operator=(const Lekar &l)
    {
        if(this!=&l)
        {
            this->faksimil = l.faksimil;
            strcpy(this->ime, l.ime);
            strcpy(this->prezime, l.prezime);
            this->plata = l.plata;
        }
        return *this;
    }
    void pecati()
    {
        cout << faksimil <<": " << ime << " " << prezime << endl;
    }
    double pl()
    {
        return plata;
    }
};
class MaticenLekar : public Lekar
{
private:
    int brojPacienti;
    double *kotizacii;
public:
    MaticenLekar()
    {
        this->kotizacii = NULL;
        this->brojPacienti = 0;
    }
    MaticenLekar(Lekar l, int brojPacienti, double *kotizacii)
    : Lekar(l)
    {
        this->brojPacienti = brojPacienti;
        this->kotizacii = new double[brojPacienti];
        for(int i = 0; i < brojPacienti; i++)
        {
            this->kotizacii[i] = kotizacii[i];
        }
    }
    MaticenLekar(const MaticenLekar &m) : Lekar(m)
    {
        this->brojPacienti = m.brojPacienti;
        this->kotizacii = new double[brojPacienti];
        for(int i = 0; i < brojPacienti; i++)
        {
            this->kotizacii[i] = m.kotizacii[i];
        }
    }
    MaticenLekar& operator=(const MaticenLekar &m)
    {
        if(this!=&m)
        {
            Lekar::operator=(m);
            this->brojPacienti = m.brojPacienti;
            this->kotizacii = new double[brojPacienti];
            for(int i = 0; i < brojPacienti; i++)
            {
                this->kotizacii[i] = m.kotizacii[i];
            }
        }
        return *this;
    }
    double prosek()
    {
        double sum = 0.0;
        for(int i = 0; i < brojPacienti; i++)
        {
            sum+=kotizacii[i];
        }
        return sum / brojPacienti;
    }
    void pecati()
    {
        Lekar::pecati();
        cout << "Prosek od naplateni kotizacii: " << prosek() << endl;
    }
    double pl()
    {
        return Lekar::pl() + (prosek() * 0.30);
    }
};
int main() {
	int n;
	cin>>n;
	int pacienti;
	double kotizacii[100];
	int faksimil;
	char ime [20];
	char prezime [20];
	double osnovnaPlata;

	Lekar * lekari = new Lekar [n];
	MaticenLekar * maticni = new MaticenLekar [n];

	for (int i=0;i<n;i++){
		cin >> faksimil >> ime >> prezime >> osnovnaPlata;
		lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
	}

	for (int i=0;i<n;i++){
		cin >> pacienti;
		for (int j=0;j<pacienti;j++){
			cin >> kotizacii[j];
		}
		maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
	}

	int testCase;
	cin>>testCase;

	if (testCase==1){
		cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
		for (int i=0;i<n;i++){
			lekari[i].pecati();
			cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].pl()<<endl;
		}
	}
	else {
		cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
		for (int i=0;i<n;i++){
			maticni[i].pecati();
			cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].pl()<<endl;
		}
	}

	delete [] lekari;
	delete [] maticni;

	return 0;
}
