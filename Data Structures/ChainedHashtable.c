/***********************************************\
*               ChainedHashTable.c              *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ChainedHashtable.h"


static size_t Hash(key_type key, size_t size);


size_t Hash(key_type key, size_t size)
{
    return key % size;
}

ChainedHashtable *ChainedHash_init(size_t size)
{
    ChainedHashtable *chtable = malloc(sizeof(ChainedHashtable));

    chtable->chains = calloc(size, sizeof(DictListNode*));
    chtable->size = size;

    return chtable;
}

DictListNode *ChainedHash_insert(ChainedHashtable *table, void *pData, key_type key)
{
    DictListNode *new_node = NULL;

    if (table)
        new_node = DictList_insert(&table->chains[ Hash(key, table->size) ], pData, key);

    return new_node;
}

void *ChainedHash_delete(ChainedHashtable *table, key_type key)
{
    void *pData = NULL;

    if (table)
        pData = DictList_deleteByKey(&table->chains[ Hash(key, table->size) ], key);

    return pData;
}

DictListNode *ChainedHash_find(ChainedHashtable *table, key_type key)
{
    DictListNode *to_find = NULL;

    if (table)
        to_find = DictList_findByKey(table->chains[ Hash(key, table->size) ], key);

    return to_find;
}

void ChainedHash_destroy(ChainedHashtable **table, CustomDataCallback freeData)
{
    if (table && *table) {

        for (size_t i = 0; i < (*table)->size; i++)
            DictList_destroy(&(*table)->chains[i], freeData);

        free((*table)->chains);
        free(*table);
        *table = NULL;
    }
}
