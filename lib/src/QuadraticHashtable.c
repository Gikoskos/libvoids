/***********************************************\
*              QuadraticHashtable.c             *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include "QuadraticHashtable.h"
#include "HashFunctions.h"


static void rehash(QuadHashtable *table, UserDataCallback freeData);


QuadHashtable *QuadHash_init(size_t size, UserCompareCallback KeyCmp, UserHashFuncCallback Hash)
{
    QuadHashtable *quadtable = NULL;

    if (KeyCmp && size > 3) {

        quadtable = malloc(sizeof(QuadHashtable));

        //if the user didn't give a custom hashing algorithm, we default to either
        //the multiplication or division hashing methods
        if (!Hash) {

            //if the array size is a power of two
            if ( !(size & (size - 1)) ) //we default to mult
                quadtable->Hash = HashMult;
            else
                quadtable->Hash = HashDiv; //else we default to div which works better when the array size isn't a power of two

        } else {
            quadtable->Hash = Hash;
        }

        quadtable->KeyCmp = KeyCmp;
        quadtable->size = size;
        quadtable->array = calloc(quadtable->size, sizeof(HashArrayElement));
        quadtable->total_elements = 0;
    }


    return quadtable;
}

void rehash(QuadHashtable *table, UserDataCallback freeData)
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
                tmp_idx = (hash_idx + (offset * offset)) % table->size;

                if (!table->array[tmp_idx].occupied) {

                    table->array[tmp_idx] = old_array[i];

                    break;
                }

                offset++;

            } while (offset < table->size);

            continue;
        }

        if (old_array[i].deleted && freeData)
            freeData((void*)&old_array[i].item);

    }

    free(old_array);
}

void *QuadHash_insert(QuadHashtable *table, void *pData, void *pKey, size_t key_size, UserDataCallback freeData)
{
    void *new_key = NULL;

    if (table && pKey && key_size) {

        size_t key_hash = HashCode(pKey, key_size);
        size_t hash_idx = table->Hash(key_hash, table->size);
        size_t offset = 0, tmp_idx;

        do {
            tmp_idx = (hash_idx + (offset * offset)) % table->size;


            if (!table->array[tmp_idx].occupied) {

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


        if ( ((float)table->total_elements / table->size) >= 0.5 )
            rehash(table, freeData);
    }
        

    return new_key;
}

KeyValuePair QuadHash_delete(QuadHashtable *table, void *pKey, size_t key_size)
{
    KeyValuePair item = { 0 };

    if (table && pKey && key_size) {
        size_t hash_idx = table->Hash(HashCode(pKey, key_size), table->size);
        size_t offset = 0, tmp_idx;

        do {
            tmp_idx = (hash_idx + (offset * offset)) % table->size;

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

HashArrayElement *QuadHash_find(QuadHashtable *table, void *pKey, size_t key_size)
{
    HashArrayElement *to_find = NULL;

    if (table && pKey && key_size) {
        size_t hash_idx = table->Hash(HashCode(pKey, key_size), table->size);
        size_t offset = 0, tmp_idx;

        do {
            tmp_idx = (hash_idx + (offset * offset)) % table->size;

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

void QuadHash_destroy(QuadHashtable **table, UserDataCallback freeData)
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
