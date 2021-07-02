# include <stdlib.h>
# include <stdio.h>
# include <string.h>
typedef struct
{
    char *nume_med;
    float pret;
    int cantitate;
    char *data_prim;
    char *data_exp;
} MEDICAMENT;

typedef struct nod
{
    MEDICAMENT *medicament;
    struct nod *prec, *urm;
} NOD;

typedef struct
{
    NOD *prim, *ultim, *crt;
    int dimensiune;
} LISTA;

void Citire(LISTA **d);
void Afisare(LISTA *d);
void Cautamed(LISTA **d);
void Eliminamed(LISTA *d);
void Salvare(LISTA *d);
void Sortare(LISTA *d);

int main()
{
    LISTA *d;
    Citire(&d);
    Sortare(d);
    int optiune;

    while(1)
    {
        printf("1 Afisare, 2 Schimba date medicament, 3 Elimina medicament, 4 Iesire : ");
        scanf("%d", &optiune);
        switch(optiune)
        {
            case 1:
            {
                printf("\n");
                if (d->prim==0) printf("Lista goala \n");
                if (d->prim!=0) Afisare(d);
                break;
            }
            case 2:
            {
                printf("\n");
                if (d->prim==0) printf("Lista goala \n");
                if (d->prim!=0) Cautamed(&d);
                break;
            }
            case 3:
            {
                printf("\n");
                if (d->prim==0) printf("Lista goala \n");
                if (d->prim!=0) Eliminamed(d);
                break;
            }
            case 4:
            {
                printf("La revedere...");
                Salvare(d);
                return 0;
            }
            default:
            {
                printf("Optiune gresita... \n");
                printf("\n");
                break;
            }
        }
    }
    return 0;
}

void Citire(LISTA **d)
{
    *d = (LISTA*)malloc(sizeof(LISTA));
    (*d)->prim = (*d)->ultim = NULL;
    (*d)->dimensiune = 0;

    FILE *f = fopen("medicamente.txt", "r");
    if(!f) return ;

    char line[200];
    while(fgets(line, sizeof(line),f))
    {
        (*d)->crt = (NOD *)malloc(sizeof(NOD));
        (*d)->crt->medicament = (MEDICAMENT *)malloc(sizeof(MEDICAMENT));

        char *token;

        token=strtok(line, ",");
        (*d)->crt->medicament->nume_med = (char*)malloc((strlen(token)+1)*sizeof(char));
        strcpy((*d)->crt->medicament->nume_med, token);
        token=strtok(NULL, ",");

        (*d)->crt->medicament->pret=atof(token);
        token=strtok(NULL, ",");

        (*d)->crt->medicament->cantitate=atoll(token);
        token=strtok(NULL, ",");

        (*d)->crt->medicament->data_prim = (char*)malloc((strlen(token)+1)*sizeof(char));
        strcpy((*d)->crt->medicament->data_prim, token);
        token=strtok(NULL, ",");

        (*d)->crt->medicament->data_exp = (char*)malloc((strlen(token)+1)*sizeof(char));
        strcpy((*d)->crt->medicament->data_exp, token);

        (*d)->dimensiune++;
        if ((*d)->prim == NULL)
        {
            (*d)->crt->urm = 0;
            (*d)->crt->prec=0;
            (*d)->prim = (*d)->ultim = (*d)->crt;
        }
        else
        {
            (*d)->crt->urm=0;
            (*d)->crt->prec=(*d)->ultim;
            (*d)->ultim->urm = (*d)->crt;
            (*d)->ultim = (*d)->crt;
        }
    }
    fclose(f);
}

void Afisare(LISTA *d)
{
    d->crt = d->prim;
    while(d->crt!=0)
    {
        printf("Medicamentul %s care costa %.2f cantitate %d primit in %s si expira in %s", d->crt->medicament->nume_med, d->crt->medicament->pret, d->crt->medicament->cantitate, d->crt->medicament->data_prim, d->crt->medicament->data_exp);
        d->crt = d->crt->urm;
    }
    printf("\n");
}

