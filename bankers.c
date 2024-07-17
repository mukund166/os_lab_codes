//Write a C program to simulate Bankers algorithm for the purpose of deadlock
//avoidance.
#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

int available[NUM_RESOURCES];
int maximum[NUM_PROCESSES][NUM_RESOURCES];
int allocation[NUM_PROCESSES][NUM_RESOURCES];
int need[NUM_PROCESSES][NUM_RESOURCES];
int safe_sequence[NUM_PROCESSES];
int scount = 0;
void calculateNeed() {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

bool isSafe() {
    int work[NUM_RESOURCES];
    bool finish[NUM_PROCESSES] = {false};

    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }

    while (true) {
        bool found = false;

        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish[i]) {
                bool canProceed = true;

                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    printf("Process %d is visited (%d,%d,%d)\n",i,work[0],work[1],work[2]);
                    finish[i] = true;
                    safe_sequence[scount]=i;
                    scount+=1;
                    found = true;
                }
            }
        }

        if (!found) {
            break;
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            return false;
        }
    }

    return true;
}

bool requestResources(int process, int request[]) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }

        if (request[i] > available[i]) {
            printf("Error: Resources not available.\n");
            return false;
        }
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (isSafe()) {
        printf("Request granted.\n");
        return true;
    } else {
        for (int i = 0; i < NUM_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        printf("Request cannot be granted. System would be in an unsafe state.\n");
        return false;
    }
}

int main() {
    // Initialize the Available, Maximum, and Allocation matrices
    int i, j;

    printf("Enter the Available Resources Vector:\n");
    for (i = 0; i < NUM_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the Maximum Matrix:\n");
    for (i = 0; i < NUM_PROCESSES; i++) {
        for (j = 0; j < NUM_RESOURCES; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < NUM_PROCESSES; i++) {
        for (j = 0; j < NUM_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    calculateNeed();
    printf("Need Matrix\n");
    for(int i=0;i<NUM_PROCESSES;i++){
        for(int j=0;j<NUM_RESOURCES;j++){
            printf("%d\t",need[i][j]);
        }
        printf("\n");
    }


    if (isSafe()) {
        printf("\nThe system is in a safe state.\n");
        printf("\nSafe Sequence\n");
        for(int i=0;i<NUM_PROCESSES;i++)
            printf("%d\t",safe_sequence[i]);
    } else {
        printf("\nThe system is not in a safe state.\n");
    }

    // Example of a resource request
    int process;
    int request[NUM_RESOURCES];

    printf("\nEnter the process number for the request (0 to %d): ", NUM_PROCESSES - 1);
    scanf("%d", &process);

    printf("Enter the request vector:\n");
    for (i = 0; i < NUM_RESOURCES; i++) {
        scanf("%d", &request[i]);
    }

    requestResources(process, request);

    return 0;
}
