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
            insertNodeDLList(&myList, &arr[i]);
        else
            appendNodeDLList(&myList, &arr[i]);
    }

    printDLList(myList, printIntData);
    putchar('\n');

    deleteNodeDLList(&myList, findNodeDLList(myList, &arr[6]));
    printDLList(myList, printIntData);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        if (deleteNodeDLList(&myList, findNodeDLList(myList, &arr[i]))) {
            printf("\nDeleted node %d successfully!\n", arr[i]);
            printDLList(myList, printIntData);
            putchar('\n');
        }
    }

    printDLList(myList, printIntData);

    deleteDLList(&myList, NULL);
    return 0;
}
