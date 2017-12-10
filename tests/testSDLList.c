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
    SDLList *myList = SDLList_init(NULL), *myOtherList = SDLList_init(NULL);
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrr[] = {43, 111, 4401, 4933, 0, 11, 4401, 00453, 9, 5};

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            SDLList_insert(myList, &arr[i], NULL);
        else
            SDLList_append(myList, &arr[i], NULL);
    }

    SDLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    //by this point the list is empty, so this line won't do anything
    SDLList_deleteData(myList, &arr[6], IntCmp, NULL);
    SDLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        if (SDLList_deleteData(myList, &arr[i], IntCmp, NULL)) {
            printf("\nSuccessfully deleted node %d!\n", arr[i]);
            SDLList_traverse(myList, printIntData, NULL);
            putchar('\n');
        }
    }

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            SDLList_insert(myList, &arr[i], NULL);
        else
            SDLList_append(myList, &arr[i], NULL);
    }

    for (int i = 5; i < 15; i++) {
        vdsErrCode err;
        if (SDLList_find(myList, &i, IntCmp, &err)) {
            printf("\nFound node %d \"%s\"!\n", i, VdsErrString(err));
        } else {
            printf("\nFailed finding node %d with error \"%s\"!\n", i, VdsErrString(err));
        }
    }

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            SDLList_insert(myOtherList, &arrr[i], NULL);
        else
            SDLList_append(myOtherList, &arrr[i], NULL);
    }

    printf("\nPrinting myOtherList: ");
    SDLList_traverse(myOtherList, printIntData, NULL);
    putchar('\n');

    SDLList_concat(myOtherList, myList, NULL);
    printf("\n\nPrinting myOtherList+myList: ");
    SDLList_traverse(myOtherList, printIntData, NULL);
    putchar('\n');

    printf("\nmyOtherList[12] = %d\n", *(int*)SDLList_at(myOtherList, 12, NULL)->pData);
    SDLList_destroy(&myOtherList, NULL, NULL);
    return 0;
}
