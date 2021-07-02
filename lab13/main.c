#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#define NMAX 10
typedef struct tip_nod{
    long ind1,ind2;
    struct tip_nod *stg,*dr;
} TIP_NOD;

void prod_matr(int n, long c[NMAX][NMAX], int d[NMAX+1])
{
    int i, j, k, l, poz;
    long min, val;
    for(i = 1; i <= n; i++) c[i][i]=0;
    for(l = 1; l <= n-1; l++)
        for(i = 1; i <= n-l; i++)
        {
            j = i + l;
            min = 0x7fffffff;
            for(k = i; k <= j-1; k++)
            {
                val=c[i][k]+c[k+1][j]+(long)d[i]*d[k+1]*d[j+1];
                if(val < min)
                {
                    min = val;
                    poz = k;

                }
            }
            c[i][j] = min;
            c[j][i] = poz;
        }
}

TIP_NOD *constr_arbore(TIP_NOD *p,int i,int j,long c[NMAX][NMAX])
{
    p = (TIP_NOD *)malloc(sizeof(TIP_NOD));
    p->ind1 = i;
    p->ind2 = j;
    if(i < j)
    {
        p->stg = constr_arbore(p->stg, i, c[j][i], c);
        p->dr = constr_arbore(p->dr, c[j][i]+1, j, c);
    }
    else
    {
        p->stg=0; p->dr=0;
    }
    return p;
}

void postordine(TIP_NOD *p, int nivel)
{
    int i;
    if(p != 0)
    {
        postordine(p->stg, nivel+1);
        postordine(p->dr, nivel+1);
        for(i = 0; i <= nivel; i++) printf(" ");
        printf("(%ld,%ld)\n", p->ind1, p->ind2);
    }
}

int main()
{
    int i, j, n;
    long c[NMAX][NMAX];
    int d[NMAX+1]; /* dimensiunile matricelor */
    TIP_NOD *rad;
    printf("\nIntroduceti nr.matricelor n=");
    scanf("%d",&n);
    printf("\nIntroduceti dimensiunile matricelor\n");
    for(i = 1; i <= n+1; i++)
    {
        printf("\nDimensiunea d[%d]=", i);
        scanf("%d", &d[i]);
    }
    prod_matr(n, c, d);
    printf("\nMATRICEA C\n");
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++) printf("%6ld", c[i][j]);
        printf("\n");
    }
    printf("\nNR.MINIM DE INMULTIRI = %ld", c[1][n]);
    getch();
    rad = constr_arbore(rad, 1, n, c);
    printf("\nARBORELE IN POSTORDINE\n");
    postordine(rad, 0);
    return 0;
}
