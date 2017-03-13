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
    SSLList *myList = SSLList_init(NULL), *myOtherList = SSLList_init(NULL);
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrr[] = {43, 111, 4401, 4933, 0, 11, 4401, 00453, 9, 5};


    for (int i = 0; i < 10; i++) {
        if (i < 5)
            SSLList_insert(myList, &arr[i], NULL);
        else
            SSLList_append(myList, &arr[i], NULL);
    }

    SSLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    //by this point the list is empty, so this line won't do anything
    SSLList_deleteData(myList, &arr[6], IntCmp, NULL);
    SSLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 4; i++) {
        SSLList_deleteData(myList, &arr[i], IntCmp, NULL);
        SSLList_traverse(myList, printIntData, NULL);
        putchar('\n');
    }

    SSLList_deleteData(myList, &arr[4], IntCmp,NULL);
    SSLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            SSLList_insert(myOtherList, &arrr[i], NULL);
        else
            SSLList_append(myOtherList, &arrr[i], NULL);
    }

    printf("Testing find on myList!!!\n");
    for (int i = 5; i < 15; i++) {
        EdsErrCode err;
        if (SSLList_find(myList, &i, IntCmp, &err)) {
            printf("\nFound node %d \"%s\"!\n", i, EdsErrString(err));
        } else {
            printf("\nFailed finding node %d with error \"%s\"!\n", i, EdsErrString(err));
        }
    }

    printf("\nPrinting myOtherList: ");
    SSLList_traverse(myOtherList, printIntData, NULL);
    putchar('\n');

    SSLList_concat(myOtherList, myList, NULL);
    printf("\n\nPrinting myOtherList+myList: ");
    SSLList_traverse(myOtherList, printIntData, NULL);
    putchar('\n');

    printf("\nmyOtherList[12] = %d\n", *(int*)SSLList_at(myOtherList, 12, NULL)->pData);


    SSLList_destroy(&myOtherList, NULL, NULL);
    return 0;
}
