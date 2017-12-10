#include <stdio.h>
#include <stdlib.h>
#include <voids.h>

void printIntData(void *dat)
{
    printf("%d ", *(int*)dat);
}

int main(int argc, char *argv[])
{
    int a[5] = {4442, 2224, 1321, 7820, 98};
    int b[3] = {6, 12, 18};
    LIFOstack *test = LIFO_init(NULL);

    for (int i = 0; i < 5; i++) {
        LIFO_push(test, (void*)&a[i], NULL);
    }

    LIFO_traverse(test, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 5; i++) {
        printf("LIFO_pop = %d\n", *(int*)LIFO_pop(test, NULL));
    }

    for (int i = 0; i < 3; i++) {
        LIFO_push(test, (void*)&b[i], NULL);
    }

    LIFO_traverse(test, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 2; i++) {
        printf("LIFO_pop = %d\n", *(int*)LIFO_pop(test, NULL));
    }

    LIFO_destroy(&test, NULL, NULL);
    return 0;
}
