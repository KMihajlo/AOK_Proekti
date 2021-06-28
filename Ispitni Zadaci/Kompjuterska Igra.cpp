#include <iostream>
#include <cstring>
using namespace std;
typedef struct Igrac
{
    char korisnickoIme[15];
    int nivo;
    int poeni;
}Igrac;
typedef struct KompjuterskaIgra
{
    char ime[20];
    Igrac lista[30];
    int n;
}KompjuterskaIgra;
void najdobarIgrac(KompjuterskaIgra *lista, int n)
{
    int max = 0, i, id = 0, bla = 0;
    for(i = 0; i < n; i++)
    {
        if(lista[i].n > max)
        {
            max = lista[i].n;
            id = i;
        }
    }
    max = 0;
    for(i = 0; i < lista[id].n; i++)
    {
        if(lista[id].lista[i].poeni > max)
        {
            max = lista[id].lista[i].poeni;
            bla = i;
        }
    }
    cout <<"Najdobar igrac e igracot so korisnicko ime" << lista[id].lista[bla].korisnickoIme << "koj ja igra igrata" << lista[id].ime << endl;
}
int main() {
    int n,m;
    char ime[20];
    cin>>n;
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.ime>>nova.n;
        Igrac pole[30];
        for (int j=0; j<nova.n; j++) {
            Igrac nov;
            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
            nova.lista[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}

