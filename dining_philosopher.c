#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PHIL 10

typedef enum { T, H, E } S;

S s[MAX_PHIL];
int n;  // Number of philosophers
int h;  // Number of hungry philosophers
int hp[MAX_PHIL];  // Positions of hungry philosophers
int f[MAX_PHIL];   // Forks status (0: available, 1: taken)

void p() {
    printf("\n");
    for (int i = 0; i < n; ++i) {
        if (s[i] == T) printf("P %d is thinking\n", i + 1);
        else if (s[i] == H) printf("P %d is waiting\n", i + 1);
        else if (s[i] == E) printf("P %d is eating\n", i + 1);
    }
}

void sim(int a) {
    int e = 0;  // Count of eating philosophers
    for (int i = 0; i < n; ++i) {
        if (s[i] == H) {
            int l = i;  // Left fork
            int r = (i + 1) % n;  // Right fork

            if (f[l] == 0 && f[r] == 0) {  // If both forks are available
                f[l] = f[r] = 1;  // Take the forks
                s[i] = E;  // Set state to eating
                e++;
                printf("P %d is granted to eat\n", i + 1);
                if (!a && e == 1) break;  // One can eat at a time
                if (a && e == 2) break;  // Two can eat at a time
            }
        }
    }

    sleep(1);  // Simulate eating time

    for (int i = 0; i < n; ++i) {
        if (s[i] == E) {
            int l = i;  // Left fork
            int r = (i + 1) % n;  // Right fork
            f[l] = f[r] = 0;  // Release the forks
            s[i] = T;  // Set state to thinking
        }
    }
}

int main() {
    printf("Enter total number of philosophers (max %d): ", MAX_PHIL);
    scanf("%d", &n);

    if (n < 2 || n > MAX_PHIL) {
        printf("Invalid number of philosophers. Exiting.\n");
        return 1;
    }

    printf("How many are hungry: ");
    scanf("%d", &h);

    for (int i = 0; i < h; ++i) {
        printf("Enter philosopher %d position: ", i + 1);
        int p;
        scanf("%d", &p);
        hp[i] = p - 1;  // Store the position (0-indexed)
        s[hp[i]] = H;  // Set state to hungry
    }

    for (int i = 0; i < n; ++i) {
        f[i] = 0;  // Initialize forks as available
    }

    int c;
    do {
        p();  // Print the state of philosophers
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &c);

        switch (c) {
            case 1:
                sim(0);  // Simulate with one eating at a time
                break;
            case 2:
                sim(1);  // Simulate with two eating at a time
                break;
            case 3:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (c != 3);

    return 0;
}
