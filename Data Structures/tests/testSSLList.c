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
    SSLList *myList = newSSLList();
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            insertNodeSSLList(myList, &arr[i]);
        else
            appendNodeSSLList(myList, &arr[i]);
    }

    traverseSSLList(myList, printIntData);
    putchar('\n');

    //by this point the list is empty, so this line won't do anything
    deleteNodeSSLList(myList, &arr[6]);
    traverseSSLList(myList, printIntData);
    putchar('\n');

    for (int i = 0; i < 4; i++) {
        deleteNodeSSLList(myList, &arr[i]);
        traverseSSLList(myList, printIntData);
        putchar('\n');
    }

    deleteNodeSSLList(myList, &arr[4]);
    traverseSSLList(myList, printIntData);
    putchar('\n');

    deleteSSLList(&myList, NULL);
    return 0;
}
