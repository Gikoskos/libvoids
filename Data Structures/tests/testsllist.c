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
        if (i < 5)
            SLList_insert(&myList, &arr[i]);
        else
            SLList_append(&myList, &arr[i]);
    }

    SLList_traverse(myList, printIntData);
    putchar('\n');

    SLList_deleteNode(&myList, SLList_find(myList, &arr[6]));

    SLList_traverse(myList, printIntData);
    putchar('\n');

    for (int i = 0; i < 4; i++) {
        SLList_deleteNode(&myList, SLList_find(myList, &arr[i]));
    }

    SLList_traverse(myList, printIntData);
    putchar('\n');

    SLList_destroy(&myList, NULL);
    return 0;
}
