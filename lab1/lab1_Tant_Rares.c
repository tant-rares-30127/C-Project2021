# include <stdlib.h>
# include <stdio.h>
# define NMAX 100

typedef struct locomotiva
{
    int Id;
    char Tip[21];
    float Greutate;
} LOCOMOTIVA;
int main()
{
    int varf = 0, optiune;
    LOCOMOTIVA DEPOU[NMAX];
    while(1)
    {
        printf("1 intrare, 2 iesire, 3 afisare, 4 terminare ");
        scanf("%d", &optiune);
        switch(optiune)
        {
            case 1:
            { // modulul Intrare;
                if(varf == NMAX)
                {
                    printf("Depoul este plin...\n");
                }
                else
                {
                    printf("Introduceti Id = ");
                    scanf("%d", &DEPOU[varf].Id);
                    printf("Introduceti Tip = ");
                    scanf("%s", DEPOU[varf].Tip);
                    printf("Introduceti Greutate = ");
                    scanf("%f", &DEPOU[varf].Greutate);
                    varf++;
                }
                break;
            }
            case 2:
            { // modulul Ieșire;
                if(varf == 0)
                {
                    printf("Depoul este gol...\n");
                }
                else
                {
                    printf("Locomotiva care iese are urmatoarele detalii: Id =%d Tip = %s Greutate = %f\n", DEPOU[varf-1].Id, DEPOU[varf-1].Tip, DEPOU[varf-1].Greutate);
                    varf--;
                }
                break;
            }
            case 3:
            { // modulul Afișare;
                if(varf == 0)
                {
                    printf("Depoul este gol...\n");
                }
                else
                {
                    int i;
                    for(i = varf-1; i >= 0; i--)
                    {
                        printf("Locomotiva %d are urmatoarele detalii: Id = %d Tip = %s Greutate = %f\n", i+1, DEPOU[i].Id, DEPOU[i].Tip, DEPOU[i].Greutate);
                    }
                }
                break;
            }
            case 4:
            {
                printf("La revedere...");
                return 0;
            }
            default:
            {
                printf("Optiune gresita...");
                break;
            }
        }
    }
}
