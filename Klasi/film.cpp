#include <iostream>
#include <cstring>
using namespace std;
class Film
{
private:
    char ime[100];
    char rezhiser[50];
    char zanr[50];
    int godina;
public:
    Film(){}
    Film(char *ime, char *rezhiser, char *zanr, int godina)
    {
        strcpy(this->ime, ime);
        strcpy(this->rezhiser, rezhiser);
        strcpy(this->zanr, zanr);
        this->godina = godina;
    }
    int getGodina()
    {
        return godina;
    }
    void print()
    {
        cout << "Ime: " << ime << endl << "Reziser: " << rezhiser << endl << "Zanr: " << zanr << endl << "Godina: " << godina << endl;
    }
};
void pecati_po_godina(Film *f, int n, int godina)
{
    int i;
    for(i = 0; i < n; i++)
    {
        if(f[i].getGodina() == godina)
            f[i].print();
    }
}
int main()
{
    char ime[100], rezhiser[50], zanr[50];
    int godina, n, i;
    cin >> n;
    Film f[n];
    for(i = 0; i < n; i++)
    {
        cin >> ime >> rezhiser >> zanr >> godina;
        f[i] = Film(ime, rezhiser, zanr, godina);
    }
    cin >> godina;
    pecati_po_godina(f, n, godina);
    delete [] f;
    return 0;
}
