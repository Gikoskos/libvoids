#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    CDLListNode *myList = NULL, *myOtherList = NULL;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrr[] = {43, 111, 4401, 4933, 0};

    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        CDLList_insert(&myList, &arr[i], NULL);
    }

    for (int i = 5; i < 10; i++) {
        CDLList_append(&myList, &arr[i], NULL);
    }

    CDLList_traverse(myList, printIntData, NULL);

    putchar('\n');
    CDLList_deleteNode(&myList, CDLList_find(myList, &arr[6], IntCmp, NULL), NULL);
    printf("DELETED: %d, LIST = ", arr[6]);
    CDLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 15; i++) {

        if (CDLList_deleteNode(&myList, CDLList_find(myList, &arr[i], IntCmp, NULL), NULL)) {
            printf("DELETED: %d, LIST = ", arr[i]);
            CDLList_traverse(myList, printIntData, NULL);
            putchar('\n');
        }
    }


    for (int i = 0; i < 10; i++) {
        CDLList_append(&myList, &arr[i], NULL);
    }

    CDLListNode *tmp = CDLList_at(myList, 0, NULL);
    printf("Index at 0: %d\n", *(int*)tmp->pData);

    tmp = CDLList_at(myList, 11, NULL);
    if (tmp)
        printf("Index at 11: %d\n", *(int*)tmp->pData);

    tmp = CDLList_at(myList, 6, NULL);
    printf("Index at 6: %d\n", *(int*)tmp->pData);

    
    tmp = CDLList_at(myList, 9, NULL);
    printf("Index at 9: %d\n", *(int*)tmp->pData);

    CDLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 5; i++) {
        CDLList_insert(&myOtherList, &arrr[i], NULL);
    }

    CDLList_concat(myList, myOtherList, NULL);
    CDLList_traverse(myList, printIntData, NULL);
    putchar('\n');

    for (int i = 0; i < 5; i++) {
        CDLList_append(&myList, &arrr[i], NULL);
    }
    CDLList_traverse(myList, printIntData, NULL);
    putchar('\n');
    printf("Index at 10: %d\n", *(int*)(CDLList_at(myList, 6, NULL)->pData));
    CDLList_destroy(&myList, NULL, NULL);
    return 0;
}
