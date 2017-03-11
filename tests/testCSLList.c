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


int main(int argc, char *argv[])
{
    CSLListNode *myList = NULL, *myOtherList = NULL;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrr[] = {43, 111, 4401, 4933, 0};

    for (int i = 0; i < 5; i++) {
        CSLList_insert(&myList, &arr[i], NULL);
    }

    for (int i = 5; i < 10; i++) {
        CSLList_append(&myList, &arr[i], NULL);
    }

    CSLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    CSLList_deleteNode(&myList, CSLList_find(myList, &arr[6], IntCmp, NULL), NULL);
    printf("DELETED: %d, LIST = ", arr[6]);
    CSLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    CSLList_insertAfter(CSLList_find(myList, &arr[4], IntCmp, NULL), &arr[9], NULL);
    printf("INSERTED: %d AFTER %d, LIST = ", arr[9], arr[4]);
    CSLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        CSLList_deleteNode(&myList, CSLList_find(myList, &arr[i], IntCmp, NULL), NULL);
        printf("DELETED: %d, LIST = ", arr[i]);
        CSLList_traverse(myList, printIntData, NULL);
        putchar('\n');
    }

    for (int i = 5; i < 10; i++) {
        CSLList_insert(&myList, &arr[i], NULL);
    }

    CSLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 4; i++) {
        CSLList_append(&myOtherList, &arrr[i], NULL);
    }

    CSLList_traverse(myOtherList, printIntData, NULL);
    putchar('\n');

    CSLList_concat(myList, myOtherList, NULL);

    CSLList_traverse(myList, printIntData, NULL);
    putchar('\n');
    CSLList_destroy(&myList, NULL, NULL);
    return 0;
}
