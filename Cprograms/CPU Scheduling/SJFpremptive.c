//SJF Pre-emptive CPU scheduling C program.

#include <stdio.h>
struct process
{
    int ID, AT, BT, BT_TMP, CT, TAT, WT;
};
void main()
{
    struct process P[10];
    int n, i, j;
    float total_tat = 0, total_wt = 0;
    printf("Enter the number of Process: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        P[i].ID = i + 1;
        printf("Enter AT for process %d :", i + 1);
        scanf("%d", &P[i].AT);
        printf("Enter BT for process %d :", i + 1);
        scanf("%d", &P[i].BT);
        P[i].BT_TMP = P[i].BT;
    }
    printf("\nGantt Chart:\n");
    int MIN_IND, MIN_BT, COMP = 0, CUR_TIME = 0;
    while (COMP != n)
    {
        MIN_IND = -1;
        MIN_BT = 999;
        for (i = 0; i < n; i++)
        {
            if (P[i].AT <= CUR_TIME && P[i].BT > 0)
                if (P[i].BT < MIN_BT || (P[i].BT == MIN_BT && P[i].AT < P[MIN_IND].AT))
                {
                    MIN_BT = P[i].BT;
                    MIN_IND = i;
                }
        }
        CUR_TIME++;
        if (MIN_IND != -1)
        {
            P[MIN_IND].BT--;
            printf("| P%d(1) %d", P[MIN_IND].ID, CUR_TIME);
            if (P[MIN_IND].BT == 0)
            {
                P[MIN_IND].CT = CUR_TIME;
                P[MIN_IND].TAT = P[MIN_IND].CT - P[MIN_IND].AT;
                P[MIN_IND].WT = P[MIN_IND].TAT - P[MIN_IND].BT_TMP;
                total_tat += P[MIN_IND].TAT;
                total_wt += P[MIN_IND].WT;
                COMP++;
            }
        }
    }
    printf("\nID\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", P[i].ID, P[i].AT, P[i].BT_TMP, P[i].CT, P[i].WT, P[i].TAT);
    printf("AVG TAT : %.3f\n", total_tat / n);
    printf("AVG WT : %.3f\n", total_wt / n);
}
