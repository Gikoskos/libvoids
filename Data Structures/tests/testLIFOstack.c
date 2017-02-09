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
    LIFOstack *test = newLIFO();

    for (int i = 0; i < 5; i++) {
        pushLIFO(test, (void*)&a[i]);
    }

    traverseLIFO(test, printIntData);
    putchar('\n');

    for (int i = 0; i < 5; i++) {
        printf("popLIFO = %d\n", *(int*)popLIFO(test));
    }

    for (int i = 0; i < 3; i++) {
        pushLIFO(test, (void*)&b[i]);
    }

    traverseLIFO(test, printIntData);
    putchar('\n');

    for (int i = 0; i < 2; i++) {
        printf("popLIFO = %d\n", *(int*)popLIFO(test));
    }

    deleteLIFO(&test, NULL);
    return 0;
}
