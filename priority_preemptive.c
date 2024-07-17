#include <stdio.h>

void sort(int proc_id[], int p[], int at[], int bt[], int b[], int n) {
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
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap original burst times
                temp = b[i];
                b[i] = b[j];
                b[j] = temp;

                // Swap priorities
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;

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

    int proc_id[n], at[n], bt[n], ct[n], tat[n], wt[n], m[n], b[n], rt[n], p[n];
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
        b[i] = bt[i];
        m[i] = -1;
        rt[i] = -1;
    }

    sort(proc_id, p, at, bt, b, n);
    int count = 0, pro = 0, priority = p[0];
    int x = 0;
    c = 0;

    while (count < n) {
        for (int i = 0; i < n; i++) {
            if (at[i] <= c && p[i] >= priority && b[i] > 0 && m[i] != 1) {
                x = i;
                priority = p[i];
            }
        }

        if (b[x] > 0) {
            if (rt[x] == -1)
                rt[x] = c - at[x];
            b[x]--;
            c++;
        }

        if (b[x] == 0) {
            count++;
            ct[x] = c;
            m[x] = 1;
            while (x >= 1 && b[x] == 0)
                priority = p[--x];
        }

        if (count == n)
            break;
    }

    // Turnaround time and RT
    for (int i = 0; i < n; i++)
        tat[i] = ct[i] - at[i];

    // Waiting time
    for (int i = 0; i < n; i++)
        wt[i] = tat[i] - bt[i];

    printf("Priority scheduling (Pre-Emptive):\n");
    printf("PID\tPrior\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t %d\t%d\t%d\t%d\t%d\t%d\t%d\n", proc_id[i], p[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);

    for (int i = 0; i < n; i++) {
        ttat += tat[i];
        twt += wt[i];
    }

    avg_tat = ttat / (double)n;
    avg_wt = twt / (double)n;

    printf("\nAverage turnaround time: %lf ms\n", avg_tat);
    printf("\nAverage waiting time: %lf ms\n", avg_wt);

    return 0;
}
