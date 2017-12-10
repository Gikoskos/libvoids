#include <stdio.h>
#include <stdlib.h>
#include <voids.h>

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
    DLListNode *myList = NULL, *myOtherList = NULL;
    int arr[] = {42, 2, 31, 4, 5, 55, 7, 77, 9, 232};
    int arrr[] = {43, 111, 4401, 4933, 0};

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            DLList_insert(&myList, &arr[i], NULL);
        else
            DLList_append(&myList, &arr[i], NULL);
    }

    DLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    DLList_deleteNode(&myList, DLList_find(myList, &arr[6], IntCmp, NULL), NULL);
    DLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        if (DLList_deleteNode(&myList, DLList_find(myList, &arr[i], IntCmp, NULL), NULL)) {
            printf("\nDeleted node %d successfully!\n", arr[i]);
            DLList_traverse(myList, printIntData, NULL);
            putchar('\n');
        }
    }

    DLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            DLList_insert(&myList, &arr[i], NULL);
        else
            DLList_append(&myList, &arr[i], NULL);
    }
    printf("printing myList: ");
    DLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 5; i++) {
        if (i < 2)
            DLList_insert(&myOtherList, &arr[i], NULL);
        else
            DLList_append(&myOtherList, &arr[i], NULL);
    }

    printf("printing myOtherList: ");
    DLList_traverse(myOtherList, printIntData, NULL);
    putchar('\n');

    DLList_concat(myOtherList, myList, NULL);

    printf("printing combined list: ");
    DLList_traverse(myOtherList, printIntData, NULL);
    putchar('\n');

    printf("\nindex at 9: %d\n", *(int*)DLList_at(myOtherList, 9, NULL)->pData);
    DLList_destroy(&myOtherList, NULL, NULL);
    return 0;
}
