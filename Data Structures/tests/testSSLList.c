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
    SSLList *myList = SSLList_init();
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            SSLList_insert(myList, &arr[i]);
        else
            SSLList_append(myList, &arr[i]);
    }

    SSLList_traverse(myList, printIntData);
    putchar('\n');

    //by this point the list is empty, so this line won't do anything
    SSLList_deleteNode(myList, &arr[6]);
    SSLList_traverse(myList, printIntData);
    putchar('\n');

    for (int i = 0; i < 4; i++) {
        SSLList_deleteNode(myList, &arr[i]);
        SSLList_traverse(myList, printIntData);
        putchar('\n');
    }

    SSLList_deleteNode(myList, &arr[4]);
    SSLList_traverse(myList, printIntData);
    putchar('\n');

    SSLList_destroy(&myList, NULL);
    return 0;
}
