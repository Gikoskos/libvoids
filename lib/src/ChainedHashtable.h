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
    UserCompareCallback KeyCmp;
    UserHashFuncCallback Hash;
    size_t size;
} ChainedHashtable;


EduDS_API ChainedHashtable *ChainedHash_init(size_t size,
                                             UserCompareCallback KeyCmp,
                                             UserHashFuncCallback Hash,
                                             EduDSErrCode *err);

EduDS_API DictListNode *ChainedHash_insert(ChainedHashtable *table,
                                           void *pData,
                                           void *pKey,
                                           size_t key_size,
                                           EduDSErrCode *err);

EduDS_API KeyValuePair ChainedHash_delete(ChainedHashtable *table,
                                          void *pKey,
                                          size_t key_size,
                                          EduDSErrCode *err);

EduDS_API DictListNode *ChainedHash_find(ChainedHashtable *table,
                                         void *pKey,
                                         size_t key_size,
                                         EduDSErrCode *err);

EduDS_API void ChainedHash_destroy(ChainedHashtable **table,
                                   UserDataCallback freeData,
                                   EduDSErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_CHAINEDHASHTABLE_H
