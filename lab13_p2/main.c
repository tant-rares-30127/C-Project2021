#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define INFINIT 0x7fffffff
int ** citire(int *n, int **ciclu)
{
    int **cost;
    FILE *f=fopen ("graf.txt","r");
    if(f == NULL)
    {
        printf("NU s-a deschis fisierul graf.txt...");
        exit(1);
    }
    int i, j, c;
    fscanf(f,"%d",n);
    *ciclu = (int *)malloc((*n+2)*sizeof(int));
    cost = (int **)malloc((*n+1)*sizeof(int));
    for(i=1; i<=*n; i++)
    {
        *(cost+i) = (int *)malloc((*n+1)*sizeof(int));
        for(j=1; j<=*n; j++)
        {
            cost[i][j] = INFINIT;
        }
    }
    while(!feof(f))
    {
        i = j = 0;
        fscanf(f,"%d%d%d", &i, &j, &c);
        if(i>0 && i<=*n && j>0 && j<=*n)
        {
            cost[i][j] = c;
            cost[j][i] = c; /* matricea este simetrică atunci când graful este nedirecționat */
        }
    }
    fclose(f);
    return cost;
}

void afisare(int **cost, int n)
{
    int i, j;
    printf("Continutul matricei de costuri:\n");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
        {
            if(cost[i][j] != INFINIT)
            {
                printf("%3d ", cost[i][j]);
            }
            else
            {
                printf("INF ");
            }
        }
        printf("\n");
    }
}

void comis_voiajor(int n, int **c, int i, int *ciclu, int *cost)
{ /* n este numărul nodurilor;
c[][] este matricea costurilor;
i este nodul de start;
ciclu[] conține nodurile din ciclu;
cost este costul ciclului */
    int k, v, j, vmin, costmin;
    int *p = (int *)malloc((n+1)*sizeof(int));
    for(k=1; k<=n; k++) p[k] = 0;
    *cost = 0;
    p[i] = 1;
    ciclu[1] = i;
    v = i; /* nodul curent */
    for(k=1;k<n;k++)
    { /* se adaugă pe rând n-1 muchii */
        costmin = INFINIT;
        /* găsirea muchiei de cost minim care are nodul de origine v */
        for(j=1;j<=n;j++)
        if((p[j]==0)&&(c[v][j]<costmin))
        {
            costmin = c[v][j];
            vmin = j;
        }
        *cost = *cost + costmin;
        ciclu[k+1] = vmin;
        p[vmin] = 1;
        v = vmin;
    }
    ciclu[n+1] = i;
    *cost = *cost + c[v][i];
    free(p);
}

void afisare_ciclu(int *ciclu, int n, int cost_ciclu)
{
    printf("\nCOSTUL CICLULUI = %d\n", cost_ciclu);
    printf("\nCICLUL = ");
    for(int i=1; i<=n+1; i++)
    printf("%3d ", ciclu[i]);
    printf("\n");
}

int main(void)
{
    int n, cost_ciclu, *ciclu, **c;
    c = citire(&n, &ciclu);
    afisare(c, n);
    comis_voiajor(n, c, 1, ciclu, &cost_ciclu);
    afisare_ciclu(ciclu, n, cost_ciclu);
    return 0;
}
