#include <stdio.h>

#define MAX_PROCESS 10

// Define a structure to represent a process
typedef struct {
    int pid;        // Process ID
    int arr;        // Arrival time
    int burst;      // Burst time
    int rem_burst;  // Remaining burst time
    int comp;       // Completion time
    int turn;       // Turnaround time
    int wait;       // Waiting time
    int processed;  // Flag to check if the process is completed
} Proc;

void srtf(Proc procs[], int n) {
    int curr_time = 0;               // Current time in the simulation
    int completed = 0;               // Number of processes completed
    int total_wait_time = 0;         // Total waiting time
    int total_turnaround_time = 0;   // Total turnaround time

    while (completed != n) {
        int shortest_job = -1;       // Index of the shortest job
        int shortest_rem_burst = 9999; // Shortest remaining burst time found

        // Find the process with the shortest remaining burst time that has arrived and is not processed
        for (int i = 0; i < n; i++) {
            if (procs[i].arr <= curr_time && procs[i].rem_burst > 0) {
                if (procs[i].rem_burst < shortest_rem_burst) {
                    shortest_rem_burst = procs[i].rem_burst;
                    shortest_job = i;
                }
            }
        }

        // If no such process is found, increment the current time and continue
        if (shortest_job == -1) {
            curr_time++;
            continue;
        }

        // Process the job for one unit of time
        procs[shortest_job].rem_burst--;
        curr_time++;

        // If the job is completed, update completion, turnaround, and waiting times
        if (procs[shortest_job].rem_burst == 0) {
            completed++;
            procs[shortest_job].comp = curr_time;
            procs[shortest_job].turn = procs[shortest_job].comp - procs[shortest_job].arr;
            procs[shortest_job].wait = procs[shortest_job].turn - procs[shortest_job].burst;
            total_wait_time += procs[shortest_job].wait;
            total_turnaround_time += procs[shortest_job].turn;
        }
    }

    // Calculate average times
    double avg_turnaround_time = (double)total_turnaround_time / n;
    double avg_waiting_time = (double)total_wait_time / n;

    // Print the results
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               procs[i].pid, procs[i].arr, procs[i].burst,
               procs[i].comp, procs[i].wait, procs[i].turn);
    }

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
}

int main() {
    int n;
    Proc procs[MAX_PROCESS];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Read arrival and burst times for each process
    for (int i = 0; i < n; i++) {
        procs[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &procs[i].arr);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &procs[i].burst);
        procs[i].rem_burst = procs[i].burst; // Initialize remaining burst time
        procs[i].processed = 0; // Initialize processed flag to 0
    }

    // Run SRTF scheduling
    srtf(procs, n);

    return 0;
}
