# include <stdlib.h>
# include <stdio.h>
# include <string.h>
typedef struct
{
    char *cuvant;
    int frecventa;
} DATE_UTILE;

typedef struct nod
{
    DATE_UTILE *date_utile;
    struct nod *prec, *urm;
} NOD;

typedef struct
{
    NOD *prim, *ultim, *crt;
    int dimensiune;
} LISTA;

void Creare(LISTA *l1, LISTA *l2);

void Afisare(LISTA *l, int ordine, char *mesaj); /* ordine == 0 pentru ordine crescătoare, ordine == 1 pentru ordine descrescătoare */

DATE_UTILE *Aloca_date(char *cuvant); /* alocă memorie pentru un cuvânt, inițial frcvența este 1 */

NOD *Aloca_nod(DATE_UTILE *date_utile); /* alocă memorie pentru un nod al listei dublu înlănțuite */

LISTA *Aloca_lista(); /* alocă memorie pentru structura LISTĂ, inițializează prim, ultim, dimensiune cu 0 */

void Cauta(LISTA *l, char *cuvant); /* l->crt va conține pointer către nodul ce are pointer la date utile cuvântul căutat sau NULL dacă nu există cuvântul căutat în listă */

void Adauga_ultim(LISTA *l, NOD *nod); /* adaugă nodul nod după ultimul nod din lista l */

void Insereaza_prim(LISTA *l, NOD *nod); /* inserează nodul nod înainte de primul nod din lista l */

void Insereaza(LISTA *l, NOD *nod); /* inserează nodul nod înainte de nodul curent din lista l (înainte de l->crt) */

int main()
{
    LISTA *l1 = Aloca_lista(), *l2 = Aloca_lista();
    Creare(l1, l2);
    Afisare(l1, 0, "Cuvintele în ordinea citirii");
    Afisare(l2, 0, "Cuvintele distincte în ordinea crescatoare");
    Afisare(l2, 1, "Cuvintele distincte în ordinea descrescatoare");
return 0;
}
void Creare(LISTA *l1, LISTA *l2)
{
    int i, n;
    char buf[100];
    NOD *nod;
    printf("Introduceti numarul de cuvinte ");
    scanf("%d", &n);
    for(i=1; i<=n; i++)
    {
        printf("Introduceti un cuvânt ");
        scanf("%s", buf);
        Cauta(l2, buf);
        if((l2->crt != NULL) && (strcmp(l2->crt->date_utile->cuvant, buf) == 0))
        { /* cuvântul citit există deja, nu mai trebuie alocată memorie, se crește  frecvența și se adaugă în l1 după ultim */
            l2->crt->date_utile->frecventa++;
            nod = Aloca_nod(l2->crt->date_utile);
            Adauga_ultim(l1, nod);
        }
        else
        {
            DATE_UTILE *d = Aloca_date(buf);
            nod = Aloca_nod(d);
            Adauga_ultim(l1, nod);
            nod = Aloca_nod(d);
            if((l2->dimensiune == 0) || ((l2->crt != NULL) && (l2->crt == l2->prim)))
            { /* lista poate fi vidă sau se introduce înainte de primul nod */
                Insereaza_prim(l2, nod);
            }
            else
            {
                if(l2->crt == NULL)
                {
                    Adauga_ultim(l2, nod);
                }
                else
                {
                    Insereaza(l2, nod);
                }
            }
        }
    }
}

void Afisare(LISTA *l, int ordine, char *mesaj)
{
    if(ordine == 0)
    {
        l->crt = l->prim;
    }
    else
    {
        l->crt = l->ultim;
    }
    printf("%s\n", mesaj);
    while(l->crt)
    {
        printf("%s %d\n", l->crt->date_utile->cuvant, l->crt->date_utile->frecventa);
        if(ordine == 0)
        {
            l->crt = l->crt->urm;
        }
        else
        {
            l->crt = l->crt->prec;
        }
    }
}

DATE_UTILE *Aloca_date(char *cuvant)
{
    DATE_UTILE *d = (DATE_UTILE *)malloc(sizeof(DATE_UTILE));
    d->cuvant = (char *)malloc((strlen(cuvant)+1)*sizeof(char));
    strcpy(d->cuvant, cuvant);
    d->frecventa = 1;
    return d;
}

NOD *Aloca_nod(DATE_UTILE *date_utile)
{
    NOD *nod = (NOD *)malloc(sizeof(NOD));
    nod->prec = nod->urm = NULL;
    nod->date_utile = date_utile;
    return nod;
}

LISTA *Aloca_lista()
{
    LISTA *l = (LISTA *)malloc(sizeof(LISTA));
    l->prim = l->ultim = NULL;
    return l;
}

void Cauta(LISTA *l, char *cuvant)
{
    int fan;
    l->crt = l->prim;
    while(l->crt)
    {
        fan = strcmp(cuvant, l->crt->date_utile->cuvant);
        /* fan == 0 înseamnă cuvântul există în listă, fan > 0 înseamnă cuvântul citit este mai mare decât cuvântul din nodul curent, fan < 0 înseamnă cuvântul citit este mai mic decât cuvântul din nodul curent */
        if((fan == 0) || (fan < 0))
        {
            return;
        }
        else
        {
            l->crt = l->crt->urm;
        }
    }
}

void Adauga_ultim(LISTA *l, NOD *nod)
{
    l->dimensiune++;
    nod->prec = l->ultim;
    if(l->ultim != NULL)
    { /* lista nu este vidă */
        l->ultim->urm = nod;
        l->ultim = nod;
    }
    else
    { /* nodul nod este primul introdus în listă */
        l->prim = l->ultim = nod;
    }
}
void Insereaza_prim(LISTA *l, NOD *nod)
{
    l->dimensiune++;
    nod->urm = l->prim;
    if(l->prim != NULL)
    { /* lista nu este vidă */
        l->prim->prec = nod;
        l->prim = nod;
    }
    else
    { /* nodul nod este primul introdus în listă */
        l->prim = l->ultim = nod;
    }
}

void Insereaza(LISTA *l, NOD *nod)
{
    l->dimensiune++;
    nod->prec = l->crt->prec;
    nod->urm = l->crt;
    if (l->crt->prec != 0)
    {
        l->crt->prec->urm = nod;
    }
    l->crt->prec = nod;
    if (l->crt == l->prim)
    {
        l->prim = nod;
    }
}
