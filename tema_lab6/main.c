#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tip_nod
{
    char *nume_med;
    float pret;
    int cantitate;
    char *data_prim;
    char *data_exp;
struct tip_nod *st,*dr;
} TIP_NOD;

void afisare(TIP_NOD *p)
{
    if (p!=0)
    {
        afisare(p->st);
        printf("%s %.2f %d %s %s \n", p->nume_med, p->pret, p->cantitate, p->data_prim, p->data_exp);
        afisare(p->dr);
    }
}

void inserare(TIP_NOD **rad, char *token1,char *token2,char *token3,char *token4,char *token5)
{
    TIP_NOD *p, *q;
    int cmp;
    p = (TIP_NOD *)malloc(sizeof(TIP_NOD));
    p->nume_med = (char *)malloc((strlen(token1)+1)*sizeof(char));
    strcpy(p->nume_med, token1);
    p->pret=atof(token2);
    p->cantitate=atoll(token3);
    p->data_prim = (char *)malloc((strlen(token4)+1)*sizeof(char));
    strcpy(p->data_prim, token4);
    p->data_exp = (char *)malloc((strlen(token5)+1)*sizeof(char));
    strcpy(p->data_exp, token5);
    p->data_exp[10]='\0';
    p->st = p->dr = 0;
    if(*rad==0)
    {
        *rad = p;
        return;
    }
    q = *rad;
    for(;;)
    {
        cmp = strcmp(token1, q->nume_med);
        if (cmp < 0)
        {
            if(q->st == 0)
            {
                q->st = p;
                return;
            }
            else
            {
                q = q->st;
            }
        }
        else
        {
            if(cmp > 0)
            {
                if(q->dr == 0)
                {
                    q->dr=p;
                    return;
                }
                else
                {
                    q=q->dr;
                }
            }
        }
    }
}

void cautaremed(TIP_NOD *rad)
{
    TIP_NOD *p;
    int cmp;
    char med[100];
    p = rad;
    printf("Medicamentul a carui pret trebuie schimbat este:");
    gets(med);
    gets(med);
    while(p != 0)
    {
        cmp = strcmp(med, p->nume_med);
        if(cmp == 0)
        {
            float pret;
            printf("Medicamentul a fost gasit, actualizati pretul:");
            scanf("%f", &pret);
            p->pret=pret;
            return;
        }
        else
        {
            if(cmp < 0) p=p->st;
            else p=p->dr;
        }
    }
    printf("NU exista medicamentul cautat... \n");
}

void citire(TIP_NOD **rad)
{
    FILE *f = fopen("medicament.txt", "r");
    if(!f)
    {
        printf("NU s-a deschis fisierul input.txt...");
        getch();
        exit(1);
    }
    char line[100];
    while(fgets(line, sizeof(line),f))
    {
        char *token1;
        char *token2;
        char *token3;
        char *token4;
        char *token5;

        token1=strtok(line, ", ");
        token2=strtok(NULL, ", ");
        token3=strtok(NULL, ", ");
        token4=strtok(NULL, ", ");
        token5=strtok(NULL, ", ");
        inserare(rad,token1,token2,token3,token4,token5);
    }
    fclose(f);
}

TIP_NOD *stergere_nod(TIP_NOD *rad)
{
    TIP_NOD *p, *tata_p;
    /* p este nodul de șters, iar tata_p este tatăl lui */
    TIP_NOD *nod_inlocuire, *tata_nod_inlocuire;
    /* nodul care il va inlocui pe p și tatăl său */
    int directie; /* st=1, dr=2 */
    char med[100];
    if(rad == NULL) return NULL; /* arborele este vid */
    p = rad;
    tata_p = NULL;
    printf("Medicamentul care trebuie eliminat este:");
    gets(med);
    gets(med);
    while((p != NULL) && (strcmp(p->nume_med,med)!=0))
    {
        if (strcmp(p->nume_med,med)>0)
        { /* căutare în stânga */
            tata_p = p;
            p = p->st;
            directie = 1;
        }
        else
        { /* căutare în dreapta */
            tata_p = p;
            p = p->dr;
            directie = 2;
        }
    }
    if(p == NULL)
    {
        printf("\nNU EXISTA MEDICAMENTUL %s\n\n", med);
        return rad;
    }
    if(p->st == NULL) nod_inlocuire = p->dr; /* nodul de șters p nu are fiu stâng */
    else
        if(p->dr == NULL) nod_inlocuire = p->st; /* nodul de șters p nu are fiu drept */
        else
        { /* nodul de șters p are fiu stâng și fiu drept */
            tata_nod_inlocuire = p;
            nod_inlocuire = p->dr; /* se caută în subarborele drept */
            while(nod_inlocuire->st != NULL)
            {
                tata_nod_inlocuire = nod_inlocuire;
                nod_inlocuire = nod_inlocuire->st;
            }
            if(tata_nod_inlocuire != p)
            {
                tata_nod_inlocuire->st = nod_inlocuire->dr;
                nod_inlocuire->dr = p->dr;
            }
            nod_inlocuire->st = p->st;
        }
    free(p);
    printf("\nMedicamentul %s a fost eliminat!\n\n", med);
    if(tata_p == NULL) return nod_inlocuire; /* s-a șters chiar rădăcina inițială */
    else
    {
        if (directie == 1) tata_p->st = nod_inlocuire;
        else tata_p->dr = nod_inlocuire;
        return rad;
    }
}

