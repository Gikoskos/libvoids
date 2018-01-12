 /********************
 *  AssociationList.h
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/

#ifndef VOIDS_ASSOCIATION_LIST_H__
#define VOIDS_ASSOCIATION_LIST_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"



typedef struct _AListNode {
    KeyValuePair item;
    struct _AListNode *nxt;
} AListNode;



VOIDS_API AListNode *AList_insert(AListNode **aListHead,
                                  void *pData,
                                  void *pKey,
                                  vdsUserCompareFunc KeyCmp,
                                  vdsErrCode *err);

VOIDS_API AListNode *AList_append(AListNode **aListHead,
                                  void *pData,
                                  void *pKey,
                                  vdsUserCompareFunc KeyCmp,
                                  vdsErrCode *err);

VOIDS_API AListNode *AList_insertAfter(AListNode *dictListPrev,
                                       void *pData,
                                       void *pKey,
                                       vdsErrCode *err);

VOIDS_API KeyValuePair AList_deleteByKey(AListNode **aListHead,
                                         void *pKey,
                                         vdsUserCompareFunc KeyCmp,
                                         vdsErrCode *err);

VOIDS_API KeyValuePair *AList_findByKey(AListNode *aListHead,
                                        void *pKey,
                                        vdsUserCompareFunc KeyCmp,
                                        vdsErrCode *err);

VOIDS_API void AList_traverse(AListNode *aListHead,
                              vdsUserDataFunc handleData,
                              vdsErrCode *err);

VOIDS_API void AList_destroy(AListNode **aListHead,
                             vdsUserDataFunc freeData,
                             vdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //VOIDS_ASSOCIATION_LIST_H__
