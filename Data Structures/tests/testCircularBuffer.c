#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GiDS.h>


int main(int argc, char *argv[])
{
    CircularBuffer *buff = newCircularBuffer(10);

    srand(time(NULL));

    printf("cBuffNew->size = %lu\n", (unsigned  long)buff->size);
    for (int i = 0; i < 10; i++) {
        int *data = malloc(sizeof data);

        *data = (int)rand();
        printf("Pushing data %d!\n", *data);

        pushCircularBuffer(buff, data);
    }

    putchar('\n');
    for (int i = 0; i < 4; i++) {
        int *data = popCircularBuffer(buff);

        if (data) {
            printf("Data %d popped!\n", *data);
            free(data);
        }
    }

    putchar('\n');
    for (int i = 0; i < 6; i++) {
        int *data = popCircularBuffer(buff);

        if (data) {
            printf("Data %d popped!\n", *data);
            free(data);
        }
    }

    if (!popCircularBuffer(buff)) {
        printf("No more data to read from the buffer!\n\n");
    }

    resizeCircularBuffer(&buff, 20);
    for (int i = 0; i < 15; i++) {
        int *data = malloc(sizeof data);

        *data = (int)rand();
        printf("Pushing data %d!\n", *data);

        pushCircularBuffer(buff, data);
    }

    putchar('\n');
    for (int i = 0; i < 17; i++) {
        int *data = popCircularBuffer(buff);

        if (data) {
            printf("Data %d popped!\n", *data);
            free(data);
        }
    }

    deleteCircularBuffer(&buff, NULL);
    return 0;
}
