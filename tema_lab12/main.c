#include <stdio.h>
#include <stdlib.h>
#define inf 100

int ** citire(int *n)
{
    int **a;
    FILE *f=fopen ("tabla.txt","r");
    if(f == NULL)
    {
        printf("NU s-a deschis fisierul graf.txt...");
        exit(1);
    }
    int i, j;
    fscanf(f,"%d",n);
    a = (int **)malloc((*n+1)*sizeof(int));
    for(i=1; i<=*n; i++)
    {
        *(a+i) = (int *)malloc((*n+1)*sizeof(int));
        for(j=1; j<=*n; j++)
        {
            fscanf(f, "%d", &a[i][j]);
        }
    }
    fclose(f);
    return a;
}

void afisare(int **a, int n)
{
    int i, j;
    printf("Tabla PERSPICO:\n");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++) printf("%2d ", a[i][j]);
        printf("\n");
    }
}

int cost(int **a, int n)
{
    int i, j;
    int m=1, c=0;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
        {
            if (a[i][j]!=m) c++;
            m++;
        }

    return c;
}

void cauta_poz(int **a, int n, int *o, int *p)
{
    int i,j;
    for (i=1; i<=n; i++)
        for (j=1; j<=n; j++)
            if (a[i][j]==16)
            {
                *o=i;
                *p=j;
                return;
            }

}

void perspico(int **a, int n)
{
    int c=cost(a,n);
    int o,p,sus,drp,jos,stg;
    int x;
    while (c!=0)
    {
        cauta_poz(a,n,&o,&p);
        if (o-1<1)
        {
            sus=inf;
            printf("Cost=INF \n");
        }
        else
        {
            x=a[o-1][p];
            a[o-1][p]=a[o][p];
            a[o][p]=x;
            sus=cost(a,n);
            printf("Cost=%d \n", sus);
            if (c>sus) c=sus;
            else
            {
                x=a[o-1][p];
                a[o-1][p]=a[o][p];
                a[o][p]=x;
            }
        }
        if (p+1>n)
        {
            drp=inf;
            printf("Cost=INF \n");
        }
        else
        {
            x=a[o][p+1];
            a[o][p+1]=a[o][p];
            a[o][p]=x;
            drp=cost(a,n);
            printf("Cost=%d \n", drp);
            if (c>drp) c=drp;
            else
            {
                x=a[o][p+1];
                a[o][p+1]=a[o][p];
                a[o][p]=x;
            }
        }
        if (o+1>n)
        {
            jos=inf;
            printf("Cost=INF \n");
        }
        else
        {
            x=a[o+1][p];
            a[o+1][p]=a[o][p];
            a[o][p]=x;
            jos=cost(a,n);
            printf("Cost=%d \n", jos);
            if (c>jos) c=jos;
            else
            {
                x=a[o+1][p];
                a[o+1][p]=a[o][p];
                a[o][p]=x;
            }
        }
        if (p-1<1)
        {
            stg=inf;
            printf("Cost=INF \n");
        }
        else
        {
            x=a[o][p-1];
            a[o][p-1]=a[o][p];
            a[o][p]=x;
            stg=cost(a,n);
            printf("Cost=%d \n \n", stg);
            if (c>stg) c=stg;
            else
            {
                x=a[o][p-1];
                a[o][p-1]=a[o][p];
                a[o][p]=x;
            }
        }
        afisare(a,n);
    }
}

int main()
{
    int n, **tabla = citire(&n);
    afisare(tabla,n);
    perspico(tabla,n);
    return 0;
}
