/* Algoritmul lui Prim (a fost prezentat la cursul 8) */
#include <stdio.h>
#include <conio.h>
#define NMAX 15
#define INFINIT 0x7fffffff
void prim(int n, int c[NMAX][NMAX], int muchii[NMAX][2], int *cost)
{ /* n - numărul nodurilor,
c - matricea costurilor,
muchii - muchiile arborelui de acoperire de cost minim,
cost - costul arborelui de acoperire de cost minim */
    int i, j, k, minim , v[NMAX];
/*
v[i] = 0 dacă i aparține arborelui,
v[i] = j dacă i nu aparține arborelui,
j este nodul din arbore a.î. muchia (i, j) este de cost minim
*/
    *cost = 0;
    v[1] = 0;
/* arborele este ({1},{}) */
    for(i = 2; i <= n; i++)
    {
        v[i]=1;
    }
/* determinarea celor n-1 muchii */
    for(i = 1; i <= n-1; i++)
    { /* determinarea muchiei care se adaugă arborelui */
        minim = INFINIT;
        for(k = 1; k <= n; k++)
        {
            if((v[k] != 0) && (c[k][v[k]] < minim))
            {
                j = k;
                minim = c[k][v[k]];
            }
        }
        muchii[i][0] = v[j];
        muchii[i][1] = j;
        *cost = *cost + c[j][v[j]];
        /* reactualizare vector v */
        v[j] = 0;
        for(k = 1; k <= n; k++)
            if((v[k] != 0) && (c[k][v[k]] > c[k][j]))
                v[k]=j;
    }
}

int main()
{
    int n; // numărul nodurilor
    int c[NMAX][NMAX]; /* matricea costurilor */
    int muchii[NMAX][2]; /* muchiile arborelui */
    int i, j, k, cost;
    FILE *f = fopen("graf.txt", "r");
    if(f == NULL)
    {
        printf("Nu exista fisierul graf.txt");
        exit(1);
    }
    /* Citire număr noduri de pe prima linie a fișierului */
    fscanf(f, "%d", &n);
    /* inițializare matrice costuri */
    for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            c[i][j] = INFINIT;
/* citirea costurilor (numere întregi) */
    while(!feof(f))
    {
        fscanf(f, "%d %d", &i, &j);
        fscanf(f, "%d", &c[i][j]);
        c[j][i] = c[i][j];
    }
    fclose(f);
    prim(n, c, muchii, &cost);
    printf("\nCOSTUL ARBORELUI = %d",cost);
    printf("\nMUCHIILE ARBORELUI COSTUL MUCHIEI\n");
    for(i = 1; i <= n-1; i++)
        printf(" %2d - %2d %10d\n", muchii[i][0], muchii[i][1], c[muchii[i][0]][muchii[i][1]]);
    getch();
return 0;
}
