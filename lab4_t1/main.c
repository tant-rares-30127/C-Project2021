#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod
{
    char *nume;
    struct nod *prec, *urm;
} NOD;

typedef struct
{
    NOD *prim, *crt;
    int dimensiune;
} LISTA;

void Citire(LISTA **d);
void Afisare(LISTA *d);
void Elimina(LISTA *d);
void Primul(LISTA *d);

int main()
{
    LISTA *d;
    Citire(&d);
    printf("Copii care se joaca sunt: \n");
    Afisare(d);
    Primul(d);
    Afisare(d);
    while(d->dimensiune!=1)
    {
        Elimina(d);
        printf("Copii ramasi sunt: \n");
        Afisare(d);
    }
    printf("Copilul castigator este: %s", d->prim->nume);

    return 0;
}

void Citire(LISTA **d)
{
    *d = (LISTA*)malloc(sizeof(LISTA));
    (*d)->prim = NULL;
    (*d)->dimensiune = 0;

    FILE *f = fopen("copii.txt", "r");
    if(!f)
    {
        printf("Nu a reusit deschiderea fisierului!");
        exit(1);
    }

    char line[200];
    while(fgets(line, sizeof(line),f))
    {
        (*d)->crt = (NOD *)malloc(sizeof(NOD));
        (*d)->crt->nume = (char*)malloc((strlen(line)+1)*sizeof(char));
        strcpy((*d)->crt->nume, line);
        (*d)->dimensiune++;
        if ((*d)->prim == NULL)
        {
            (*d)->crt->urm =(*d)->crt;
            (*d)->crt->prec=(*d)->crt;
            (*d)->prim = (*d)->crt;
        }
        else
        {
            (*d)->crt->prec=(*d)->prim->prec;
            (*d)->crt->urm=(*d)->prim;
            (*d)->prim->prec->urm=(*d)->crt;
            (*d)->prim->prec=(*d)->crt;
        }
    }
    fclose(f);
}

void Afisare(LISTA *d)
{
    d->crt = d->prim;
    for (int i=1; i<=d->dimensiune; i++)
    {
        printf("%d. %s", i, d->crt->nume);
        d->crt = d->crt->urm;
    }
    printf("\n");
}

void Elimina(LISTA *d)
{
    int m;
    printf("Al catelea copil va fi eliminat:");
    scanf("%d", &m);
    printf("\n");

    d->crt=d->prim;

    for(int i=2; i<=m; i++)
    {
        d->crt=d->crt->urm;
    }

    d->prim=d->crt->urm;
    d->crt->urm->prec=d->crt->prec;
    d->crt->prec->urm=d->crt->urm;
    d->dimensiune--;
    free(d->crt);

    return ;
}

void Primul(LISTA *d)
{
    char s[100];
    int i=1;
    printf("Copilul de la care se va incepe este:");
    gets(s);
    d->crt=d->prim;
    while ((strncmp(d->crt->nume,s,strlen(s))!=0)&&(i<=d->dimensiune))
    {
        i++;
        d->crt=d->crt->urm;
    }
    if (i>d->dimensiune)
    {
        printf("Nu exista copilul \n");
        Primul(d);
    }
    d->prim=d->crt;
}
