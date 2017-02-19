#include <stdio.h>
#include <stdlib.h>
#include <EduDS.h>

void printIntData(void *pData)
{
    int x = *(int *)pData;
    printf("%d ", x);
}

int main(int argc, char *argv[])
{
    CSLListNode *myList = NULL;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 5; i++) {
        CSLList_insert(&myList, &arr[i]);
    }

    for (int i = 5; i < 10; i++) {
        CSLList_append(&myList, &arr[i]);
    }

    CSLList_traverse(myList, printIntData);
    putchar('\n');

    CSLList_deleteNode(&myList, CSLList_find(myList, &arr[6]));
    printf("DELETED: %d, LIST = ", arr[6]);
    CSLList_traverse(myList, printIntData);
    putchar('\n');

    CSLList_insertAfter(CSLList_find(myList, &arr[4]), &arr[9]);
    printf("INSERTED: %d AFTER %d, LIST = ", arr[9], arr[4]);
    CSLList_traverse(myList, printIntData);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        CSLList_deleteNode(&myList, CSLList_find(myList, &arr[i]));
        printf("DELETED: %d, LIST = ", arr[i]);
        CSLList_traverse(myList, printIntData);
        putchar('\n');
    }

    CSLList_destroy(&myList, NULL);
    return 0;
}
