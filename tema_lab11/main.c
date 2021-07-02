#include <stdio.h>
#include <stdlib.h>

void afisare(int *a, int n)
{
    for (int i=1; i<=n; i++)
    {
        printf("%3d ", a[i]);
    }
    printf("\n");
}

void greedy(int *g, int *c, int n, int gmax)
{
    float v_g[n+1];
    int i,j,castig;
    int x;

    for (i=1; i<=n; i++)
    {
        v_g[i]=(float)c[i]/g[i];
    }

    printf("Vectorul cu raportul vi/gi=>");
    for (i=1; i<=n; i++)
    {
        printf("%2.1f ",v_g[i]);
    }
    printf("\n");

    for (i=1; i<=n; i++)
    {
        for (j=1; j<=n; j++)
        if (v_g[i]>=v_g[j])
        {
            float aux;
            aux=v_g[i];
            v_g[i]=v_g[j];
            v_g[j]=aux;
            x=g[i];
            g[i]=g[j];
            g[j]=x;
            x=c[i];
            c[i]=c[j];
            c[j]=x;
        }
    }

    castig=0; x=gmax;
    for (i=1; i<=n; i++)
    {
        if (g[i]<=x)
        {
            x=x-g[i];
            castig=castig+c[i];
        }
    }
    printf("Castigul pentru materiale luat in intregime este de: %d \n", castig);

    castig=0; x=gmax;
    for (i=1; i<=n; i++)
    {
        if (g[i]<=x)
        {
            x=x-g[i];
            castig=castig+c[i];
        }
        else
        {
            castig=castig+x*v_g[i];
            x=0;
        }
    }
    printf("Castigul pentru fractiuni de material este de: %d \n", castig);
}


int main()
{
    int *g, *c;
    int n, gmax;

    FILE *f=fopen("obiecte.txt", "r");
    if(!f)
    {
        printf("NU s-a deschis fisierul studenti.txt...");
        exit(1);
    }

    fscanf(f, "%d %d", &n, &gmax);
    g=(int*)malloc(sizeof(int)*(n+1));
    c=(int*)malloc(sizeof(int)*(n+1));
    for (int i=1; i<=n; i++)
    {
        fscanf(f, "%d %d", &g[i], &c[i]);
    }
    fclose(f);

    printf("Greutatea maxima: %d\n", gmax);
    printf("Vectorul de greutati=>");
    afisare(g,n);
    printf("Vectorul de valori=>  ");
    afisare(c,n);

    greedy(g,c,n,gmax);

    return 0;
}
