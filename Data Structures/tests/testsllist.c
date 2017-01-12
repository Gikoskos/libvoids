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
    SLListNode *myList = NULL;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++) {
        insertNodeSLList(&myList, &arr[i]);
    }

    printSLList(myList, printIntData);

    //by this point the list is empty, so this line won't do anything
    deleteNodeSLList(&myList, findNodeSLList(myList, &arr[6]));
    for (int i = 0; i < 4; i++) {
        deleteNodeSLList(&myList, findNodeSLList(myList, &arr[i]));
    }

    printSLList(myList, printIntData);

    deleteSLList(&myList, NULL);
    return 0;
}
