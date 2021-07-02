#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod
{
    int cheie;
    char *car;
    struct nod *urm;
} NOD;

typedef struct
{
    NOD *prim, *ultim, *crt;
    int dimensiune;
} LISTA;

void Citire(LISTA **a, LISTA **b);
void Afisare(LISTA *d);
void Interclasare(LISTA *a, LISTA *b, LISTA **c);

int main()
{
    LISTA *a, *b, *c;
    Citire(&a, &b);
    printf("Lista 1: \n");
    Afisare(a);
    printf("Lista 2: \n");
    Afisare(b);
    Interclasare(a,b,&c);
    printf("Lista interclasata: \n");
    Afisare(c);
    return 0;
}

void Citire(LISTA **a, LISTA **b)
{
    *a = (LISTA*)malloc(sizeof(LISTA));
    *b = (LISTA*)malloc(sizeof(LISTA));
    (*a)->prim = (*a)->ultim = NULL;
    (*b)->prim = (*b)->ultim = NULL;
    FILE *f = fopen("interclasare.txt", "r");
    if(!f) return;
    char buf[100];
    fscanf(f, "%d", &(*a)->dimensiune);
    fscanf(f, "%d", &(*b)->dimensiune);
    for (int i=1; i<=(*a)->dimensiune; i++)
    {
        (*a)->crt = (NOD *)malloc(sizeof(NOD));
        fscanf(f, "%d", &((*a)->crt->cheie));
        fscanf(f, "%s", buf);
        (*a)->crt->car = (char*)malloc((strlen(buf)+1)*sizeof(char));
        strcpy((*a)->crt->car, buf);
        (*a)->crt->urm = 0;
        if ((*a)->prim == NULL)
        {
            (*a)->prim = (*a)->ultim = (*a)->crt;
        }
        else
        {
            (*a)->ultim->urm = (*a)->crt;
            (*a)->ultim = (*a)->crt;
        }
    }
    for (int i=1; i<=(*b)->dimensiune; i++)
    {
        (*b)->crt = (NOD *)malloc(sizeof(NOD));
        fscanf(f, "%d", &((*b)->crt->cheie));
        fscanf(f, "%s", buf);
        (*b)->crt->car = (char*)malloc((strlen(buf)+1)*sizeof(char));
        strcpy((*b)->crt->car, buf);
        (*b)->crt->urm = 0;
        if ((*b)->prim == NULL)
        {
            (*b)->prim = (*b)->ultim = (*b)->crt;
        }
        else
        {
            (*b)->ultim->urm = (*b)->crt;
            (*b)->ultim = (*b)->crt;
        }
    }
    fclose(f);
}

void Afisare(LISTA *d)
{
    d->crt = d->prim;
    while(d->crt)
    {
        printf("%d %s ", d->crt->cheie, d->crt->car);
        d->crt = d->crt->urm;
    }
    printf("\n");
}

void Interclasare(LISTA *a, LISTA *b, LISTA **c)
{
    a->crt=a->prim;
    b->crt=b->prim;
    *c = (LISTA*)malloc(sizeof(LISTA));
    (*c)->prim = (*c)->ultim = NULL;
    while((a->crt)&&(b->crt))
    {
            if (a->crt->cheie==b->crt->cheie)
            {
                if(strcmp(a->crt->car,b->crt->car)>0)
                {
                    (*c)->crt = (NOD *)malloc(sizeof(NOD));
                    (*c)->crt->cheie=b->crt->cheie;
                    (*c)->crt->car = (char*)malloc((strlen(b->crt->car)+1)*sizeof(char));
                    strcpy((*c)->crt->car, b->crt->car);
                    (*c)->crt->urm = 0;
                    if ((*c)->prim == NULL)
                    {
                        (*c)->prim = (*c)->ultim = (*c)->crt;
                    }
                    else
                    {
                        (*c)->ultim->urm = (*c)->crt;
                        (*c)->ultim = (*c)->crt;
                    }
                    b->crt=b->crt->urm;
                }
                else
                {
                    (*c)->crt = (NOD *)malloc(sizeof(NOD));
                    (*c)->crt->cheie=a->crt->cheie;
                    (*c)->crt->car = (char*)malloc((strlen(a->crt->car)+1)*sizeof(char));
                    strcpy((*c)->crt->car, a->crt->car);
                    (*c)->crt->urm = 0;
                    if ((*c)->prim == NULL)
                    {
                        (*c)->prim = (*c)->ultim = (*c)->crt;
                    }
                    else
                    {
                        (*c)->ultim->urm = (*c)->crt;
                        (*c)->ultim = (*c)->crt;
                    }
                    a->crt=a->crt->urm;
                }
            }
            else
            {
            if (a->crt->cheie>b->crt->cheie)
            {
                (*c)->crt = (NOD *)malloc(sizeof(NOD));
                (*c)->crt->cheie=b->crt->cheie;
                (*c)->crt->car = (char*)malloc((strlen(b->crt->car)+1)*sizeof(char));
                strcpy((*c)->crt->car, b->crt->car);
                (*c)->crt->urm = 0;
                if ((*c)->prim == NULL)
                {
                    (*c)->prim = (*c)->ultim = (*c)->crt;
                }
                else
                {
                    (*c)->ultim->urm = (*c)->crt;
                    (*c)->ultim = (*c)->crt;
                }
                b->crt=b->crt->urm;
            }
            else
            {
                (*c)->crt = (NOD *)malloc(sizeof(NOD));
                (*c)->crt->cheie=a->crt->cheie;
                (*c)->crt->car = (char*)malloc((strlen(a->crt->car)+1)*sizeof(char));
                strcpy((*c)->crt->car, a->crt->car);
                (*c)->crt->urm = 0;
                if ((*c)->prim == NULL)
                {
                    (*c)->prim = (*c)->ultim = (*c)->crt;
                }
                else
                {
                    (*c)->ultim->urm = (*c)->crt;
                    (*c)->ultim = (*c)->crt;
                }
                a->crt=a->crt->urm;
            }
            }
    }
    while(a->crt)
    {
        (*c)->crt = (NOD *)malloc(sizeof(NOD));
        (*c)->crt->cheie=a->crt->cheie;
        (*c)->crt->car = (char*)malloc((strlen(a->crt->car)+1)*sizeof(char));
        strcpy((*c)->crt->car, a->crt->car);
        (*c)->crt->urm = 0;
        if ((*c)->prim == NULL)
        {
            (*c)->prim = (*c)->ultim = (*c)->crt;
        }
        else
        {
            (*c)->ultim->urm = (*c)->crt;
            (*c)->ultim = (*c)->crt;
        }
        a->crt=a->crt->urm;
    }
    while(b->crt)
    {
        (*c)->crt = (NOD *)malloc(sizeof(NOD));
        (*c)->crt->cheie=b->crt->cheie;
        (*c)->crt->car = (char*)malloc((strlen(b->crt->car)+1)*sizeof(char));
        strcpy((*c)->crt->car, b->crt->car);
        (*c)->crt->urm = 0;
        if ((*c)->prim == NULL)
        {
            (*c)->prim = (*c)->ultim = (*c)->crt;
        }
        else
        {
            (*c)->ultim->urm = (*c)->crt;
            (*c)->ultim = (*c)->crt;
        }
        b->crt=b->crt->urm;
    }
}