void inserare2(TIP_NOD **rad, char *token1,float token2,int token3,char *token4,char *token5)
{
    TIP_NOD *p, *q;
    int cmp;
    p = (TIP_NOD *)malloc(sizeof(TIP_NOD));
    p->nume_med = (char *)malloc((strlen(token1)+1)*sizeof(char));
    strcpy(p->nume_med, token1);
    p->pret=token2;
    p->cantitate=token3;
    p->data_prim = (char *)malloc((strlen(token4)+1)*sizeof(char));
    strcpy(p->data_prim, token4);
    p->data_exp = (char *)malloc((strlen(token5)+1)*sizeof(char));
    strcpy(p->data_exp, token5);
    p->data_exp[10]='\0';
    p->st = p->dr = 0;
    if(*rad==0)
    {
        *rad = p;
        return;
    }
    q = *rad;
    for(;;)
    {
        cmp = strcmp(token1, q->nume_med);
        if (cmp < 0)
        {
            if(q->st == 0)
            {
                q->st = p;
                return;
            }
            else
            {
                q = q->st;
            }
        }
        else
        {
            if(cmp > 0)
            {
                if(q->dr == 0)
                {
                    q->dr=p;
                    return;
                }
                else
                {
                    q=q->dr;
                }
            }
        }
    }
}

void creare(TIP_NOD *p,TIP_NOD **q, char s[15])
{
    if (p!=0)
    {
        creare(p->st, q, s);
        char v1[15], v2[15];
        char *z1;
        char *l1;
        char *a1;
        char *z2;
        char *l2;
        char *a2;
        strcpy(v1,p->data_exp);
        z1=strtok(v1,".");
        l1=strtok(NULL,".");
        a1=strtok(NULL,".");
        strcpy(v2,s);
        z2=strtok(v2,".");
        l2=strtok(NULL,".");
        a2=strtok(NULL,".");
        if (strcmp(a1,a2)==0)
        {
            if (strcmp(l1,l2)==0)
            {
                if (strcmp(z1,z2)<0)
                {
                    inserare2(q,p->nume_med,p->pret,p->cantitate,p->data_prim,p->data_exp);
                }
            }
            else
            {
                if (strcmp(l1,l2)<0)
                {
                   // printf(". \n");
                    inserare2(q,p->nume_med,p->pret,p->cantitate,p->data_prim,p->data_exp);
                }
            }
        }
        else
        {
            if (strcmp(a1,a2)<0)
            {
               // printf(". \n");
                inserare2(q,p->nume_med,p->pret,p->cantitate,p->data_prim,p->data_exp);
            }
        }
        creare(p->dr, q, s);
    }
}

void stergere_arbore(TIP_NOD *rad)
{
    if (rad !=0)
    {
        stergere_arbore (rad->st);
        stergere_arbore (rad->dr);
        free (rad);
    }
}

void salvare(FILE *f, TIP_NOD *p)
{
    if (p!=0)
    {
        salvare(f,p->st);
        fprintf(f, "%s, %.2f, %d, %s, %s\n", p->nume_med, p->pret, p->cantitate, p->data_prim, p->data_exp);
        salvare(f,p->dr);
    }
}

int main(void)
{
    TIP_NOD *rad = 0;
    TIP_NOD *rad2=0;
    citire(&rad);
    int optiune;

    while(1)
    {
        printf("1 Afisare, 2 Actualizeaza pret medicament, 3 Elimina medicament, 4 Creeaza lista medicamente expirate, 5 Iesire : ");
        scanf("%d", &optiune);
        switch(optiune)
        {
            case 1:
            {
                printf("\n");
                if (rad==0) printf("Lista goala \n");
                if (rad!=0) afisare(rad);
                printf("\n");
                break;
            }
            case 2:
            {
                printf("\n");
                if (rad==0) printf("Lista goala \n");
                if (rad!=0) cautaremed(rad);
                printf("\n");
                break;
            }
            case 3:
            {
                printf("\n");
                if (rad==0) printf("Lista goala \n");
                if (rad!=0) rad=stergere_nod(rad);
                break;
            }
            case 4:
            {
                printf("Introduceti data expirarii:");
                char data[15];
                gets(data);
                gets(data);
                if (rad2!=0)
                {
                    stergere_arbore(rad2);
                    rad2=NULL;
                }
                creare(rad, &rad2, data);
                afisare(rad2);
                break;
            }
            case 5:
            {
                printf("La revedere...");
                FILE *f = fopen("medicament.txt", "w");
                if(!f) return 0;
                salvare(f,rad);
                fclose(f);
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