void Cautamed(LISTA **d)
{
    char nume[200];
    float p;
    int x=0;;

    printf("Introduceti numele medicamentului: ");
    scanf("%s",nume);

    printf("Introduceti pretul medicamentului: ");
    scanf("%f",&p);

    (*d)->crt=(*d)->prim;
    while((*d)->crt)
    {
        if ((strcmp(((*d)->crt->medicament->nume_med),nume)==0) && (((*d)->crt->medicament->pret)==p))
        {
            int c;
            char date[200];
            printf("Introduceti noile date \n");
            printf("Cantitate:");
            scanf("%d", &c);
            (*d)->crt->medicament->cantitate=c;
            printf("Data primirii:");
            scanf("%s", date);
            strcpy((*d)->crt->medicament->data_prim,date);
            printf("Data expirarii:");
            scanf("%s", date);
            date[10]='\n';
            strcpy((*d)->crt->medicament->data_exp,date);
            x=1;
        }
        (*d)->crt = (*d)->crt->urm;
    }
    if (x==0) printf("Nu se gaseste medicamentul \n");

}

void Eliminamed(LISTA *d)
{
    char nume[200];
    float p;
    int x=0;

    printf("Introduceti numele medicamentului: ");
    scanf("%s",nume);

    printf("Introduceti pretul medicamentului: ");
    scanf("%f",&p);

    d->crt=d->prim;
    while ((d->crt) && (x!=1))
    {
        if ((strcmp((d->crt->medicament->nume_med),nume)==0) && ((d->crt->medicament->pret)==p))
        {
            if ((d->prim==d->crt)&&(d->ultim==d->crt))
            {
                d->prim=d->ultim=0;
                free(d->crt);
                printf("Medicamentul a fost eliminat \n");
                x=1;
                d->dimensiune--;
            }
            else
            {
                if(d->crt==d->prim)
                {
                    d->prim=d->prim->urm;
                    d->prim->prec=0;
                    free(d->crt);
                    printf("Medicamentul a fost eliminat \n");
                    x=1;
                    d->dimensiune--;
                }
                else
                {
                    if (d->crt==d->ultim)
                    {
                        d->ultim=d->ultim->prec;
                        d->ultim->urm=0;
                        free(d->crt);
                        d->dimensiune--;
                        printf("Medicamentul a fost eliminat \n");
                        x=1;
                    }
                    else
                    {
                        d->crt->urm->prec=d->crt->prec;
                        d->crt->prec->urm=d->crt->urm;
                        d->dimensiune--;
                        free(d->crt);
                        printf("Medicamentul a fost eliminat \n");
                        x=1;
                    }
                }
            }
        }
        d->crt = d->crt->urm;
    }
    if (x==0) printf("Nu se gaseste medicamentul \n");
    return ;
}

void Salvare(LISTA *d)
{
    FILE *f = fopen("output.txt", "w");
    if(!f) return;
    d->crt = d->prim;
    if (d->crt!=NULL)
    {
        while(d->crt->urm)
        {
            fprintf(f, "%s %.2f %d %s %s\n", d->crt->medicament->nume_med, d->crt->medicament->pret, d->crt->medicament->cantitate, d->crt->medicament->data_prim, d->crt->medicament->data_exp);
            d->crt=d->crt->urm;
        }
        fprintf(f, "%s %.2f %d %s %s\n", d->crt->medicament->nume_med, d->crt->medicament->pret, d->crt->medicament->cantitate, d->crt->medicament->data_prim, d->crt->medicament->data_exp);
    }
    fclose(f);
}

void Sortare(LISTA *d)
{
    int n=d->dimensiune;
    char s[n][100];
    float p[n];
    int j=0, i=0;
    d->crt=d->prim;
    while (d->crt)
    {
        strcpy(s[i], d->crt->medicament->nume_med);
        p[i]=d->crt->medicament->pret;
        i++;
        d->crt=d->crt->urm;
    }
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if (strcmp(s[i],s[j])<0)
            {
                char aux[100];
                strcpy(aux,s[i]);
                strcpy(s[i],s[j]);
                strcpy(s[j],aux);
                float x;
                x=p[i];
                p[i]=p[j];
                p[j]=x;
            }
            else
                if (strcmp(s[i],s[j])==0)
                {
                    if (p[i]>p[j])
                    {
                        char aux[100];
                        strcpy(aux,s[i]);
                        strcpy(s[i],s[j]);
                        strcpy(s[j],aux);
                        float x;
                        x=p[i];
                        p[i]=p[j];
                        p[j]=x;
                    }
                }
        }
    }
    d->crt=d->prim;
    i=0;
    while (d->crt)
    {
        strcpy(d->crt->medicament->nume_med,s[i]);
        d->crt->medicament->pret=p[i];
        i++;
        d->crt=d->crt->urm;
    }
}



