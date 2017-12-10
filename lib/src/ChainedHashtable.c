 /********************
 *  ChainedHashTable.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "MemoryAllocation.h"
#include "ChainedHashtable.h"
#include "HashFunctions.h"


ChainedHashtable *ChainedHash_init(size_t size,
                                   vdsUserCompareFunc KeyCmp,
                                   vdsUserHashFunc Hash,
                                   vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    ChainedHashtable *chtable = NULL;

    if (KeyCmp && size > 3) {

        chtable = VdsMalloc(sizeof(ChainedHashtable));

        if (chtable) {

            chtable->chains = VdsCalloc(size, sizeof(DictListNode*));

            if (chtable->chains) {
                //if the user didn't give a custom hashing algorithm, we default to either
                //the multiplication or division hashing methods
                if (!Hash) {

                    //if the array size is a power of two
                    if ( !(size & (size - 1)) ) //we default to mult
                        chtable->Hash = HashMult;
                    else
                        chtable->Hash = HashDiv; //else we default to div which works better when the array size isn't a power of two

                } else {
                    chtable->Hash = Hash;
                }

                chtable->KeyCmp = KeyCmp;
                chtable->size = size;

            } else {
                tmp_err = VDS_MALLOC_FAIL;
                VdsFree(chtable);
                chtable = NULL;
            }

        } else
            tmp_err = VDS_MALLOC_FAIL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return chtable;
}

DictListNode *ChainedHash_insert(ChainedHashtable *table,
                                 void *pData,
                                 void *pKey,
                                 size_t key_size,
                                 vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DictListNode *new_node = NULL;

    if (table && pKey && key_size)
        new_node = DictList_insert(&table->chains[ table->Hash(HashCode(pKey, key_size), table->size) ], pData, pKey, table->KeyCmp, &tmp_err);
    else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

KeyValuePair ChainedHash_delete(ChainedHashtable *table,
                                void *pKey,
                                size_t key_size,
                                vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    KeyValuePair item = { 0 };

    if (table && pKey && key_size)
        item = DictList_deleteByKey(&table->chains[ table->Hash(HashCode(pKey, key_size), table->size) ], pKey, table->KeyCmp, &tmp_err);
    else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return item;
}

DictListNode *ChainedHash_find(ChainedHashtable *table,
                               void *pKey,
                               size_t key_size,
                               vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DictListNode *to_find = NULL;

    if (table && pKey && key_size)
        to_find = DictList_findByKey(table->chains[ table->Hash(HashCode(pKey, key_size), table->size) ], pKey, table->KeyCmp, &tmp_err);
    else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return to_find;
}

void ChainedHash_destroy(ChainedHashtable **table,
                         vdsUserDataFunc freeData,
                         vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    if (table && *table) {

        for (size_t i = 0; i < (*table)->size; i++)
            DictList_destroy(&(*table)->chains[i], freeData, NULL);

        VdsFree((*table)->chains);
        VdsFree(*table);
        *table = NULL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
