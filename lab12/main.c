/* Program de sortare a unui vector prin interclasare */
#include <stdio.h>
#include <conio.h>
#define NMAX 100
int a[NMAX]; /* vectorul de sortat */

void afisare(int n)
{ /* afișarea vectorului */
    int i;
    printf("\n");
    for(i=0; i<n; i++)
    {
        printf("%5d", a[i]);
        if(((i+1) % 10)==0) printf("\n");
    }
    printf("\n");
}

void comb(int inf, int med, int sup)
{ /* interclasarea vectorilor a[inf .. med] și a[med+1 .. sup] */
    int i, j, k, l;
    int b[NMAX];
    i = inf;
    j = med+1;
    k = inf;
    while((i<=med)&(j<=sup))
    {
        if(a[i]<=a[j])
        {
            b[k] = a[i];
            i++;
        }
        else
        {
            b[k] = a[j];
            j++;
        }
        k++;
    }
    for(l=i; l<=med; l++)
    { /* au ramas elemente in stânga */
        b[k] = a[l];
        k++;
    }
    for(l=j;l<=sup;l++)
    { /* au ramas elemente in dreapta */
        b[k] = a[l];
        k++;
    }
    /* secvența între inf și sup este sortată */
    for(l=inf; l<=sup; l++) a[l] = b[l];
}

void divide_impera(int inf,int sup)
{
    int med;
    if(inf<sup)
    {
        med = (inf+sup) / 2;
        divide_impera(inf, med);
        divide_impera(med+1, sup);
        comb(inf, med, sup);
    }
}

int main(void)
{
    int i, n;
    printf("\nIntroduceți numarul de elemente n=");
    scanf("%d",&n);
    printf("\nIntroduceti elementele vectorului:\n");
    for(i=0;i<n;i++)
    {
        printf("a[%d]=", i);
        scanf("%d", &a[i]);
    }
    printf("\nVECTORUL NESORTAT\n");
    afisare(n);
    divide_impera(0,n-1);
    printf("\nVECTORUL SORTAT\n");
    afisare(n);
    getch();
    return 0;
}
