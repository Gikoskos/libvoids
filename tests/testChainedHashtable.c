#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <EduDS.h>


int *newRandInt(int range)
{
    int *p = malloc(sizeof(int));

    if (range) {
        *p = rand()%range + 1;
    } else {
        *p = rand();
    }

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

void printListItem(void *param)
{
    KeyValuePair *item = (KeyValuePair *)param;

    printf("->(key=%d, data=%d) ", *(int*)item->pKey, *(int*)item->pData);
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
    ChainedHashtable *table = ChainedHash_init(7, compareInts, NULL);

    srand(time(NULL));

    printf("!! STARTING INSERTIONS !!");
    for (int i = 0; i < 8; i++) {
        int *new_data = newRandInt(0);
        int *new_key = newRandInt(100);

        if (!ChainedHash_insert(table, (void *)new_data, (void *)new_key, sizeof(*new_key))) {
            printf("\nFailed inserting data %d with key %d\n", *new_data, *new_key);
            free(new_data);
            free(new_key);
        } else {
            printf("\n==== Printing chained hashtable after inserting node (key=%d, data= %d) ====\n", *new_key, *new_data);
            printChainedHashtable(table);
        }
    }

    printf("\n\n!! STARTING DELETIONS !!");
    for (int i = 1; i <= 40; i++) {
        KeyValuePair item;

        item = ChainedHash_delete(table, &i, sizeof i);

        if (item.pKey) {
            printf("\n==== Printing chained hashtable after deleting node (key=%d, data= %d) ====\n", *(int*)item.pKey, *(int*)item.pData);
            printChainedHashtable(table);
            free(item.pKey);
            free(item.pData);
        }
    }

    ChainedHash_destroy(&table, freeKeyValuePair);
    return 0;
}
