#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tip_nod
{
    char c;
    struct tip_nod *st, *dr;
} TIP_NOD;

typedef struct nod_lista
{
    TIP_NOD *continut;
    struct nod_lista *urm;
} NOD_LISTA;

void citire(char s[])
{
    FILE *f = fopen("input.txt", "r");
    if(!f)
    {
        printf("Fisierul input.txt nu a fost deschis...");
        exit(1);
    }
    fgets(s, 100, f);
    fclose(f);
}

void push(NOD_LISTA **prim, TIP_NOD *nod_arbore)
{
    NOD_LISTA * p = (NOD_LISTA *)malloc(sizeof(NOD_LISTA));
    p->continut = nod_arbore;
    p->urm = NULL;
    if (*prim == 0)
    {
        *prim = p;
    }
    else
    {
        p->urm = *prim;
        *prim = p;
    }
}

TIP_NOD *pop(NOD_LISTA **prim)
{
    TIP_NOD *nod_arbore = NULL;
    NOD_LISTA *p;
    if(*prim != NULL)
    {
        p = *prim;
        *prim = (*prim)->urm;
        nod_arbore = p->continut;
        free(p);
    }
return nod_arbore;
}

TIP_NOD *creare_nod(char c)
{
    TIP_NOD *nod_arbore = (TIP_NOD *)malloc(sizeof(TIP_NOD));
    nod_arbore->c = c;
    nod_arbore->st = nod_arbore->dr = NULL;
    return nod_arbore;
}

TIP_NOD *prelucrare(char s[])
{
    NOD_LISTA *prim = NULL;
    TIP_NOD *nod_arbore, *nod_arbore1, *nod_arbore2;
    int i;
    for(i=0; i<strlen(s)-1; i++)
    {
        switch(s[i])
        {
            case '+': case '-': case '*': case '/':
            {
                nod_arbore1 = pop(&prim);
                nod_arbore2 = pop(&prim);
                nod_arbore = creare_nod(s[i]);
                nod_arbore->st = nod_arbore1;
                nod_arbore->dr = nod_arbore2;
                push(&prim, nod_arbore);
                break;
            }
            case ' ':
            {
                break;
            }
            default:
            {
                nod_arbore = creare_nod(s[i]);
                push(&prim, nod_arbore);
                break;
            }
        }
    }
    return nod_arbore = pop(&prim);
}

void inordine(TIP_NOD *p, int nivel)
{
    int i;
    if (p != 0)
    {
        inordine(p->st, nivel+1);
        for(i = 0; i <= nivel; i++) printf(" ");
        printf("%c \n", p->c);
        inordine(p->dr, nivel+1);
    }
}
int main()
{
    char s[100];
    TIP_NOD *radacina;
    citire(s);
    radacina = prelucrare(s);
    inordine(radacina, 0);
    return 0;
}
