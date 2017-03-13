#include <stdio.h>
#include <stdlib.h>
#include <EduDS.h>

void printIntData(void *pData)
{
    int x = *(int *)pData;
    printf("%d ", x);
}

int IntCmp(const void *data1, const void *data2)
{
    return *(int*)data1 - *(int*)data2;
}

void Dequeue_printFront(Dequeue *dequeue)
{
    if (dequeue) {
        printf("Printing dequeue forwards!\n");
        printf("head = ");
        for (DLListNode *curr = dequeue->head; curr; curr = curr->nxt) {
            printf("%d -> ", *(int*)curr->pData);
        }
        printf("NULL\n");
    }
}

void Dequeue_printBack(Dequeue *dequeue)
{
    if (dequeue) {
        printf("Printing dequeue backwards!\n");
        printf("tail = ");
        for (DLListNode *curr = dequeue->tail; curr; curr = curr->prv) {
            printf("%d -> ", *(int*)curr->pData);
        }
        printf("NULL\n");
    }
}

int main(int argc, char *argv[])
{
    Dequeue *dequeue = Dequeue_init(NULL);
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrr[] = {43, 111, 4401, 4933, 0, 11, 4401, 00453, 9, 5};

    Dequeue_printFront(dequeue);
    Dequeue_printBack(dequeue);
    putchar('\n');
    for (int i = 0; i < 10; i++) {
        if (i < 5) {
            Dequeue_push(dequeue, &arr[i], NULL);
            printf("Pushed element %d!:\n", arr[i]);
            Dequeue_printFront(dequeue);
            putchar('\n');
        } else {
            Dequeue_inject(dequeue, &arr[i], NULL);
            printf("Injected element %d!:\n", arr[i]);
            Dequeue_printFront(dequeue);
            putchar('\n');
        }
    }

    Dequeue_printFront(dequeue);
    Dequeue_printBack(dequeue);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        void *p = Dequeue_eject(dequeue, NULL);
        
        if (p) {
            printf("Successfully ejected node %d!\n", *(int*)p);
            Dequeue_printFront(dequeue);
            Dequeue_printBack(dequeue);
            putchar('\n');
        } else {
            printf("Failed ejecting node!\n");
        }
    }

    for (int i = 0; i < 10; i++) {
        if (i < 5) {
            Dequeue_inject(dequeue, &arrr[i], NULL);
            printf("Injected element %d!:\n", arrr[i]);
            Dequeue_printFront(dequeue);
            putchar('\n');
        } else {
            Dequeue_push(dequeue, &arrr[i], NULL);
            printf("Pushed element %d!:\n", arrr[i]);
            Dequeue_printFront(dequeue);
            putchar('\n');
        }
    }

    for (int i = 0; i < 5; i++) {
        void *p = Dequeue_pop(dequeue, NULL);
        
        if (p) {
            printf("Successfully popped node %d!\n", *(int*)p);
            Dequeue_printFront(dequeue);
            Dequeue_printBack(dequeue);
            putchar('\n');
        } else {
            printf("Failed popped node!\n");
        }
    }
    
    Dequeue_printFront(dequeue);
    Dequeue_printBack(dequeue);
    putchar('\n');

    Dequeue_destroy(&dequeue, NULL, NULL);
    return 0;
}
