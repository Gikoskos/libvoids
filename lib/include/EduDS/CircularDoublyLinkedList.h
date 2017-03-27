 /********************
 *  CircularDoublyLinkedList.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef __EduDS_CDL_LIST_H
#define __EduDS_CDL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _CDLListNode {
    void *pData;
    struct _CDLListNode *nxt, *prv;
} CDLListNode;



EduDS_API CDLListNode *CDLList_insert(CDLListNode **cdllHead,
                                      void *pData,
                                      EdsErrCode *err);

EduDS_API CDLListNode *CDLList_append(CDLListNode **cdllHead,
                                      void *pData,
                                      EdsErrCode *err);

EduDS_API CDLListNode *CDLList_concat(CDLListNode *cdll_1,
                                      CDLListNode *cdll_2,
                                      EdsErrCode *err);

EduDS_API CDLListNode *CDLList_insertAfter(CDLListNode *cdllPrev,
                                           void *pData,
                                           EdsErrCode *err);

EduDS_API void *CDLList_deleteNode(CDLListNode **cdllHead,
                                   CDLListNode *cdllToDelete,
                                   EdsErrCode *err);

EduDS_API void *CDLList_deleteData(CDLListNode **cdllHead,
                                   void *pToDelete,
                                   UserCompareCallback DataCmp,
                                   EdsErrCode *err);

EduDS_API CDLListNode *CDLList_at(CDLListNode *cdllHead,
                                  size_t idx,
                                  EdsErrCode *err);

EduDS_API CDLListNode *CDLList_find(CDLListNode *cdllHead,
                                    void *pToFind,
                                    UserCompareCallback DataCmp,
                                    EdsErrCode *err);

EduDS_API void CDLList_traverse(CDLListNode *cdllHead,
                                UserDataCallback handleData,
                                EdsErrCode *err);

EduDS_API void CDLList_destroy(CDLListNode **cdllHead,
                               UserDataCallback freeData,
                               EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_CDL_LIST_H
