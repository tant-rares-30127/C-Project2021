#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tip_nod
{
    int x;
    struct tip_nod *st, *dr;
} TIP_NOD;

typedef struct tip_nod2
{
    int x;
    int n;
    struct tip_nod2 **v;
} TIP_NOD2;


typedef struct nod_lista
{
    TIP_NOD *continut;
    struct nod_lista *urm;
} NOD_LISTA;

TIP_NOD *construire()
{
    TIP_NOD *p = NULL;
    int d;
    printf("Valoare nodului actual:");
    scanf("%d", &d);
    if(d!=0)
    {
        p=(TIP_NOD *)malloc(sizeof(TIP_NOD));
        p->x= d;
        p->st = construire( );
        p->dr = construire( );
    }
    return p;
}

TIP_NOD *construire_echilibrat(int nr_noduri)
{
    TIP_NOD *p = NULL;
    int n_st, n_dr;
    if(nr_noduri != 0)
    {
        n_st = nr_noduri/2; /* numărul nodurilor din subarborele stâng */
        n_dr = nr_noduri - n_st - 1; /* ~ drept */
        p = (TIP_NOD *)malloc(sizeof(TIP_NOD));
        printf("Introduceti informatia din nod in preordine ");
        scanf("%d", &(p->x));
        p->st = construire_echilibrat(n_st);
        p->dr = construire_echilibrat(n_dr);
    }
    return p;
}

TIP_NOD2 *construire_oarecare()
{
    TIP_NOD2 *p = NULL;
    int n,d;
    printf("Valoarea nodului actual:");
    scanf("%d", &d);
    p=(TIP_NOD2 *)malloc(sizeof(TIP_NOD2));
    p->x= d;
    printf("Nr de fii pt nod:");
    scanf("%d",&n);
    p->n=n;
    p->v=(TIP_NOD2 **)malloc(sizeof(TIP_NOD2*)*n);
    for(int i=1;i<=n;i++)
    {
        p->v[i]=construire_oarecare();
    }
    return p;
}

void preordine(TIP_NOD *p, int nivel)
{
    int i;
    if (p != 0)
    {
        /*tipărire spații variabile funcție de nivel, pentru indentare*/
        for(i = 0; i <= nivel; i++) printf(" ");
        printf("%d\n", p->x); /*prelucrare nod curent*/
        preordine(p->st, nivel+1);
        preordine(p->dr, nivel+1);
    }
}

void inordine(TIP_NOD *p, int nivel)
{
    int i;
    if (p != 0)
    {
        inordine(p->st, nivel+1);
        /*tipărire spații variabile funcție de nivel, pentru indentare*/
        for(i = 0; i <= nivel; i++) printf(" ");
        printf("%d\n", p->x); /*prelucrare nod curent*/
        inordine(p->dr, nivel+1);
    }
}

void postordine(TIP_NOD *p, int nivel)
{
    int i;
    if (p != 0)
    {
        postordine(p->st, nivel+1);
        postordine(p->dr, nivel+1);
        /*tipărire spații variabile funcție de nivel, pentru indentare*/
        for(i = 0; i <= nivel; i++) printf(" ");
        printf("%d\n", p->x); /*prelucrare nod curent*/
    }
}

void preordine_oarecare(TIP_NOD2 *p, int nivel)
{
    int i;
    if (p != 0)
    {
        printf("%d\n", p->x);
        for (int j=1; j<=p->n; j++)
        {
            /*tipărire spații variabile funcție de nivel, pentru indentare*/
            for(i = 0; i <= nivel; i++) printf(" ");
            preordine_oarecare(p->v[j], nivel+1);
        }
    }
}

int main()
{
    TIP_NOD *radacina1, *radacina2;
    TIP_NOD2 *radacina3;
    int n;

    radacina1 = construire();
    inordine(radacina1,0);
    printf("\n");

    printf("Introduceti nr de noduri pt arbore echilibrat:");
    scanf("%d", &n);
    radacina2=construire_echilibrat(n);
    printf("\n");

    inordine(radacina2,0);
    radacina3=construire_oarecare();
    preordine_oarecare(radacina3,0);

    return 0;
}
