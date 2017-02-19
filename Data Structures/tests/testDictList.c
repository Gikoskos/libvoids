#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GiDS.h>


int *newRandInt(void)
{
    int *p = malloc(sizeof(int));

    *p = (int)rand();
    return p;
}

void printListItem(void *pData)
{
    DictListItem *x = (DictListItem *)pData;
    printf("->(key=%u, data=%d) ", x->key, *(int*)x->pData);
}

int main(int argc, char *argv[])
{
    DictListNode *dict = NULL;
    key_type keys[100];
    srand(time(NULL));

    for (size_t i = 0; i < 100; i++)
        keys[i] = (size_t)rand() % 100;

    printf("!! STARTING INSERTIONS !!\n");
    for (int i = 0; i < 6; i++) {
        int *new_data = newRandInt();

        if (!DictList_insert(&dict, (void *)new_data, keys[i])) {
            printf("Failed inserting data %d with key %u\n", *new_data, keys[i]);
            free(new_data);
        } else {
            printf("\n==== Printing list after inserting data %d with key %u ====\n", *new_data, keys[i]);
            DictList_traverse(dict, printListItem);
            putchar('\n');
        }
    }

    printf("\n\n!! STARTING DELETIONS !!\n");
    for (int i = 7; i >= 3; i--) {
        int *ptr;

        ptr = (int*)DictList_deleteByKey(&dict, keys[i]);

        if (!ptr) {
            printf("Failed deleting node with key %u\n", keys[i]);
        } else {
            printf("\n==== Printing list after deleting data %d with key %u ====\n", *ptr, keys[i]);
            DictList_traverse(dict, printListItem);
            putchar('\n');
            free(ptr);
        }
    }

    printf("\n\n!! STARTING APPENDS !!\n");
    for (int i = 42; i < 50; i++) {
        int *new_data = newRandInt();

        if (!DictList_append(&dict, (void *)new_data, keys[i])) {
            printf("Failed appending data %d with key %u\n", *new_data, keys[i]);
            free(new_data);
        } else {
            printf("\n==== Printing list after appending data %d with key %u ====\n", *new_data, keys[i]);
            DictList_traverse(dict, printListItem);
            putchar('\n');
        }
    }

    DictList_destroy(&dict, free);
    return 0;
}
