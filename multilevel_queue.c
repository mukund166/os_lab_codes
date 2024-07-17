#include <stdio.h>

void sort(int proc_id[], int at[], int bt[], int n) {
    int temp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (at[j] < at[i]) {
                // Swap arrival times
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap burst times
                temp = bt[j];
                bt[j] = bt[i];
                bt[i] = temp;

                // Swap process IDs
                temp = proc_id[i];
                proc_id[i] = proc_id[j];
                proc_id[j] = temp;
            }
        }
    }
}

void fcfs(int at[], int bt[], int ct[], int tat[], int wt[], int n, int *c) {
    // Completion time
    for (int i = 0; i < n; i++) {
        if (*c >= at[i])
            *c += bt[i];
        else
            *c += at[i] - ct[i - 1] + bt[i];

        ct[i] = *c;
    }

    // Turnaround time
    for (int i = 0; i < n; i++)
        tat[i] = ct[i] - at[i];

    // Waiting time
    for (int i = 0; i < n; i++)
        wt[i] = tat[i] - bt[i];
}

void main() {
    int sn, un, c = 0;
    printf("Enter number of system processes: ");
    scanf("%d", &sn);
    int sproc_id[sn], sat[sn], sbt[sn], sct[sn], stat[sn], swt[sn];

    for (int i = 0; i < sn; i++)
        sproc_id[i] = i + 1;

    printf("Enter arrival times of the system processes:\n");
    for (int i = 0; i < sn; i++)
        scanf("%d", &sat[i]);

    printf("Enter burst times of the system processes:\n");
    for (int i = 0; i < sn; i++)
        scanf("%d", &sbt[i]);

    printf("Enter number of user processes: ");
    scanf("%d", &un);
    int uproc_id[un], uat[un], ubt[un], uct[un], utat[un], uwt[un];

    for (int i = 0; i < un; i++)
        uproc_id[i] = i + 1;

    printf("Enter arrival times of the user processes:\n");
    for (int i = 0; i < un; i++)
        scanf("%d", &uat[i]);

    printf("Enter burst times of the user processes:\n");
    for (int i = 0; i < un; i++)
        scanf("%d", &ubt[i]);

    sort(sproc_id, sat, sbt, sn);
    sort(uproc_id, uat, ubt, un);
    fcfs(sat, sbt, sct, stat, swt, sn, &c);
    fcfs(uat, ubt, uct, utat, uwt, un, &c);

    printf("\nScheduling:\n");
    printf("System processes:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < sn; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", sproc_id[i], sat[i], sbt[i], sct[i], stat[i], swt[i]);

    printf("User processes:\n");
    for (int i = 0; i < un; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", uproc_id[i], uat[i], ubt[i], uct[i], utat[i], uwt[i]);
}
