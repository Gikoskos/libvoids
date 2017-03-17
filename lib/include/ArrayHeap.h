 /********************
 *  ArrayHeap.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef __EduDS_ARRAYHEAP_H
#define __EduDS_ARRAYHEAP_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "BinaryHeap.h"


typedef struct _ArrayHeap {
    void **array;
    size_t size, idx;
    UserCompareCallback DataCmp;
    HeapPropertyType property;
} ArrayHeap;


EduDS_API ArrayHeap *ArrayHeap_init(UserCompareCallback DataCmp,
                                    HeapPropertyType property,
                                    size_t size,
                                    EdsErrCode *err);

EduDS_API void *ArrayHeap_push(ArrayHeap *arrheap,
                               void *pData,
                               EdsErrCode *err);

EduDS_API void *ArrayHeap_pop(ArrayHeap *arrheap,
                              EdsErrCode *err);

EduDS_API void *ArrayHeap_replace(ArrayHeap *arrheap,
                                  void *pData,
                                  EdsErrCode *err);

EduDS_API void ArrayHeap_destroy(ArrayHeap *arrheap,
                                 UserDataCallback freeData,
                                 EdsErrCode *err);


#ifdef __cplusplus
}
#endif

#endif //__EduDS_ARRAYHEAP_H
