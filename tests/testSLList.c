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
    SLListNode *myList = NULL, *myOtherList = NULL;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrr[] = {43, 111, 4401, 4933, 0, 11, 4401, 00453, 9, 5};

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            SLList_insert(&myList, &arr[i], NULL);
        else
            SLList_append(&myList, &arr[i], NULL);
    }

    SLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    SLList_deleteNode(&myList, SLList_find(myList, &arr[6], IntCmp, NULL), NULL);

    SLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 4; i++) {
        SLList_deleteNode(&myList, SLList_find(myList, &arr[i], IntCmp, NULL), NULL);
    }

    SLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            SLList_insert(&myOtherList, &arrr[i], NULL);
        else
            SLList_append(&myOtherList, &arrr[i], NULL);
    }

    SLList_traverse(myOtherList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 4; i++) {
        SLList_deleteData(&myOtherList, &arrr[i], IntCmp, NULL);
    }

    SLList_traverse(myOtherList, printIntData, NULL);
    putchar('\n');

    SLList_concat(myOtherList, myList, NULL);
    SLList_traverse(myOtherList, printIntData, NULL);
    putchar('\n');
    SLList_destroy(&myOtherList, NULL, NULL);
    return 0;
}
