#include <stdio.h>
#include <string.h>
typedef struct SkiLift
{
    char ime[15];
    int max_skijaci;
    int voUpotreba;
}SkiLift;
typedef struct skiCenter
{
    char ime[20];
    char drzava[20];
    SkiLift niza[20];
    int br_lifts;
}skiCenter;
void najgolemKapacitet(skiCenter *sc, int n)
{
    int i, max = 0, j, id, sum = 0;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < sc[i].niza[j].voUpotreba; j++)
        {
            sum = sum + sc[i].niza[j].max_skijaci;
        }
        if(sum > max)
        {
            max = sum;
            id = i;
        }
        if(sum == max)
        {
            if(sc[i].br_lifts > sc[id].br_lifts)
            {
                id = i;
            }
        }
    }
    printf("%s\n%s\n%d", sc[id].ime, sc[id].drzava, sc[id].br_lifts);
}
int main()
{
	int i, j, n, broj;
	skiCenter sc[20];
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		//printf("Ime:");
		scanf("%s", sc[i].ime);
		//printf("\nDrzava:");
		scanf("%s", sc[i].drzava);
		scanf("%d", &sc[i].br_lifts);

		for (j = 0; j < sc[i].br_lifts; j++){
			scanf("%s", sc[i].niza[j].ime);
			scanf("%d", &sc[i].niza[j].max_skijaci);
			scanf("%d", &sc[i].niza[j].voUpotreba);
		}
	}
	najgolemKapacitet(sc, n);

	return 0;
}

