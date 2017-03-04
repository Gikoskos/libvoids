#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <EduDS.h>
//testQuadraticHashtable

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

void printHashtable(QuadHashtable *table)
{
    for (size_t i = 0; i < table->size; i++) {

        if (table->array[i].occupied) {
            printf("[%u] = (key=%d, data=%d) ", i, *(int*)table->array[i].item.pKey, *(int*)table->array[i].item.pData);
        } else {
            if (table->array[i].deleted) {
                printf("[%u] = (key=%d, data=%d) (DELETED)", i, *(int*)table->array[i].item.pKey, *(int*)table->array[i].item.pData);
            } else {
                printf("[%u] = (EMPTY) ", i);
            }
        }

        putchar('\n');
    }
}

int main(int argc, char *argv[])
{
    QuadHashtable *table = QuadHash_init(7, compareInts, NULL);

    srand(time(NULL));

    printf("!! STARTING INSERTIONS !!");
    for (int i = 0; i < 8; i++) {
        int *new_data = newRandInt(0);
        int *new_key = newRandInt(10);

        if (!QuadHash_insert(table, (void *)new_data, (void *)new_key, sizeof(*new_key), freeKeyValuePair)) {
            printf("\nFailed inserting data %d with key %d\n", *new_data, *new_key);
            free(new_data);
            free(new_key);
        } else {
            printf("\n==== Printing quadratic hashtable after inserting node (key=%d, data= %d) ====\n", *new_key, *new_data);
            printHashtable(table);
        }
    }

    printf("\n\n!! STARTING DELETIONS !!");
    for (int i = 1; i <= 4; i++) {
        KeyValuePair item;

        item = QuadHash_delete(table, &i, sizeof i);

        if (item.pKey) {
            printf("\n==== Printing quadratic hashtable after deleting node (key=%d, data= %d) ====\n", *(int*)item.pKey, *(int*)item.pData);
            printHashtable(table);
        }
    }

    printf("\n\n!! STARTING INSERTIONS !!");
    for (int i = 0; i < 4; i++) {
        int *new_data = newRandInt(0);
        int *new_key = newRandInt(10);

        if (!QuadHash_insert(table, (void *)new_data, (void *)new_key, sizeof(*new_key), freeKeyValuePair)) {
            printf("\nFailed inserting data %d with key %d\n", *new_data, *new_key);
            free(new_data);
            free(new_key);
        } else {
            printf("\n==== Printing quadratic hashtable after inserting node (key=%d, data= %d) ====\n", *new_key, *new_data);
            printHashtable(table);
        }
    }

    printf("\n\n!! TESTING FIND !!");
    for (int i = 1; i <= 10; i++) {

        if (!QuadHash_find(table, (void *)&i, sizeof(i))) {
            printf("\nFind failed on key %d\n", i);
        } else {
            printf("\nFind was successful on key %d\n", i);
        }
    }


    QuadHash_destroy(&table, freeKeyValuePair);
    return 0;
}
