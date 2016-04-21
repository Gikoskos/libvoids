/***********************************************\
*                   testqueue.c                 *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "FIFOqueue.h"

void FIFOprint(FIFOqueue *queue, FILE *output_stream)
{
    if (queue) {
        FIFOnode *curr;
        fprintf(output_stream, "(head) ");
        for (curr = queue->head; curr; curr = curr->next) {
            fprintf(output_stream, "%d <- ", *(int*)(curr->data));
        }
        fprintf(output_stream, "\b\b\b(tail)\n");
    }
}

int main(int argc, char *argv[])
{
    FIFOqueue *test = newFIFOqueue();
    int a[5] = {4442, 2224, 1321, 7820, 98};
    int b[3] = {6, 12, 18};

    for (int i = 0; i < 5; i++) {
        if (!FIFOenqueue(test, (void*)&a[i])) {
            return 1;
        }
    }
    FIFOprint(test, stdout);
    for (int i = 0; i < 5; i++) {
        printf("FIFOdequeue = %d\n", *(int*)FIFOdequeue(test));
    }

    for (int i = 0; i < 3; i++) {
        if (!FIFOenqueue(test, (void*)&b[i])) {
            return 1;
        }
    }
    FIFOprint(test, stdout);
    for (int i = 0; i < 2; i++) {
        printf("FIFOdequeue = %d\n", *(int*)FIFOdequeue(test));
    }

    deleteFIFOqueue(test, DONT_DELETE_DATA);
    return 0;
}
