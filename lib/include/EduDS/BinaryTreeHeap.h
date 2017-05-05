 /********************
 *  BinaryTreeHeap.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef EduDS_BINARYTREEHEAP_H__
#define EduDS_BINARYTREEHEAP_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef enum _HeapPropertyType {
    EDS_MAX_HEAP, EDS_MIN_HEAP
} HeapPropertyType;

typedef struct _BTHeapNode {
    void *pData;
    struct _BTHeapNode *left, *right, *parent;
} BTHeapNode;

typedef struct _BTHeap {
    BTHeapNode *root;
    unsigned int total_nodes;
    UserCompareCallback DataCmp;
    HeapPropertyType property;
} BTHeap;


EduDS_API BTHeap *BTHeap_init(UserCompareCallback DataCmp,
                              HeapPropertyType property,
                              EdsErrCode *err);

EduDS_API BTHeapNode *BTHeap_push(BTHeap *btheap,
                                  void *pData,
                                  EdsErrCode *err);

EduDS_API void *BTHeap_pop(BTHeap *btheap,
                           EdsErrCode *err);

EduDS_API void *BTHeap_replace(BTHeap *btheap,
                               void *pData,
                               EdsErrCode *err);

EduDS_API void BTHeap_destroy(BTHeap **btheap,
                              UserDataCallback freeData,
                              EdsErrCode *err);


#ifdef __cplusplus
}
#endif

#endif //EduDS_BINARYTREEHEAP_H__
