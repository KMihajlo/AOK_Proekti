#include <iostream>
#include <cstring>
using namespace std;

//Vasiot kod ovde

class Ekipa
{
protected:
    char ime[15];
    int brojPobedi;
    int brojPorazi;
public:
    Ekipa(){}
    Ekipa(char *ime, int brojPobedi, int brojPorazi)
    {
        strcpy(this->ime, ime);
        this->brojPobedi = brojPobedi;
        this->brojPorazi = brojPorazi;
    }
    void pecati()
    {
        cout << "Ime: " << ime << " Pobedi: " << brojPobedi << " Porazi: " << brojPorazi;
    }
};
class FudbalskaEkipa : public Ekipa
{
private:
    int brojCrveni;
    int brojZolti;
    int brojNeresheni;
public:
    FudbalskaEkipa(){}
    FudbalskaEkipa(char *ime, int brojPobedi, int brojPorazi, int brojCrveni, int brojZolti, int brojNeresheni)
    : Ekipa(ime, brojPobedi, brojPorazi)
    {
        this->brojCrveni = brojCrveni;
        this->brojZolti = brojZolti;
        this->brojNeresheni = brojNeresheni;
    }
    void pecati()
    {
        Ekipa::pecati();
        cout << " Nereseni: " << brojNeresheni << " Poeni: " << (brojPobedi*3) + (brojNeresheni) << endl;
    }
};
int main(){
	char ime[15];
	int pob,por,ck,zk,ner;
	cin>>ime>>pob>>por>>ck>>zk>>ner;
	FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
	f1.pecati();
	return 0;
}
