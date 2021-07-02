#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define NMAX 10
int n; /* dimensiunea (ordinul) tablei de șah */
int nr_solutie;
int x[NMAX];
int FI(int k)
{ /* testează condițiile de continuare */
    int i;
    for(i = 1; i <= k-1; i++)
        if((x[k] == x[i]) || (abs(k - i) == abs(x[k] - x[i])))
            return 0;
    return 1;
}
void back_recursiv(int k)
{
    int i, j, p;
    for(j = 1; j <= n; j++)
    {
        x[k]=j;
        if(FI(k) == 1)
        {
            if(k < n) back_recursiv(k+1);
            else
            { /* tipărirea soluției */
                nr_solutie++;
                printf("\nSOLUTIA nr.%d\n", nr_solutie);
                for(i = 1; i <= n; i++)
                {
                    for(p = 1; p <= n; p++)
                        if(x[i] == p) printf("1");
                        else printf("0");

                    printf("\n");
                }
                getch();
            }
        }
    }
}

int main()
{
    printf("\nOrdinul tablei de sah n=");
    scanf("%d",&n);
    back_recursiv(1);
    return 0;
}
