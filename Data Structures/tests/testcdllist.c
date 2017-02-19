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
        CDLList_insert(&myList, &arr[i]);
    }

    for (int i = 5; i < 10; i++) {
        CDLList_append(&myList, &arr[i]);
    }

    CDLList_traverse(myList, printIntData);

    putchar('\n');
    CDLList_deleteNode(&myList, CDLList_find(myList, &arr[6]));
    printf("DELETED: %d, LIST = ", arr[6]);
    CDLList_traverse(myList, printIntData);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        CDLList_deleteNode(&myList, CDLList_find(myList, &arr[i]));
        printf("DELETED: %d, LIST = ", arr[i]);
        CDLList_traverse(myList, printIntData);
        putchar('\n');
    }


    CDLList_destroy(&myList, NULL);
    return 0;
}
