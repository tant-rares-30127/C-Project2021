#include <stdio.h>
#include <stdlib.h>

int INFINIT=10000;

int ** citire(int *n, int **distante, int **tata)
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
    *distante = (int *)malloc((*n+1)*sizeof(int));
    *tata = (int *)malloc((*n+1)*sizeof(int));
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

int citire_nod(int n, char *mesaj)
{
    int nod;
    do
    {
        printf("Introduceti nodul de %s = ", mesaj);
        scanf("%d", &nod);
    } while(nod<=0 || nod>n); /* nodul trebuie să aibă valoarea între 1 și n */
    return nod;
}

int ** FLOYD(int n, int **C, int P[n+1][n+1])
{
    int i, j, k;
    int **A;
    A = (int **)malloc((n+1)*sizeof(int));
    for(i = 1; i <= n; i++)
    {
        *(A+i) = (int *)malloc((n+1)*sizeof(int));
        for(j = 1; j <= n; j++)
        {
            A[i][j] = C[i][j]; /* iniţializare A */
            P[i][j]=0;
        }
    }
    for(i = 1; i <= n; i++) A[i][i]=0;
    for(k = 1; k <= n; k++) /* iteraţiile */
        for(i = 1; i <= n; i++) /* pentru toate liniile */
            for(j = 1; j <= n; j++) /* pentru toate coloanele */
                if ((A[i][k] + A[k][j] < A[i][j]) && (A[i][j]!=INFINIT))
                {
                    A[i][j] = A[i][k] + A[k][j];
                    P[i][j]=k;
                }

    return A;
}

void dijkstra(int **cost, int n, int s, int *distante, int *tata)
{ /* s = nod de plecare */
    int *vizitate = (int *)malloc((n+1)*sizeof(int));
    int i, k, pas, minim;
    /* inițializări */
    for (i = 1; i <= n; i++)
    {
        vizitate[i] = 0;
        distante[i] = cost[s][i];
        if (distante[i] < INFINIT) tata[i] = s;
        else tata[i] = 0;
    }
    vizitate[s] = 1;
    tata [s] = 0;
    distante [s] = 0;
    for (pas = 1; pas <= n-1; pas++)
    {
        /* găsește vârful k neselectat cu distanțe[k] minim */
        minim = INFINIT;
        k = 0;
        for (i = 1; i <= n; i++)
        {
            if(distante[i]<minim && !vizitate[i])
            {
                minim = distante[i];
                k = i;
            }
        }
        if (minim == INFINIT)
        {
            free(vizitate);
            return;
        }
        vizitate[k] = 1;
        for (i = 1; i <= n; i++)
        {
            if((vizitate[i] == 0) && (distante[k] + cost[k][i] < distante[i]) && (distante[k] + cost[k][i] > 0))
            {
                distante [i] = distante[k] + cost[k][i];
                tata[i] = k;
            }
        }
    }
    free(vizitate);
}


void cale(int nod, int *tata, int n, int P[n+1][n+1])
{
    if(nod)
    {
        cale(tata[nod], tata, n, P);
        int k=P[nod][tata[nod]];
        if ((k!=0)&(tata[nod]!=0)) printf("%d-> ", k);
        printf("%d-> ", nod);
    }
}

void afisare_distante(int *distante, int n, int s, int *tata, int P[n+1][n+1])
{
    int i;
    printf("Vectorul distante: ");
    for(i=1; i<=n; i++)
    {
            printf("%d ", distante[i]);
    }
    printf("\nVectorul tata: ");
    for(i=1; i<=n; i++)
    {
        printf("%d ", tata[i]);
    }
    printf("\n");
    printf("\n");
    for (int j=1; j<=n; j++)
        if (j!=s)
        {
            printf("Distanta intre nodul %d si nodul %d este %d\n", s, j, distante[j]);
            printf("Drumul intre noduri este urmatorul: ");
            cale(j, tata, n, P);
            printf("|\n");
        }
}

int main()
{
    int *distante, *tata;
    int n, **cost = citire(&n, &distante, &tata);
    afisare(cost, n);
    printf("\n");
    //int s = citire_nod(n, "plecare");
    int P[n+1][n+1];
    int **A=FLOYD(n,cost,P);
    printf("\n");
    afisare(A,n);

    for (int i=1; i<=n; i++)
    {
        dijkstra(A, n, i, distante, tata);
        afisare_distante(distante, n, i, tata, P);
        printf("\n");
    }

    return 0;
}
