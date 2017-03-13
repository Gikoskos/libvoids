 /********************
 *  DoublyLinkedList.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef __EduDS_DL_LIST_H
#define __EduDS_DL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _DLListNode {
    void *pData;
    struct _DLListNode *nxt, *prv;
} DLListNode;



EduDS_API DLListNode *DLList_insert(DLListNode **dllHead,
                                    void *pData,
                                    EdsErrCode *err);

EduDS_API DLListNode *DLList_append(DLListNode **dllHead,
                                    void *pData,
                                    EdsErrCode *err);

EduDS_API DLListNode *DLList_concat(DLListNode *dll_1,
                                    DLListNode *dll_2,
                                    EdsErrCode *err);

EduDS_API DLListNode *DLList_insertAfter(DLListNode *dllPrev,
                                         void *pData,
                                         EdsErrCode *err);

EduDS_API void *DLList_deleteNode(DLListNode **dllHead,
                                  DLListNode *dllToDelete,
                                  EdsErrCode *err);

EduDS_API void *DLList_deleteData(DLListNode **dllHead,
                                  void *pToDelete,
                                  UserCompareCallback DataCmp,
                                  EdsErrCode *err);

EduDS_API DLListNode *DLList_at(DLListNode *dllHead,
                                size_t idx,
                                EdsErrCode *err);

EduDS_API DLListNode *DLList_find(DLListNode *dllHead,
                                  void *pToFind,
                                  UserCompareCallback DataCmp,
                                  EdsErrCode *err);

EduDS_API void DLList_traverse(DLListNode *dllHead,
                               UserDataCallback handleData,
                               EdsErrCode *err);

EduDS_API void DLList_destroy(DLListNode **dllHead,
                              UserDataCallback freeData,
                              EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_DL_LIST_H
