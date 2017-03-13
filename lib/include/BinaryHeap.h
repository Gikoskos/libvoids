 /********************
 *  BinaryHeap.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef __EduDS_BINARYHEAP_H
#define __EduDS_BINARYHEAP_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"

typedef enum _HeapOrderType {
    MAX_ORDER_HEAP, MIN_ORDER_HEAP
} HeapOrderType;

typedef struct _BinaryHeapNode {
    void *pData;
    struct _BinaryHeapNode *left, *right, *parent;
} BinaryHeapNode;

typedef struct _BinaryHeap {
    BinaryHeapNode *root;
    UserCompareCallback DataCmp;
    HeapOrderType order;
} BinaryHeap;


EduDS_API BinaryHeap *BinaryHeap_init(UserCompareCallback DataCmp,
                                      HeapOrderType order,
                                      EdsErrCode *err);

EduDS_API BinaryHeapNode *BinaryHeap_push(BinaryHeap *bheap,
                                          void *pData,
                                          EdsErrCode *err);

EduDS_API void *BinaryHeap_pop(BinaryHeap *bheap,
                               EdsErrCode *err);

EduDS_API void *BinaryHeap_replace(BinaryHeap *bheap,
                                   void *pData,
                                   EdsErrCode *err);

EduDS_API void BinaryHeap_destroy(BinaryHeap **bheap,
                                  UserDataCallback freeData,
                                  EdsErrCode *err);


#ifdef __cplusplus
}
#endif

#endif //__EduDS_BINARYHEAP_H
