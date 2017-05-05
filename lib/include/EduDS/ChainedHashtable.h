 /********************
 *  ChainedHashTable.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef EduDS_CHAINEDHASHTABLE_H__
#define EduDS_CHAINEDHASHTABLE_H__


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
                                             EdsErrCode *err);

EduDS_API DictListNode *ChainedHash_insert(ChainedHashtable *table,
                                           void *pData,
                                           void *pKey,
                                           size_t key_size,
                                           EdsErrCode *err);

EduDS_API KeyValuePair ChainedHash_delete(ChainedHashtable *table,
                                          void *pKey,
                                          size_t key_size,
                                          EdsErrCode *err);

EduDS_API DictListNode *ChainedHash_find(ChainedHashtable *table,
                                         void *pKey,
                                         size_t key_size,
                                         EdsErrCode *err);

EduDS_API void ChainedHash_destroy(ChainedHashtable **table,
                                   UserDataCallback freeData,
                                   EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //EduDS_CHAINEDHASHTABLE_H__
