 /********************
 *  LeftistHeap.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef EduDS_LEFTISTHEAP_H__
#define EduDS_LEFTISTHEAP_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "BinaryTreeHeap.h"

typedef struct _LeftistHeapNode {
    void *pData;
    struct _LeftistHeapNode *left, *right, *parent;
    unsigned int npl; //null path length
} LeftistHeapNode;

typedef struct _LeftistHeap {
    LeftistHeapNode *root;
    UserCompareCallback DataCmp;
    HeapPropertyType property;
} LeftistHeap;


EduDS_API LeftistHeap *LeftistHeap_init(UserCompareCallback DataCmp,
                                        HeapPropertyType property,
                                        EdsErrCode *err);

EduDS_API LeftistHeapNode *LeftistHeap_push(LeftistHeap *lheap,
                                            void *pData,
                                            EdsErrCode *err);

EduDS_API void *LeftistHeap_pop(LeftistHeap *lheap,
                                EdsErrCode *err);

EduDS_API void LeftistHeap_destroy(LeftistHeap **lheap,
                                   UserDataCallback freeData,
                                   EdsErrCode *err);


#ifdef __cplusplus
}
#endif

#endif //EduDS_LEFTISTHEAP_H__
