 /********************
 *  SentinelDoublyLinkedList.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef __EduDS_SENT_DL_LIST_H
#define __EduDS_SENT_DL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "DoublyLinkedList.h"


typedef struct _SDLList {
    DLListNode *head, *sentinel;
} SDLList;


EduDS_API SDLList *SDLList_init(EdsErrCode *err);

EduDS_API DLListNode *SDLList_insert(SDLList *sdllList,
                                     void *pData,
                                     EdsErrCode *err);

EduDS_API DLListNode *SDLList_append(SDLList *sdllList,
                                     void *pData,
                                     EdsErrCode *err);

EduDS_API void *SDLList_deleteNode(SDLList *sdllList,
                                   DLListNode *sdllToDelete,
                                   EdsErrCode *err);

EduDS_API void *SDLList_deleteData(SDLList *sdllList,
                                   void *pToDelete,
                                   UserCompareCallback DataCmp,
                                   EdsErrCode *err);

EduDS_API DLListNode *SDLList_at(SDLList *sdllHead,
                                 size_t idx,
                                 EdsErrCode *err);

EduDS_API SDLList *SDLList_concat(SDLList *sdll1,
                                  SDLList *sdll2,
                                  EdsErrCode *err);

EduDS_API DLListNode *SDLList_find(SDLList *sdllList,
                                   void *pToFind,
                                   UserCompareCallback DataCmp,
                                   EdsErrCode *err);

EduDS_API void SDLList_traverse(SDLList *sdllList,
                                UserDataCallback handleData,
                                EdsErrCode *err);

EduDS_API void SDLList_destroy(SDLList **sdllList,
                               UserDataCallback freeData,
                               EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_SENT_DL_LIST_H
