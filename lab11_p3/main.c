#include <stdio.h>
#include <stdlib.h>

void greedy1(int v_bani[], int v_nr[], int r)
{
    int i=0;
    while (r!=0)
    {
        while(v_bani[i]<=r)
        {
            r=r-v_bani[i];
            v_nr[i]++;
            printf("%d %d\n", r, v_bani[i]);
        }
        i++;
    }
}

int main()
{
    int v_bani[7];
    int v_nr[7];
    int i, r;
    v_bani[0]=500;
    v_bani[1]=200;
    v_bani[2]=100;
    v_bani[3]=50;
    v_bani[4]=10;
    v_bani[5]=5;
    v_bani[6]=1;
    for (i=0;i<=6;i++)
    {
        v_nr[i]=0;
    }
    printf("Restul=");
    scanf("%d", &r);
    greedy1(v_bani,v_nr,r);

    printf("Pentru a plati restul=%d s-au folosit: \n", r);
    for (i=0;i<=6;i++)
    {
        if (v_nr[i]!=0) printf("%d bancnote de %d lei \n", v_nr[i], v_bani[i]);
    }

    return 0;
}
