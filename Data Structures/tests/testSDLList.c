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
    SDLList *myList = SDLList_init();
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++) {
        if (i < 5)
            SDLList_insert(myList, &arr[i]);
        else
            SDLList_append(myList, &arr[i]);
    }

    SDLList_traverse(myList, printIntData);
    putchar('\n');

    //by this point the list is empty, so this line won't do anything
    SDLList_deleteNode(myList, &arr[6]);
    SDLList_traverse(myList, printIntData);
    putchar('\n');

    for (int i = 0; i < 10; i++) {
        if (SDLList_deleteNode(myList, &arr[i])) {
            printf("\nSuccessfully deleted node %d!\n", arr[i]);
            SDLList_traverse(myList, printIntData);
            putchar('\n');
        }
    }

    SDLList_destroy(&myList, NULL);
    return 0;
}
