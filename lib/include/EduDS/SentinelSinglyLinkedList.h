 /********************
 *  SentinelSinglyLinkedList.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef __EduDS_SENT_SL_LIST_H
#define __EduDS_SENT_SL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "SinglyLinkedList.h"


typedef struct _SSLList {
    SLListNode *head, *sentinel;
} SSLList;


EduDS_API SSLList *SSLList_init(EdsErrCode *err);

EduDS_API SLListNode *SSLList_insert(SSLList *ssllList,
                                     void *pData,
                                     EdsErrCode *err);

EduDS_API SLListNode *SSLList_append(SSLList *ssllList,
                                     void *pData,
                                     EdsErrCode *err);

EduDS_API void *SSLList_deleteData(SSLList *ssllList,
                                   void *pData,
                                   UserCompareCallback DataCmp,
                                   EdsErrCode *err);

EduDS_API void *SSLList_deleteNode(SSLList *ssllList,
                                   SLListNode *sllToDelete,
                                   EdsErrCode *err);

EduDS_API SLListNode *SSLList_at(SSLList *ssllList,
                                 size_t idx,
                                 EdsErrCode *err);

EduDS_API SSLList *SSLList_concat(SSLList *ssll1,
                                  SSLList *ssll2,
                                  EdsErrCode *err);

EduDS_API SLListNode *SSLList_find(SSLList *ssllList,
                                   void *pToFind,
                                   UserCompareCallback DataCmp,
                                   EdsErrCode *err);

EduDS_API void SSLList_traverse(SSLList *ssllList,
                                UserDataCallback handleData,
                                EdsErrCode *err);

EduDS_API void SSLList_destroy(SSLList **ssllList,
                               UserDataCallback freeData,
                               EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_SENT_SL_LIST_H
