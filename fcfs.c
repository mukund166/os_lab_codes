#include <stdio.h>

#define MX_PROC 10

typedef struct {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
} Pr;

void swp(Pr *a, Pr *b) {
    Pr temp = *a;
    *a = *b;
    *b = temp;
}

void srt(Pr pr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (pr[j].at > pr[j + 1].at) {
                swp(&pr[j], &pr[j + 1]);
            }
        }
    }
}

int main() {
    int np;
    Pr pr[MX_PROC];

    printf("Enter the number of processes: ");
    scanf("%d", &np);

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < np; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &pr[i].at);
        printf("Burst Time: ");
        scanf("%d", &pr[i].bt);
        pr[i].pid = i + 1;
    }

    srt(pr, np);

    int ct = 0;
    for (int i = 0; i < np; i++) {
        if (ct < pr[i].at) {
            ct = pr[i].at;
        }
        pr[i].ct = ct + pr[i].bt;
        pr[i].tat = pr[i].ct - pr[i].at;
        pr[i].wt = pr[i].tat - pr[i].bt;
        ct = pr[i].ct;
    }

    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < np; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pr[i].pid, pr[i].at,
               pr[i].bt, pr[i].ct, pr[i].tat,
               pr[i].wt);
    }

    return 0;
}
