#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GiDS.h>
/*GiDS_API ChainedHashtable *ChainedHash_init(size_t size);

GiDS_API DictListNode *ChainedHash_insert(ChainedHashtable *table, void *pData, key_type key);

GiDS_API void *ChainedHash_delete(ChainedHashtable *table, key_type key);

GiDS_API DictListNode *ChainedHash_find(ChainedHashtable *table, key_type key);

GiDS_API void ChainedHash_destroy(ChainedHashtable **table, CustomDataCallback freeData);*/


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

void printChainedHashtable(ChainedHashtable *table)
{
    for (size_t i = 0; i < table->size; i++) {
        printf("List[%u] ", i);
        DictList_traverse(table->chains[i], printListItem);
        putchar('\n');
    }
}

int main(int argc, char *argv[])
{
    ChainedHashtable *table = ChainedHash_init(6);
    key_type keys[100];
    srand(time(NULL));

    for (size_t i = 0; i < 100; i++)
        keys[i] = (size_t)rand() % 100;

    printf("!! STARTING INSERTIONS !!");
    for (int i = 0; i < 6; i++) {
        int *new_data = newRandInt();

        if (!ChainedHash_insert(table, (void *)new_data, keys[i])) {
            printf("\nFailed inserting data %d with key %u\n", *new_data, keys[i]);
            free(new_data);
        } else {
            printf("\n==== Printing chained hashtable after inserting data %d with key %u ====\n", *new_data, keys[i]);
            printChainedHashtable(table);
        }
    }

    printf("\n\n!! STARTING DELETIONS !!");
    for (int i = 7; i >= 3; i--) {
        int *ptr;

        ptr = (int*)ChainedHash_delete(table, keys[i]);

        if (!ptr) {
            printf("\nFailed deleting node with key %u\n", keys[i]);
        } else {
            printf("\n==== Printing chained hashtable after deleting data %d with key %u ====\n", *ptr, keys[i]);
            printChainedHashtable(table);
            free(ptr);
        }
    }

    ChainedHash_destroy(&table, free);
    return 0;
}
