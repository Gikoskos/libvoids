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
        insertNodeDLList(&myList, &arr[i]);
    }

    printDLList(myList, printIntData);

    //by this point the list is empty, so this line won't do anything
    deleteNodeDLList(&myList, findNodeDLList(myList, &arr[6]));
    for (int i = 0; i < 10; i++) {
        deleteNodeDLList(&myList, findNodeDLList(myList, &arr[i]));
    }

    printDLList(myList, printIntData);

    deleteDLList(&myList, NULL);
    return 0;
}
