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
    CDLListNode *myList = NULL;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 5; i++) {
        insertFirstNodeCDLList(&myList, &arr[i]);
    }

    for (int i = 5; i < 10; i++) {
        insertLastNodeCDLList(&myList, &arr[i]);
    }

    printCDLList(myList, printIntData);

    putchar('\n');
    deleteNodeCDLList(&myList, findNodeCDLList(myList, &arr[6]));
    printf("DELETED: %d, LIST = ", arr[6]);
    printCDLList(myList, printIntData);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        deleteNodeCDLList(&myList, findNodeCDLList(myList, &arr[i]));
        printf("DELETED: %d, LIST = ", arr[i]);
        printCDLList(myList, printIntData);
        putchar('\n');
    }


    //deleteCDLList(&myList, NULL);
    return 0;
}
