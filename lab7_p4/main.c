#include <stdio.h>
#include <stdlib.h>
typedef struct nod
{
    int cheie;
    struct nod *urm;
} NOD;

void adauga( NOD **prim, NOD **ultim,int cheie)
{ /* adăugare la sfârșit */
    NOD *p = (NOD*)malloc(sizeof(NOD));
    p->cheie = cheie;
    p->urm = 0;
    if (*prim==0)
    {
        *prim = *ultim = p;
    }
    else
    {
        (*ultim)->urm = p;
        *ultim = p;
    }
}

int sterge(NOD **prim, NOD **ultim)
{ /* șterge primul nod din listă */
    NOD *p;
    int cheie=0;
    if(*prim!=0)
    {
        p=*prim;
        *prim=(*prim)->urm;
        cheie = p->cheie;
        if(*prim==0)
        {
            *ultim=0;
        }
        free(p);
    }
    return cheie;
}

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

void explorare_largime(int **a, int n, int s)
{ /* s = nod de plecare */
    int *vizitate = (int *)malloc((n+1)*sizeof(int));
    int *tata = (int *)malloc((n+1)*sizeof(int));
    NOD *prim = 0, *ultim = 0;
    int i, v, w;
    for (i=1; i<=n; i++)
    {
        vizitate[i] = 0;
    }
    for (i=1; i<=n; i++)
    {
        tata[i] = 0;
    }
    adauga(&prim, &ultim, s);
    vizitate[s] = 1;
    while (prim)
    {
        v = sterge(&prim, &ultim);
        for (i=1; i<=n; i++)
        {
            if((a[v][i]==1) && (vizitate[i]==0))
            {
                w = i;
                adauga(&prim, &ultim, w);
                vizitate[w] = 1;
                tata[w]=v;
            }
        }
    }
    int e, aux;
    printf("Nodul la care se ajunge:");
    scanf("%d", &e);
    aux=e;
    int vec[n+1];
    int m=0;
    while (tata[aux]!=0)
    {
        m++;
        vec[m]=aux;
        aux=tata[aux];
    }
    if (m!=0)
    {
        m++;
        vec[m]=aux;
    }
    else printf("Nu exista drum");
    for(i=m; i>=1; i--) printf("%d ", vec[i]);
    free(vizitate);
}

void drum(int **a, int n)
{
    int s;
    printf("Nodul de plecare:");
    scanf("%d",&s);
    explorare_largime(a, n, s);
}

int main()
{
    int n, **a = citire(&n);
    afisare(a, n);
    drum(a, n);
    return 0;
}
