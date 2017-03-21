 /********************
 *  SinglyLinkedList.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef __EduDS_SL_LIST_H
#define __EduDS_SL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _SLListNode {
    void *pData;
    struct _SLListNode *nxt;
} SLListNode;



EduDS_API SLListNode *SLList_insert(SLListNode **sllHead,
                                    void *pData,
                                    EdsErrCode *err);

EduDS_API SLListNode *SLList_append(SLListNode **sllHead,
                                    void *pData,
                                    EdsErrCode *err);

EduDS_API SLListNode *SLList_insertAfter(SLListNode *sllPrev,
                                         void *pData,
                                         EdsErrCode *err);

EduDS_API void *SLList_deleteNode(SLListNode **sllHead,
                                  SLListNode *sllToDelete,
                                  EdsErrCode *err);

EduDS_API void *SLList_deleteData(SLListNode **sllHead,
                                  void *pData,
                                  UserCompareCallback DataCmp,
                                  EdsErrCode *err);

EduDS_API SLListNode *SLList_at(SLListNode *sllHead,
                                size_t idx,
                                EdsErrCode *err);

EduDS_API SLListNode *SLList_concat(SLListNode *sll1,
                                    SLListNode *sll2,
                                    EdsErrCode *err);

EduDS_API SLListNode *SLList_find(SLListNode *sllHead,
                                  void *pToFind,
                                  UserCompareCallback DataCmp,
                                  EdsErrCode *err);

EduDS_API void SLList_traverse(SLListNode *sllHead,
                               UserDataCallback handleData,
                               EdsErrCode *err);

EduDS_API void SLList_destroy(SLListNode **sllHead,
                              UserDataCallback freeData,
                              EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_SL_LIST_H
