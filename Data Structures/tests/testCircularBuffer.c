#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <EduDS.h>


int main(int argc, char *argv[])
{
    CircularBuffer *buff = CircularBuffer_init(10);

    srand(time(NULL));

    printf("cBuffNew->size = %lu\n", (unsigned  long)buff->size);
    for (int i = 0; i < 10; i++) {
        int *data = malloc(sizeof data);

        *data = (int)rand();
        printf("Pushing data %d!\n", *data);

        CircularBuffer_write(buff, data);
    }

    putchar('\n');
    for (int i = 0; i < 4; i++) {
        int *data = CircularBuffer_read(buff);

        if (data) {
            printf("Data %d popped!\n", *data);
            free(data);
        }
    }

    putchar('\n');
    for (int i = 0; i < 6; i++) {
        int *data = CircularBuffer_read(buff);

        if (data) {
            printf("Data %d popped!\n", *data);
            free(data);
        }
    }

    if (!CircularBuffer_read(buff)) {
        printf("No more data to read from the buffer!\n\n");
    }

    CircularBuffer_resize(&buff, 20);
    for (int i = 0; i < 15; i++) {
        int *data = malloc(sizeof data);

        *data = (int)rand();
        printf("Pushing data %d!\n", *data);

        CircularBuffer_write(buff, data);
    }

    putchar('\n');
    for (int i = 0; i < 17; i++) {
        int *data = CircularBuffer_read(buff);

        if (data) {
            printf("Data %d popped!\n", *data);
            free(data);
        }
    }

    CircularBuffer_destroy(&buff, NULL);
    return 0;
}
