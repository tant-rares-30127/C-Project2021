#include <stdio.h>
#include <stdlib.h>

int ** citire(int *n)
{
    int **a;
    FILE *f=fopen ("graf.txt","r");
    if(f == NULL)
    {
        printf("NU s-a deschis fisierul graf.txt...");
        exit(1);
    }
    int i,j;
    fscanf(f,"%d",n);
    a = (int **)malloc((*n+1)*sizeof(int));
    for(i=1; i<=*n; i++)
    {
        *(a+i) = (int *)malloc((*n+1)*sizeof(int));
        for(j=1; j<=*n; j++)
        {
            a[i][j] = 0;
        }
    }
    while(!feof(f))
    {
        i = j = 0;
        fscanf(f,"%d%d", &i, &j);
        if(i>0 && i<=*n && j>0 && j<=*n)
        {
            a[i][j] = 1;
        }
    }
    fclose(f);
    return a;
}

void afisare(int **a, int n)
{
    int i, j;
    printf("Continutul matricei de adiacente:\n");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
        {
            printf("%2d ", a[i][j]);
        }
        printf("\n");
    }
}

int ham(int i, int n, int viz[n+1], int **a, int elem[n+1], int m)
{
    int j=1;
    int cap=0;
    while ((j<=n)&&(cap==0))
    {
        if (a[i][j]==1)
        {
            m++;
            elem[m]=j;
            viz[j]=1;
            int s=0;
            for (int k=1; k<=n; k++)
            {
                if (viz[k]==1) {s=s+1;}
            }
            if (s==n) cap=1;
            else ham(j,n,viz,a,elem,m);
        }
        viz[j]=0;
        j++;
    }
    return cap;
}

int main()
{
    int n, **a = citire(&n);
    int viz[n+1];
    int elem[n+1];
    int m=0;
    afisare(a, n);
    int i, sem=0;
    for (i=1; i<=n; i++) viz[i]=0;
    i=1;
    while ((i<=n)&&(sem==0))
    {
        viz[i]=1;
        m++;
        elem[m]=i;
        sem=ham(i,n,viz,a,elem,m);
        i++;
    }
    for (i=1; i<=n; i++) printf("%d ", viz[i]);
    printf("\n");
    for (i=1; i<=n; i++) printf("%d ", elem[i]);
    return 0;
}
