/***********************************************\
*               ChainedHashTable.h              *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __EduDS_CHAINEDHASHTABLE_H
#define __EduDS_CHAINEDHASHTABLE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "AssociationList.h"


typedef struct _ChainedHashtable {
    DictListNode **chains;
    size_t size;
} ChainedHashtable;


EduDS_API ChainedHashtable *ChainedHash_init(size_t size);
          
EduDS_API DictListNode *ChainedHash_insert(ChainedHashtable *table, void *pData, key_type key);
          
EduDS_API void *ChainedHash_delete(ChainedHashtable *table, key_type key);
          
EduDS_API DictListNode *ChainedHash_find(ChainedHashtable *table, key_type key);
          
EduDS_API void ChainedHash_destroy(ChainedHashtable **table, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_CHAINEDHASHTABLE_H
