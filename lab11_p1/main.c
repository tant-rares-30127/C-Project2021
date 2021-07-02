#include <stdio.h>
#include <stdlib.h>

int ** citire(int *n)
{
    int **a;
    FILE *f=fopen ("vectori.txt","r");
    if(f == NULL)
    {
        printf("NU s-a deschis fisierul vectori.txt...");
        exit(1);
    }
    int i, j;
    fscanf(f,"%d",n);
    a = (int **)malloc((*n+1)*sizeof(int));
    for(i=1; i<=*n; i++)
    {
        int m;
        fscanf(f,"%d", &m);
        *(a+i) = (int *)malloc((m+1)*sizeof(int));
        a[i][0]=m;
        for(j=1; j<=m; j++)
        {
            fscanf(f, "%d", &a[i][j]);
        }
    }
    return a;
}

void afisare(int **a, int n)
{
    int i, j;
    printf("Vectori:\n");
    for(i=1; i<=n; i++)
    {
        int m=a[i][0];
        printf("%d \n", m);
        for(j=1; j<=m; j++) printf("%d ", a[i][j]);
        printf("\n");
    }
}

void interclasare_vect(int x[], int *v, int p, int *m)
{
    int i, j=1;
    int y[*m];
    for (i=1; i<=*m; i++)
    {
        y[i]=v[i];
    }
    int k=*m;
    *m=0;
    for(i=1;i<=k;i++)
    {
        printf("%d ",y[i]);
    }
    printf("\n");
    for(i=1;i<=p;i++)
    {
        printf("%d ",x[i]);
    }
    printf("\n");
    i=1;
    while ((i<=p) && (j<=k))
    {
        (*m)++;
        if(x[i]>=y[j])
        {
            v[*m]=y[j];
            j++;
        }
        else
        {
            v[*m]=x[i];
            i++;
        }
    }
   while (i<=p)
   {
       (*m)++;
       v[*m]=x[i];
       i++;
   }
   while (j<=k)
   {
        (*m)++;
        v[*m]=y[j];
        j++;
   }
}

int *interclasare(int **a, int n, int *m)
{
    int i;
    for (i=1; i<=n; i++)
    {
        *m=*m+a[i][0];
    }
    int *v;
    v=(int *)malloc((*m)*sizeof(int));
    for (i=1; i<=(*m); i++)
    {
        v[i]=0;
    }
    int p=a[1][0];
    for (int j=1; j<=p; j++)
    {
        v[j]=a[1][j];
    }
    *m=p;
    for(i=2; i<=n; i++)
    {
        int p=a[i][0];
        int x[p];
        for (int j=1; j<=p; j++)
        {
            x[j]=a[i][j];
        }
        interclasare_vect(x,v,p,m);
    }
    return v;
}

int main()
{
    int n, m=0;
    int **a=citire(&n);
    afisare(a, n);
    int *v=interclasare(a,n,&m);
    for (int i=1; i<=m; i++) printf("%d ", v[i]);
    return 0;
}
