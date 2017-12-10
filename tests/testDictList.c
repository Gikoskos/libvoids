#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <voids.h>


int *newRandInt(int range)
{
    int *p = malloc(sizeof(int));

    if (range)
        *p = rand()%range + 1;
    else
        *p = rand();

    return p;
}

int compareInts(const void *key1, const void *key2)
{
    return *(int*)key1 - *(int*)key2;
}

void freeKeyValuePair(void *param)
{
    KeyValuePair *item = (KeyValuePair *)param;

    free(item->pKey);
    free(item->pData);
}

void printListItem(void *pData)
{
    KeyValuePair *item = (KeyValuePair *)pData;
    printf("->(key=%d, data=%d) ", *(int*)item->pKey, *(int*)item->pData);
}

int main(int argc, char *argv[])
{
    DictListNode *dict = NULL;

    srand(time(NULL));


    printf("!! STARTING INSERTIONS !!\n");
    for (int i = 0; i < 6; i++) {
        int *new_data = newRandInt(0);
        int *new_key = newRandInt(100);

        if (!DictList_insert(&dict, (void *)new_data, (void *)new_key, compareInts, NULL)) {
            printf("\nFailed inserting node (key=%d, data=%d)\n", *new_key, *new_data);
            free(new_data);
            free(new_key);
        } else {
            printf("\n==== Printing list after inserting node (key=%d, data=%d) ====\n", *new_key, *new_data);
            DictList_traverse(dict, printListItem, NULL);
            putchar('\n');
        }
    }

    printf("\n\n!! STARTING DELETIONS !!\n");
    for (int i = 1; i < 41; i++) {
        KeyValuePair deleted = DictList_deleteByKey(&dict, (void *)&i, compareInts, NULL);

        if (deleted.pKey) {
            printf("\n==== Printing list after deleting node (key=%d, data=%d) ====\n", *(int*)deleted.pKey, *(int*)deleted.pData);
            DictList_traverse(dict, printListItem, NULL);
            putchar('\n');
            freeKeyValuePair((void*)&deleted);
        }
    }

    printf("\n\n!! STARTING APPENDS !!\n");
    for (int i = 0; i < 6; i++) {
        int *new_data = newRandInt(0);
        int *new_key = newRandInt(100);

        if (!DictList_append(&dict, (void *)new_data, (void *)new_key, compareInts, NULL)) {
            printf("Failed appending node (key=%d, data=%d)\n", *new_key, *new_data);
            free(new_data);
            free(new_key);
        } else {
            printf("\n==== Printing list after appending node (key=%d, data=%d) ====\n", *new_key, *new_data);
            DictList_traverse(dict, printListItem, NULL);
            putchar('\n');
        }
    }

    DictList_destroy(&dict, freeKeyValuePair, NULL);
    return 0;
}
