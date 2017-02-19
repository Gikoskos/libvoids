#include <stdio.h>
#include <stdlib.h>
#include <GiDS.h>

void printIntData(void *dat)
{
    printf("%d ", *(int*)dat);
}

int main(int argc, char *argv[])
{
    int a[5] = {4442, 2224, 1321, 7820, 98};
    int b[3] = {6, 12, 18};
    FIFOqueue *test = FIFO_init();

    for (int i = 0; i < 5; i++) {
        FIFO_enqueue(test, (void*)&a[i]);
    }

    FIFO_traverse(test, printIntData);
    putchar('\n');

    for (int i = 0; i < 5; i++) {
        printf("FIFO_dequeue = %d\n", *(int*)FIFO_dequeue(test));
    }

    for (int i = 0; i < 3; i++) {
        FIFO_enqueue(test, (void*)&b[i]);
    }

    FIFO_traverse(test, printIntData);
    putchar('\n');

    for (int i = 0; i < 2; i++) {
        printf("FIFO_dequeue = %d\n", *(int*)FIFO_dequeue(test));
    }

    FIFO_destroy(&test, NULL);
    return 0;
}
