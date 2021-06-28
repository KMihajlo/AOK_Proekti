#include <stdio.h>
typedef struct proizvod
{
    char ime[15];
    float cena;
    int kolichina;
}proizvod;
int main()
{
    int n, i;
    float sum = 0;
    scanf("%d", &n);
    proizvod article[n];
    for(i = 0; i < n; i++)
    {
        scanf("%s %f %d", &article[i].ime, &article[i].cena, &article[i].kolichina);
    }
    for(i = 0; i < n; i++)
    {
        printf("%d. %s   %.2f x %d = %.2f\n", i+1, article[i].ime, article[i].cena, article[i].kolichina, article[i].cena * article[i].kolichina);
        sum = sum + (article[i].cena * article[i].kolichina);
    }
    printf("Total: %.2f\n", sum);
    return 0;
}
