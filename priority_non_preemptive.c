#include <stdio.h>

void sort(int proc_id[], int p[], int at[], int bt[], int n) {
    int min, temp;
    for (int i = 0; i < n; i++) {
        min = p[i];
        for (int j = i; j < n; j++) {
            if (p[j] < min) {
                // Swap arrival times
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap burst times
                temp = bt[j];
                bt[j] = bt[i];
                bt[i] = temp;

                // Swap priorities
                temp = p[j];
                p[j] = p[i];
                p[i] = temp;

                // Swap process IDs
                temp = proc_id[i];
                proc_id[i] = proc_id[j];
                proc_id[j] = temp;
            }
        }
    }
}

int main() {
    int n, c = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int proc_id[n], at[n], bt[n], ct[n], tat[n], wt[n], m[n], rt[n], p[n];
    double avg_tat = 0.0, ttat = 0.0, avg_wt = 0.0, twt = 0.0;

    for (int i = 0; i < n; i++) {
        proc_id[i] = i + 1;
        m[i] = 0;
    }

    printf("Enter priorities:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &at[i]);

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        m[i] = -1;
        rt[i] = -1;
    }

    sort(proc_id, p, at, bt, n);

    // Completion time
    int count = 0, pro = 0, priority = p[0], x = 0;
    c = 0;

    while (count < n) {
        for (int i = 0; i < n; i++) {
            if (at[i] <= c && p[i] >= priority && m[i] != 1) {
                x = i;
                priority = p[i];
            }
        }

        if (rt[x] == -1)
            rt[x] = c - at[x];

        if (at[x] <= c)
            c += bt[x];
        else
            c += at[x] - c + bt[x];

        count++;
        ct[x] = c;
        m[x] = 1;

        while (x >= 1 && m[--x] != 1) {
            priority = p[x];
            break;
        }
        x++;

        if (count == n)
            break;
    }

    // Turnaround time and RT
    for (int i = 0; i < n; i++)
        tat[i] = ct[i] - at[i];

    // Waiting time
    for (int i = 0; i < n; i++)
        wt[i] = tat[i] - bt[i];

    printf("\nPriority scheduling:\n");
    printf("PID\tPrior\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t %d\t\t%d\t%d\t%d\t%d\t%d\t%d\n",
               proc_id[i], p[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);

    for (int i = 0; i < n; i++) {
        ttat += tat[i];
        twt += wt[i];
    }

    avg_tat = ttat / (double)n;
    avg_wt = twt / (double)n;

    printf("\nAverage turnaround time: %lf ms\n", avg_tat);
    printf("Average waiting time: %lf ms\n", avg_wt);

    return 0;
}
