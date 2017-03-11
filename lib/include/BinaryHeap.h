/***********************************************\
*                  BinaryHeap.h                 *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __EduDS_BINARYHEAP_H
#define __EduDS_BINARYHEAP_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"

typedef enum _HeapType {
    MAX_ORDER_HEAP, MIN_ORDER_HEAP
} HeapType;

typedef struct _BinaryHeapNode {
    void *pData;
    struct _BinaryHeapNode *left, *right, *parent;
} BinaryHeapNode;

typedef struct _BinaryHeap {
    BinaryHeapNode *root;
    UserCompareCallback DataCmp;
    HeapType type;
} BinaryHeap;


EduDS_API BinaryHeap *BinaryHeap_init(UserCompareCallback DataCmp,
                                      HeapType type,
                                      EduDSErrCode *err);

EduDS_API BinaryHeapNode *BinaryHeap_push(BinaryHeap *bheap,
                                          void *pData,
                                          EduDSErrCode *err);

EduDS_API void *BinaryHeap_pop(BinaryHeap *bheap,
                               EduDSErrCode *err);

EduDS_API void *BinaryHeap_replace(BinaryHeap *bheap,
                                   void *pData,
                                   EduDSErrCode *err);

EduDS_API void BinaryHeap_destroy(BinaryHeap **bheap,
                                  UserDataCallback freeData,
                                  EduDSErrCode *err);


#ifdef __cplusplus
}
#endif

#endif //__EduDS_BINARYHEAP_H
