/* Algoritmul lui Kruskal (a fost prezentat la cursul 8) */
#include<stdio.h>
#include <stdlib.h>
#define NMAX 20
#define NMUCHII 20
typedef struct
{
    int u, v;
    float cost;
} MUCHIE;

void citeste(int *nr_noduri, int *nr_muchii, MUCHIE *m);
void afiseaza(int nr_noduri, int nr_muchii, MUCHIE *m);
void ordonare(int nr_muchii, MUCHIE *m);
int gasire_cap_componenta(int *tata, int i);
void unire_componente(int a, int b, int *tata);
int kruskal(int nr_noduri, int nr_muchii, MUCHIE *m, int *selectate, int *tata);

int main()
{
    int nr_noduri, nr_muchii, i;
    int tata[NMAX] = {0};
    int selectate[NMUCHII] = {0};
    float cost_total;
    MUCHIE m[100];
    citeste(&nr_noduri, &nr_muchii, m);
    afiseaza(nr_noduri, nr_muchii, m);
    ordonare(nr_muchii, m);
    printf("Dupa ordonare\n");
    afiseaza(nr_noduri, nr_muchii, m);
    getch();
    for (i = 1; i <= nr_noduri; i++) tata[i] = -1;
    for (i = 1; i <= nr_muchii; i++) selectate[i] = 0;
    i = kruskal(nr_noduri, nr_muchii, m, selectate, tata);
    if(i == 0) printf("\nNu s-a construit arborele\n");
    else
    {
        cost_total=0;
        printf("Arborele de acoperire de cost minim are muchiile\n");
        printf("Muchia cost\n");
        for(i = 0; i < nr_muchii; i++)
        {
            if(selectate[i]==1)
            {
                printf("(%d,%d) %f\n", m[i].u, m[i].v, m[i].cost);
                cost_total += m[i].cost;
            }
        }
        printf("Costul total al arboreului: %f\n", cost_total);
    }
    getch();
    return 0;
}

void citeste(int *nr_noduri, int *nr_muchii, MUCHIE *m)
{
    FILE *f = fopen("graf.txt", "r");
    if(f == NULL)
    {
        printf("Nu exista fisierul graf.txt");
        exit(1);
    }
    fscanf(f, "%d", nr_noduri);
    *nr_muchii = 0;
    while(!feof(f))
    {
        fscanf(f, "%d%d%f", &m[*nr_muchii].u, &m[*nr_muchii].v, &m[*nr_muchii].cost);
        (*nr_muchii)++;
    }
    (*nr_muchii)--;
    fclose(f);
}

void afiseaza(int nr_noduri, int nr_muchii, MUCHIE *m)
{
    int i;
    printf("\nNr noduri:%d\n", nr_noduri);
    printf("\nNr muchii:%d\n", nr_muchii);
    printf("\nMUCHIA COST\n");
    for(i = 0; i < nr_muchii; i++)
        printf("(%d,%d) %f\n",m[i].u, m[i].v, m[i].cost);
}

void ordonare(int nr_muchii, MUCHIE *m)
{
    int i, j, k;
    MUCHIE z;
    j = -1;
    do
    {
        k = 1;
        j++;
        for(i = 0; i < nr_muchii-j; i++)
        {
            if (m[i].cost > m[i+1].cost)
            {
                z = m[i];
                m[i] = m[i+1];
                m[i+1] = z;
                k = 0;
            }
        }
    } while(k == 0);
}
int gasire_cap_componenta(int *tata, int i)
{
    while (tata[i] > 0)
        i = tata[i];
    return i;
}

void unire(int a, int b, int *tata)
{
    int k;
    k = tata[a] + tata[b];
    if(tata[a] > tata[b])
    {
        tata[a] = b;
        tata[b] = k;
    }
    else
    {
        tata[b] = a;
        tata[a] = k;
    }
}

int kruskal(int nr_noduri, int nr_muchii, MUCHIE *m, int *selectate, int *tata)
{
    int i = 0, j = 0, c1, c2;
    while((i < nr_noduri-1) && (j < nr_muchii))
    {
        j++;
        c1 = gasire_cap_componenta(tata, m[j].u);
        c2 = gasire_cap_componenta(tata, m[j].v);
        if(c1 != c2)
        {
            i++;
            selectate[j] = 1;
            unire(c1, c2, tata);
        }
    }
    if(i == nr_noduri-1) return 1;
    else return 0;
}
