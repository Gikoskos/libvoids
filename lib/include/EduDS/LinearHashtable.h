 /********************
 *  LinearHashtable.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef __EduDS_LINEARHASHTABLE_H
#define __EduDS_LINEARHASHTABLE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _HashArrayElement {
    KeyValuePair item;
    unsigned char state;
    size_t key_hash; //saving this to make rehashing slightly faster
} HashArrayElement;

typedef struct _LinHashtable {
    HashArrayElement *array;
    UserCompareCallback KeyCmp;
    UserHashFuncCallback Hash;
    int rehash;
    size_t total_elements;
    size_t size;
} LinHashtable;


EduDS_API LinHashtable *LinHash_init(size_t size,
                                     UserCompareCallback KeyCmp,
                                     UserHashFuncCallback Hash,
                                     int rehash,
                                     EdsErrCode *err);

EduDS_API void *LinHash_insert(LinHashtable *table,
                               void *pData,
                               void *pKey,
                               size_t key_size,
                               UserDataCallback freeData,
                               EdsErrCode *err);

EduDS_API KeyValuePair LinHash_delete(LinHashtable *table,
                                      void *pKey,
                                      size_t key_size,
                                      EdsErrCode *err);

EduDS_API HashArrayElement *LinHash_find(LinHashtable *table,
                                         void *pKey,
                                         size_t key_size,
                                         EdsErrCode *err);

EduDS_API void LinHash_destroy(LinHashtable **table,
                               UserDataCallback freeData,
                               EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_LINEARHASHTABLE_H
