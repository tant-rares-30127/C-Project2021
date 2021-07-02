#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define NMAX 10

void dame_nerecursiv(int n)
{
    int x[NMAX], v, i, j, k = 1, nr_solutie = 0;
    x[k]=0;
    while(k > 0)
    { /* găsirea unei așezări corecte în linia k */
        v=0;
        while((v == 0) && (x[k] <= n-1))
        {
            x[k]++;
            v=1;
            i=1;
            while((i <= k-1) && (v == 1))
                if((x[k] == x[i]) || (abs(k-i) == abs(x[k] - x[i]))) v=0;
                else i++;
        }
        if(v == 0) k--;
        else
        {
            if(k == n)
            { /* afișarea tablei */
                nr_solutie++;
                printf("\nSOLUTIA nr. %d\n",nr_solutie);
                for(i = 1; i <= n; i++)
                {
                    for(j = 1; j <= n; j++)
                        if (x[i] == j) printf("1");
                        else printf("0");

                    printf("\n");
                }
                getch();
            }
            else
            {
                k++;
                x[k] = 0;
            }
        }
    }
}

int main()
{
    int n;
    printf("\nOrdinul tablei de sah=");
    scanf("%d",&n);
    dame_nerecursiv(n);
    return 0;
}
