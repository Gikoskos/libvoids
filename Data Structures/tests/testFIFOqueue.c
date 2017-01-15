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
    FIFOqueue *test = newFIFO();

    for (int i = 0; i < 5; i++) {
        enqueueFIFO(test, (void*)&a[i]);
    }

    printFIFO(test, printIntData);

    for (int i = 0; i < 5; i++) {
        printf("dequeueFIFO = %d\n", *(int*)dequeueFIFO(test));
    }

    for (int i = 0; i < 3; i++) {
        enqueueFIFO(test, (void*)&b[i]);
    }

    printFIFO(test, printIntData);

    for (int i = 0; i < 2; i++) {
        printf("dequeueFIFO = %d\n", *(int*)dequeueFIFO(test));
    }

    deleteFIFO(test, NULL);
    return 0;
}
