 /********************
 *  BinomialHeap.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef EduDS_BINOMIALHEAP_H__
#define EduDS_BINOMIALHEAP_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "BinaryTreeHeap.h" //HeapPropertyType


typedef struct _BinomialTree {
    KeyValuePair item;
    struct _BinomialTree *child, *sibling, *parent;
    unsigned int order;
} BinomialTree;

typedef struct _BinomialHeap {
    BinomialTree *forest; //this is the first binomial tree on the forest of roots
    UserCompareCallback KeyCmp;
    HeapPropertyType property;
} BinomialHeap;


EduDS_API BinomialHeap *BinomialHeap_init(UserCompareCallback KeyCmp,
                                          HeapPropertyType property,
                                          EdsErrCode *err);

EduDS_API BinomialTree *BinomialHeap_push(BinomialHeap *binheap,
                                          void *pData,
                                          void *pKey,
                                          EdsErrCode *err);

EduDS_API KeyValuePair BinomialHeap_pop(BinomialHeap *binheap,
                                        EdsErrCode *err);

EduDS_API KeyValuePair BinomialHeap_getTop(BinomialHeap *binheap,
                                           EdsErrCode *err);

EduDS_API void *BinomialHeap_replaceKey(BinomialHeap *binheap,
                                        BinomialTree *tree,
                                        void *pNewKey,
                                        EdsErrCode *err);

EduDS_API void BinomialHeap_destroy(BinomialHeap **binheap,
                                    UserDataCallback freeData,
                                    EdsErrCode *err);


#ifdef __cplusplus
}
#endif

#endif //EduDS_BINOMIALHEAP_H__
