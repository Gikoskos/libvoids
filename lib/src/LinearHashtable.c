/***********************************************\
*               LinearHashtable.c               *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include "LinearHashtable.h"
#include "HashFunctions.h"


static void LinHash_rehash(LinHashtable *table);


LinHashtable *LinHash_init(size_t size, UserCompareCallback KeyCmp, UserHashFuncCallback Hash, int rehash)
{
    LinHashtable *lintable = NULL;

    if (KeyCmp && size > 3) {

        lintable = malloc(sizeof(LinHashtable));

        //if the user didn't give a custom hashing algorithm, we default to either
        //the multiplication or division hashing methods
        if (!Hash) {

            //if the array size is a power of two
            if ( !(size & (size - 1)) ) //we default to mult
                lintable->Hash = HashMult;
            else
                lintable->Hash = HashDiv; //else we default to div which works better when the array size isn't a power of two

        } else {
            lintable->Hash = Hash;
        }

        lintable->KeyCmp = KeyCmp;
        lintable->size = size;
        lintable->array = calloc(lintable->size, sizeof(HashArrayElement));
        lintable->rehash = rehash;
        lintable->total_elements = 0;
    }


    return lintable;
}

void LinHash_rehash(LinHashtable *table)
{
    HashArrayElement *old_array = table->array; //save the old array
    size_t old_size = table->size;

    table->size *= 2;
    table->array = calloc(table->size, sizeof(HashArrayElement));

    for (size_t i = 0; i < old_size; i++) {

        if (old_array[i].occupied) {

            size_t hash_idx = table->Hash(old_array[i].key_hash, table->size);
            size_t offset = 0, tmp_idx;

            do {
                tmp_idx = (hash_idx + offset) % table->size;

                if (!table->array[tmp_idx].occupied) {

                    table->array[tmp_idx] = old_array[i];

                    break;
                }

                offset++;

            } while (offset < table->size);

        }

    }

    free(old_array);
}

void *LinHash_insert(LinHashtable *table, void *pData, void *pKey, size_t key_size, UserDataCallback freeData)
{
    void *new_key = NULL;

    if (table && pKey && key_size && (table->total_elements < table->size)) {

        size_t key_hash = HashCode(pKey, key_size, table->size);
        size_t hash_idx = table->Hash(key_hash, table->size);
        size_t offset = 0, tmp_idx;

        do {
            tmp_idx = (hash_idx + offset) % table->size;

            //if we found an available position on the array, during linear probing, we store
            //our new key and data there, and save the pointer to that position to return it
            if (!table->array[tmp_idx].occupied) {

                //in case there is already a deleted element in the position that we're about to add
                //the new element to the array, we have to cleanup with the user-supplied cleanup function
                if (table->array[tmp_idx].deleted && freeData)
                    freeData((void *)&table->array[tmp_idx].item);

                table->array[tmp_idx].item.pData = pData;
                table->array[tmp_idx].item.pKey = pKey;
                table->array[tmp_idx].occupied = 1;
                table->array[tmp_idx].deleted = 0;
                //saving the pre-computed hashcode
                table->array[tmp_idx].key_hash = key_hash;

                table->total_elements++; //successful insertion
                new_key = pKey;
                break;

            } else if (!table->KeyCmp(table->array[tmp_idx].item.pKey, pKey)) {
                //if the same key is already in the table then the insertion has failed
                break;
            }

            offset++;

        } while (offset < table->size);

        if (table->rehash) //if the load factor is greater than 0.5 we rehash the table
            if ( ((float)table->total_elements / table->size) >= 0.5 )
                LinHash_rehash(table);
    }
        

    return new_key;
}

KeyValuePair LinHash_delete(LinHashtable *table, void *pKey, size_t key_size)
{
    KeyValuePair item = { 0 };

    if (table && pKey && key_size) {
        size_t hash_idx = table->Hash(HashCode(pKey, key_size, table->size), table->size);
        size_t offset = 0, tmp_idx;

        do {
            tmp_idx = (hash_idx + offset) % table->size;

            if (table->array[tmp_idx].occupied && table->KeyCmp(table->array[tmp_idx].item.pKey, pKey)) {
                table->array[tmp_idx].occupied = 0;
                table->array[tmp_idx].deleted = 1;
                item = table->array[tmp_idx].item;

                table->total_elements--; //successful deletion
                break;
            }

            offset++;

        } while (offset < table->size);
    }

    return item;
}

HashArrayElement *LinHash_find(LinHashtable *table, void *pKey, size_t key_size)
{
    HashArrayElement *to_find = NULL;

    if (table && pKey && key_size) {
        size_t hash_idx = table->Hash(HashCode(pKey, key_size, table->size), table->size);
        size_t offset = 0, tmp_idx;

        do {
            tmp_idx = (hash_idx + offset) % table->size;

            if (!table->array[tmp_idx].deleted && 
                table->array[tmp_idx].occupied &&
                !table->KeyCmp(table->array[tmp_idx].item.pKey, pKey)) {

                to_find = &table->array[tmp_idx];
                break;

            }

            offset++;

        } while (offset < table->size);

    }

    return to_find;
}

void LinHash_destroy(LinHashtable **table, UserDataCallback freeData)
{
    if (table && *table) {

        for (size_t i = 0; i < (*table)->size; i++)
            if (freeData && ((*table)->array[i].occupied || (*table)->array[i].deleted))
                freeData((void *)&(*table)->array[i].item);

        free((*table)->array);
        free(*table);
        *table = NULL;
    }
}
