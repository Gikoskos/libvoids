#include <stdio.h>
#include <stdlib.h>
#include <GiDS.h>

void printIntData(void *pData)
{
    int x = *(int *)pData;
    printf("%d ", x);
}

int main(int argc, char *argv[])
{
    DLListNode *myList = NULL;
    int arr[] = {42, 2, 31, 4, 5, 55, 7, 77, 9, 232};

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            DLList_insert(&myList, &arr[i]);
        else
            DLList_append(&myList, &arr[i]);
    }

    DLList_traverse(myList, printIntData);
    putchar('\n');

    DLList_deleteNode(&myList, DLList_find(myList, &arr[6]));
    DLList_traverse(myList, printIntData);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        if (DLList_deleteNode(&myList, DLList_find(myList, &arr[i]))) {
            printf("\nDeleted node %d successfully!\n", arr[i]);
            DLList_traverse(myList, printIntData);
            putchar('\n');
        }
    }

    DLList_traverse(myList, printIntData);

    DLList_destroy(&myList, NULL);
    return 0;
}
