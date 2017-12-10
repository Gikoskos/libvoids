 /********************
 *  QuadraticHashtable.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "MemoryAllocation.h"
#include "QuadraticHashtable.h"
#include "HashFunctions.h"

#define SET_OCCUPIED(x) (x) = 1
#define SET_DELETED(x) (x) = 2

#define IS_OCCUPIED(x) ((x) == 1)
#define IS_DELETED(x) ((x) == 2)


static int rehash(QuadHashtable *table, vdsUserDataFunc freeData);


QuadHashtable *QuadHash_init(size_t size,
                             vdsUserCompareFunc KeyCmp,
                             vdsUserHashFunc Hash,
                             vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    QuadHashtable *quadtable = NULL;

    if (KeyCmp && size > 3) {

        quadtable = VdsMalloc(sizeof(QuadHashtable));

        if (quadtable) {

            quadtable->array = VdsCalloc(size, sizeof(HashArrayElement));

            if (quadtable->array) {
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
                quadtable->total_elements = 0;

            } else {
                VdsFree(quadtable);
                quadtable = NULL;
                tmp_err = VDS_MALLOC_FAIL;
            }

        } else
            tmp_err = VDS_MALLOC_FAIL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return quadtable;
}

int rehash(QuadHashtable *table, vdsUserDataFunc freeData)
{
    HashArrayElement *old_array = table->array; //save the old array
    size_t old_size = table->size;

    table->size *= 2;

    table->array = VdsCalloc(table->size, sizeof(HashArrayElement));
    if (!table->array) {
        table->array = old_array;
        return 0;
    }

    for (size_t i = 0; i < old_size; i++) {

        if (IS_OCCUPIED(old_array[i].state)) {

            size_t hash_idx = table->Hash(old_array[i].key_hash, table->size);
            size_t offset = 0, tmp_idx;

            do {
                tmp_idx = (hash_idx + (offset * offset)) % table->size;

                if (!IS_OCCUPIED(table->array[tmp_idx].state)) {

                    table->array[tmp_idx] = old_array[i];

                    break;
                }

                offset++;

            } while (offset < table->size);

            continue;
        }

        if (IS_DELETED(old_array[i].state) && freeData)
            freeData((void*)&old_array[i].item);

    }

    VdsFree(old_array);

    return 1;
}

void *QuadHash_insert(QuadHashtable *table,
                      void *pData,
                      void *pKey,
                      size_t key_size,
                      vdsUserDataFunc freeData,
                      vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    void *new_key = NULL;

    if (table && pKey && key_size) {

        size_t key_hash = HashCode(pKey, key_size);
        size_t hash_idx = table->Hash(key_hash, table->size);
        size_t offset = 0, tmp_idx;

        do {
            tmp_idx = (hash_idx + (offset * offset)) % table->size;


            if (!IS_OCCUPIED(table->array[tmp_idx].state)) {

                if (IS_DELETED(table->array[tmp_idx].state) && freeData)
                    freeData((void *)&table->array[tmp_idx].item);

                table->array[tmp_idx].item.pData = pData;
                table->array[tmp_idx].item.pKey = pKey;
                SET_OCCUPIED(table->array[tmp_idx].state);
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

        //@TODO: handle possible case where insertion fails and we have to rehash the table
        //when offset >= table->size and try to re-insert the element with a recursive call
        //to QuadHash_insert

        if ( ((float)table->total_elements / table->size) >= 0.5 )
            if (!rehash(table, freeData))
                tmp_err = VDS_MALLOC_FAIL;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);        

    return new_key;
}

KeyValuePair QuadHash_delete(QuadHashtable *table,
                             void *pKey,
                             size_t key_size,
                             vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    KeyValuePair item = { 0 };

    if (table && pKey && key_size) {
        size_t hash_idx = table->Hash(HashCode(pKey, key_size), table->size);
        size_t offset = 0, tmp_idx;

        do {
            tmp_idx = (hash_idx + (offset * offset)) % table->size;

            if (IS_OCCUPIED(table->array[tmp_idx].state) && table->KeyCmp(table->array[tmp_idx].item.pKey, pKey)) {

                SET_DELETED(table->array[tmp_idx].state);
                item = table->array[tmp_idx].item;

                table->total_elements--; //successful deletion

                break;
            }

            offset++;

        } while (offset < table->size);

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return item;
}

HashArrayElement *QuadHash_find(QuadHashtable *table,
                                void *pKey,
                                size_t key_size,
                                vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    HashArrayElement *to_find = NULL;

    if (table && pKey && key_size) {
        size_t hash_idx = table->Hash(HashCode(pKey, key_size), table->size);
        size_t offset = 0, tmp_idx;

        do {
            tmp_idx = (hash_idx + (offset * offset)) % table->size;

            if (IS_OCCUPIED(table->array[tmp_idx].state) &&
                !table->KeyCmp(table->array[tmp_idx].item.pKey, pKey)) {

                to_find = &table->array[tmp_idx];
                break;

            }

            offset++;

        } while (offset < table->size);

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return to_find;
}

void QuadHash_destroy(QuadHashtable **table,
                      vdsUserDataFunc freeData,
                      vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (table && *table) {

        for (size_t i = 0; i < (*table)->size; i++)
            if (freeData && (IS_OCCUPIED((*table)->array[i].state) || IS_DELETED((*table)->array[i].state)))
                freeData((void *)&(*table)->array[i].item);

        VdsFree((*table)->array);
        VdsFree(*table);
        *table = NULL;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
