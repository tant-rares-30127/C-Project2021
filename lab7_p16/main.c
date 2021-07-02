#include <stdio.h>
#include <stdlib.h>

typedef struct nod
{
    int cheie;
    struct nod *urm;
} NOD;

typedef struct
{
    NOD *prim, *ultim, *crt;
    int dimensiune;
} LISTA;

LISTA **citeste(int *n)
{
    LISTA **a;
    FILE *f=fopen ("graf.txt","r");
    if(f == NULL)
    {
        printf("NU s-a deschis fisierul graf.txt...");
        exit(1);
    }
    int i,j,x;
    fscanf(f,"%d",n);

    a = (LISTA **)malloc((*n+1)*sizeof(LISTA));

    for(i=1; i<=*n; i++)
    {
        *(a+i) = (LISTA *)malloc(sizeof(LISTA));
        (*(a+i))->dimensiune = 1;
        (*(a+i))->crt = (NOD *)malloc(sizeof(NOD));
        (*(a+i))->crt->cheie=i;
        (*(a+i))->crt->urm=0;
        (*(a+i))->prim = (*(a+i))->ultim =(*(a+i))->crt;;
        for(j=1; j<=*n; j++)
        {
            fscanf(f,"%d",&x);
            if (x==1)
            {
                (*(a+i))->crt = (NOD *)malloc(sizeof(NOD));
                (*(a+i))->dimensiune++;
                (*(a+i))->crt->cheie=j;
                (*(a+i))->crt->urm=0;
                (*(a+i))->ultim->urm = (*(a+i))->crt;
                (*(a+i))->ultim = (*(a+i))->crt;
            }
        }
    }
    fclose(f);
    return a;
}

void afisare(LISTA **a, int n)
{
    int i;
    printf("Continutul listei de adiacente:\n");
    for(i=1; i<=n; i++)
    {
        a[i]->crt = a[i]->prim;
        while(a[i]->crt!=0)
        {
            printf("%d ", a[i]->crt->cheie);
            a[i]->crt = a[i]->crt->urm;
        }
        printf("\n");
    }
}

void adauga( NOD **prim, NOD **ultim,int cheie)
{ /* adăugare la sfârșit */
    NOD *p = (NOD*)malloc(sizeof(NOD));
    p->cheie = cheie;
    if (*prim==0)
    {
        p->urm = 0;
        *prim = *ultim = p;
    }
    else
    {
        p->urm = *prim;
        *prim = p;
    }
}

void sterge(NOD **prim, NOD **ultim)
{ /* șterge primul nod din listă */
    NOD *p;
    if(*prim!=0)
    {
        p=*prim;
        *prim=(*prim)->urm;
        if(*prim==0)
        {
            *ultim=0;
        }
        free(p);
    }
    return;
}


void explorare_adancime(LISTA **a, int n, int s, int vizitate[n+1])
{ /* s este nodul de pornire */

    NOD *prim = 0, *ultim = 0;
    int v,w;
    vizitate[s]=1; /* se începe cu s */
    adauga(&prim, &ultim, s);
    while(prim)
    {
        v = prim->cheie;
        (*(a+v))->crt=(*(a+v))->prim;
        w=(*(a+v))->crt->cheie;
        while ((vizitate[w]!=0) && ((*(a+v))->crt!=0))
        {
            (*(a+v))->crt=(*(a+v))->crt->urm;
            if ((*(a+v))->crt!=0)
            {
                w=(*(a+v))->crt->cheie;
            }
            else w=0;
        }
        if (w!=0)
        {
            vizitate[w] = 1;
            adauga(&prim, &ultim, w);
        }
        else
        {
            sterge(&prim, &ultim);
        }
    }
    free(vizitate);
}

void afisare_traversari(LISTA **a, int n)
{
    int i, k=0;
    int vizitate[n+1];
    for(i = 1; i <= n; i++) vizitate[i]=0; /* inițializare vector vizitate cu zero */
    i=1;
    while (i<=n)
    {
        if (vizitate[i]==0)
            {
                explorare_adancime(a, n, i, vizitate);
                k++;
                for (int j=i;j<=n;j++)
                {
                    if (vizitate[j]!=0) printf("%d ", j);
                }
                printf("\n");
            }
        i++;
    }
    printf("Nr de componente conexe: %d", k);
}

int main()
{
    int n;
    LISTA **v=citeste(&n);
    afisare(v, n);
    afisare_traversari(v,n);
    return 0;
}
