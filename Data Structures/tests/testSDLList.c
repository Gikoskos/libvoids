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
    SDLList *myList = newSDLList();
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            insertNodeSDLList(myList, &arr[i]);
        else
            appendNodeSDLList(myList, &arr[i]);
    }

    traverseSDLList(myList, printIntData);
    putchar('\n');

    //by this point the list is empty, so this line won't do anything
    deleteNodeSDLList(myList, &arr[6]);
    traverseSDLList(myList, printIntData);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        if (deleteNodeSDLList(myList, &arr[i])) {
            printf("\nSuccessfully deleted node %d!\n", arr[i]);
            traverseSDLList(myList, printIntData);
            putchar('\n');
        }
    }

    deleteSDLList(&myList, NULL);
    return 0;
}
