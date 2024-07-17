//Write a C program to simulate deadlock detection
#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

int available[NUM_RESOURCES];
int allocation[NUM_PROCESSES][NUM_RESOURCES];
int request[NUM_PROCESSES][NUM_RESOURCES];
int avail_matrix[NUM_PROCESSES + 1][NUM_RESOURCES];

bool deadlockDetection(int *safeSequence) {
    int work[NUM_RESOURCES];
    bool finish[NUM_PROCESSES] = {false};

    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
        avail_matrix[0][i] = work[i];
    }

    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;

        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish[i]) {
                bool canProceed = true;

                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (request[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;


                    for (int k = 0; k < NUM_RESOURCES; k++) {
                        avail_matrix[count][k] = work[k];
                    }
                }
            }
        }

        if (!found) {
            break;
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            printf("Deadlock detected. Process P%d is in deadlock.\n", i);
            return false;
        }
    }

    printf("No deadlock detected. The system is in a safe state.\n");
    printf("Safe sequence: ");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return true;
}

int main() {
    int i, j;

    printf("Enter the Available Resources Vector:\n");
    for (i = 0; i < NUM_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    printf("Available Resources: ");
    for (i = 0; i < NUM_RESOURCES; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < NUM_PROCESSES; i++) {
        for (j = 0; j < NUM_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Request Matrix:\n");
    for (i = 0; i < NUM_PROCESSES; i++) {
        for (j = 0; j < NUM_RESOURCES; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    int safeSequence[NUM_PROCESSES];
    if (deadlockDetection(safeSequence)) {
        printf("Available Matrix:\n");
        for (i = 0; i <= NUM_PROCESSES; i++) {
            for (j = 0; j < NUM_RESOURCES; j++) {
                printf("%d ", avail_matrix[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
