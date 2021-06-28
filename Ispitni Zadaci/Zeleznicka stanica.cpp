#include <iostream>
#include <cstring>
using namespace std;
typedef struct Voz
{
    char relacija[50];
    float kilometri;
    int brojPatnici;
}Voz;
typedef struct ZeleznickaStanica
{
    char grad[20];
    Voz vozovi[30];
    int brojVozovi;
}ZeleznickaStanica;
void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
{
    int i, j, min = 10000, id1 = 0, id2 = 0;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < zs[i].brojVozovi; j++)
        {
            if(strcmp(zs[i].grad, grad) == 0)
            {
                if(zs[i].vozovi[j].kilometri <= min)
                {
                    min = zs[i].vozovi[j].kilometri;
                	id1 = i;
                	id2 = j;
                }
            }
        }
    }
    cout << "Najkratka relacija: " << zs[id1].vozovi[id2].relacija << " (" << zs[id1].vozovi[id2].kilometri << " km)" << endl;
}
int main(){

    int n;
	cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        cin >> zStanica[i].grad >> zStanica[i].brojVozovi;
        for(int j = 0; j < zStanica[i].brojVozovi; j++)
        {
            cin >> zStanica[i].vozovi[j].relacija >> zStanica[i].vozovi[j].kilometri >> zStanica[i].vozovi[j].brojPatnici;
        }
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
    }

    char grad[25];
    cin>>grad;

	najkratkaRelacija(zStanica,n,grad);
	return 0;
}
