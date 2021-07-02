#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define NMAX 10
int n; /* dimensiunea (ordinul) tablei de șah */
int nr_solutie;
int a[NMAX][NMAX];
int gata(int k)
{ /* testează condițiile de continuare */
    int i,j;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            if (a[i][j]==0) return 0;
    return 1;
}
void back_recursiv(int k, int p, int ord)
{
    int i, j;
    a[k][p]=ord;
    ord++;
    if (gata(k)==1)
    {
        printf("\nO solutie este: \n");
        for (i=1; i<=n; i++)
        {
            for (j=1; j<=n; j++) printf("%2d ", a[i][j]);
            printf("\n");
        }
    }
    else
    {
        if ((a[k-2][p-1]==0) && (k-2>0) && (p-1>0))
        {
            back_recursiv(k-2, p-1, ord);
            a[k-2][p-1]=0;
        }
        if ((a[k-1][p-2]==0) && (k-1>0) && (p-2>0))
        {
            back_recursiv(k-1, p-2, ord);
            a[k-1][p-2]=0;
        }
        if ((a[k-2][p+1]==0) && (k-2>0) && (p+1<n+1))
        {
            back_recursiv(k-2, p+1, ord);
            a[k-2][p+1]=0;
        }
        if ((a[k-1][p+2]==0) && (k-1>0) && (p+2<n+1))
        {
            back_recursiv(k-1, p+2, ord);
            a[k-1][p+2]=0;
        }
        if ((a[k+1][p+2]==0) && (k+1<n+1) && (p+2<n+1))
        {
            back_recursiv(k+1, p+2, ord);
            a[k+1][p+2]=0;
        }
        if ((a[k+2][p+1]==0) && (k+2<n+1) && (p+1<n+1))
        {
            back_recursiv(k+2, p+1, ord);
            a[k+2][p+1]=0;
        }
        if ((a[k+1][p-2]==0) && (k+1<n+1) && (p-2>0))
        {
            back_recursiv(k+1, p-2, ord);
            a[k+1][p-2]=0;
        }
        if ((a[k+2][p-1]==0) && (k+2<n+1) && (p-1>0))
        {
            back_recursiv(k+2, p-1, ord);
            a[k+2][p-1]=0;
        }
    }
}

int main()
{
    printf("\nOrdinul tablei de sah n=");
    scanf("%d",&n);
    int i,j;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++) a[i][j]=0;
    back_recursiv(1,1,1);
    return 0;
}
