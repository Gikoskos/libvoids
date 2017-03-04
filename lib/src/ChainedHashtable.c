/***********************************************\
*               ChainedHashTable.c              *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include "ChainedHashtable.h"
#include "HashFunctions.h"


ChainedHashtable *ChainedHash_init(size_t size, UserCompareCallback KeyCmp, UserHashFuncCallback Hash)
{
    ChainedHashtable *chtable = NULL;

    if (KeyCmp && size > 3) {

        chtable = malloc(sizeof(ChainedHashtable));

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
        chtable->chains = calloc(size, sizeof(DictListNode*));
        chtable->size = size;
    }


    return chtable;
}

DictListNode *ChainedHash_insert(ChainedHashtable *table, void *pData, void *pKey, size_t key_size)
{
    DictListNode *new_node = NULL;

    if (table && pKey && key_size)
        new_node = DictList_insert(&table->chains[ table->Hash(HashCode(pKey, key_size, table->size), table->size) ], pData, pKey, table->KeyCmp);

    return new_node;
}

KeyValuePair ChainedHash_delete(ChainedHashtable *table, void *pKey, size_t key_size)
{
    KeyValuePair item = { 0 };

    if (table && pKey && key_size)
        item = DictList_deleteByKey(&table->chains[ table->Hash(HashCode(pKey, key_size, table->size), table->size) ], pKey, table->KeyCmp);

    return item;
}

DictListNode *ChainedHash_find(ChainedHashtable *table, void *pKey, size_t key_size)
{
    DictListNode *to_find = NULL;

    if (table && pKey && key_size)
        to_find = DictList_findByKey(table->chains[ table->Hash(HashCode(pKey, key_size, table->size), table->size) ], pKey, table->KeyCmp);

    return to_find;
}

void ChainedHash_destroy(ChainedHashtable **table, UserDataCallback freeData)
{
    if (table && *table) {

        for (size_t i = 0; i < (*table)->size; i++)
            DictList_destroy(&(*table)->chains[i], freeData);

        free((*table)->chains);
        free(*table);
        *table = NULL;
    }
}
