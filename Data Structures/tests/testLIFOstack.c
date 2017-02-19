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
    LIFOstack *test = LIFO_init();

    for (int i = 0; i < 5; i++) {
        LIFO_push(test, (void*)&a[i]);
    }

    LIFO_traverse(test, printIntData);
    putchar('\n');

    for (int i = 0; i < 5; i++) {
        printf("LIFO_pop = %d\n", *(int*)LIFO_pop(test));
    }

    for (int i = 0; i < 3; i++) {
        LIFO_push(test, (void*)&b[i]);
    }

    LIFO_traverse(test, printIntData);
    putchar('\n');

    for (int i = 0; i < 2; i++) {
        printf("LIFO_pop = %d\n", *(int*)LIFO_pop(test));
    }

    LIFO_destroy(&test, NULL);
    return 0;
}
