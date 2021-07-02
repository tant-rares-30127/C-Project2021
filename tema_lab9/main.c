#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 256

typedef struct tip_nod
{
    char *nume;
    float media;
    struct tip_nod *urm;
}TIP_NOD;

int fun(char *cheie)
{
    int i, suma;
    suma = 0;
    for(i = 0; i < strlen(cheie); i++)
        suma += *(cheie + i);
    return suma & (M-1);
}

void citire(TIP_NOD *HT[M])
{
    FILE *f = fopen("studenti.txt", "r");
    if(!f)
    {
        printf("NU s-a deschis fisierul studenti.txt...");
        exit(1);
    }
    char line[200];
    while(fgets(line, sizeof(line),f))
    {
        TIP_NOD *p;

        p = (TIP_NOD*)malloc(sizeof(TIP_NOD));

        char *token;
        char nume[50], prenume[50];

        token=strtok(line, ",");
        strcpy(nume, token);
        token=strtok(NULL, ",");
        strcpy(prenume, token);
        strcat(nume, " ");
        strcat(nume, prenume);
        p->nume = (char*)malloc((strlen(nume))*sizeof(char));
        strcpy(p->nume, nume);
        token=strtok(NULL, ",");
        p->media=atof(token);

        int h=fun(p->nume);


        if(HT[h] == 0)
        {
            HT[h] = p;
            p->urm = 0;
        }
        else
        {
            p->urm = HT[h];
            HT[h] = p;
        }
    }
    fclose(f);
}

void afisare(TIP_NOD *HT[M])
{
    int i;
    TIP_NOD *p;
    for(i = 0;i < M; i++)
    if(HT[i] != 0)
    {
        printf("Inregistrari avand codul de dispersie = %d\n", i);
        p = HT[i];
        while(p != 0)
        {
            printf("%s %.2f \n", p->nume, p->media);
            p = p->urm;
        }
    }
}

void schimbadate(TIP_NOD *HT[M])
{
    printf("Introduceti numele studentului caruia doriti sa ii schimbati media:");
    char nume[100];
    gets(nume);
    gets(nume);
    int h = fun(nume);
    TIP_NOD *p = HT[h];
    float med=0;
    while((p) && (med==0))
    {
        if(strcmp(nume, p->nume) == 0)
        {
            printf("Studentul a fost gasit. Introduceti media:");
            scanf("%f", &med);
            p->media=med;
            printf("Datele au fost modificate \n");
        }
        p = p->urm;
    }
    if (med==0) printf("Studentul nu a fost gasit \n");
    return;
}

void adaugadate(TIP_NOD *HT[M])
{
    TIP_NOD *p;
    p = (TIP_NOD*)malloc(sizeof(TIP_NOD));
    printf("Introduceti numele studentului pe care doriti sa-l adaugati:");
    char nume[100];
    gets(nume);
    gets(nume);
    p->nume = (char*)malloc((strlen(nume))*sizeof(char));
    strcpy(p->nume,nume);
    printf("Introduceti media:");
    scanf("%f", &p->media);
    int h = fun(p->nume);
    if(HT[h] == 0)
    {
        HT[h] = p;
        p->urm = 0;
    }
    else
    {
        p->urm = HT[h];
        HT[h] = p;
    }
}

void eliminadate(TIP_NOD *HT[M])
{
    printf("Introduceti numele studentului pe care doriti sa-l eliminati:");
    char nume[100];
    gets(nume);
    gets(nume);
    int h = fun(nume);
    TIP_NOD *p=HT[h];
    TIP_NOD *q=HT[h];
    if (p==0)
    {
        printf("Nu exista studentul \n");
    }
    else
    {
        while(p)
        {
            if(strcmp(nume, p->nume) == 0)
            {
                if(p==HT[h])
                {
                    HT[h]=p->urm;
                    free(p);
                    return;
                }
                else
                {
                    if (p->urm==0)
                    {
                        q->urm=0;
                        free(p);
                        return;
                    }
                    else
                    {
                        q->urm=q->urm->urm;
                        free(p);
                        return;
                    }
                }
            }
            q = p;
            p = p->urm;
        }
    }
}

void salvare(TIP_NOD *HT[M])
{
    FILE *f = fopen("studenti.txt", "w");
    if(!f)
    {
        printf("NU s-a deschis fisierul studenti.txt...");
        exit(1);
    }
    for(int i=0; i<M; i++)
    {
        if (HT[i]!=0)
        {
            TIP_NOD *p=HT[i];
            while(p)
            {
                char *token;
                char nume[50], prenume[50];

                token=strtok(p->nume, " ");
                strcpy(nume, token);
                token=strtok(NULL, " ");
                strcpy(prenume, token);
                fprintf(f, "%s,%s,%.2f\n", nume, prenume, p->media);
                p=p->urm;
            }
        }
    }
    fclose(f);
}

int main()
{
    TIP_NOD *HT[M];

    for(int i = 0; i < M; i++) HT[i] = 0;

    citire(HT);

    while(1)
    {
        int optiune;
        printf("1 Afisare inregistrari, 2 Schimba inregistrare, 3 Adauga inregistrare, 4 Elimina inregistrare, 5 Iesire : ");
        scanf("%d", &optiune);
        switch(optiune)
        {
            case 1:
            {
                printf("\n");
                afisare(HT);
                printf("\n");
                break;
            }
            case 2:
            {
                printf("\n");
                schimbadate(HT);
                break;
            }
            case 3:
            {
                printf("\n");
                adaugadate(HT);
                break;
            }
            case 4:
            {
                printf("\n");
                eliminadate(HT);
                break;
            }
            case 5:
            {
                printf("La revedere...");
                salvare(HT);
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
}
