#include <stdio.h>
#include <stdlib.h>

typedef struct lista
{
    int val;
    struct lista *urm;
} LISTA;

int main()
{
    LISTA *L1=0, *L2=0;
    int n;

    printf("Introduceti numarul de valori pentru lista 1:");
    scanf("%d", &n);
    printf("Introduceti %d valori", n);
    for (int i=1; i<=n; i++)
    {
        if (i=1)
        {
            scanf("%d", &L1->val);
            L1->urm=0;
        }
        else
        {
            sca
        }

    }


    return 0;
}
