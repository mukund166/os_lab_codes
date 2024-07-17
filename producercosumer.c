#include <stdio.h>

#define MAX 10

int sharedMemory[MAX];
int top = -1;
int mutex = 1;
int empty = MAX;
int full = 0;

void wait(int *s){
    (*s)--;
}

void signal(int *s){
    (*s)++;
}

void producer(int A[], int *top, int *m, int *e, int *f){
    if(*e != 0){
        wait(m);
        A[++(*top)] = 1; // Produce an item (here represented by 1)
        wait(e);
        signal(f);
        signal(m);
    } else {
        printf("Buffer is full!\n");
    }
}

void consumer(int A[], int *top, int *m, int *e, int *f){
    if(*f != 0){
        wait(m);
        A[(*top)--] = 0; // Consume an item (here represented by setting it to 0)
        signal(e);
        wait(f);
        signal(m);
    } else {
        printf("Buffer is empty!\n");
    }
}

void printBuffer(int A[], int top) {
    printf("Buffer: ");
    for(int i = 0; i < MAX; i++) {
        if(i <= top) {
            printf("%d ", A[i]);
        } else {
            printf("0 ");
        }
    }
    printf("\n");
}

int main(){
    int optn;
    printf("Buffer size is %d\n", MAX);
    printf("1. Produce\n2. Consume\n3. Exit\n");

    while(1){
        printf("Enter option: ");
        scanf("%d", &optn);
        switch(optn) {
            case 1:
                producer(sharedMemory, &top, &mutex, &empty, &full);
                printBuffer(sharedMemory, top);
                break;
            case 2:
                consumer(sharedMemory, &top, &mutex, &empty, &full);
                printBuffer(sharedMemory, top);
                break;
            case 3:
                return 0;
            default:
                printf("Invalid option!\n");
                break;
        }
    }
    return 0;
}
