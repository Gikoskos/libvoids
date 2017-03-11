/***********************************************\
*           SentinelDoublyLinkedList.h          *
*           George Koskeridis (C) 2016          *
\***********************************************/

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


EduDS_API SDLList *SDLList_init(EduDSErrCode *err);

EduDS_API DLListNode *SDLList_insert(SDLList *sdllList,
                                     void *pData,
                                     EduDSErrCode *err);

EduDS_API DLListNode *SDLList_append(SDLList *sdllList,
                                     void *pData,
                                     EduDSErrCode *err);

EduDS_API void *SDLList_deleteNode(SDLList *sdllList,
                                   DLListNode *sdllToDelete,
                                   EduDSErrCode *err);

EduDS_API void *SDLList_deleteData(SDLList *sdllList,
                                   void *pToDelete,
                                   UserCompareCallback DataCmp,
                                   EduDSErrCode *err);

EduDS_API DLListNode *SDLList_at(SDLList *sdllHead,
                                 size_t idx,
                                 EduDSErrCode *err);

EduDS_API SDLList *SDLList_concat(SDLList *sdll1,
                                  SDLList *sdll2,
                                  EduDSErrCode *err);

EduDS_API DLListNode *SDLList_find(SDLList *sdllList,
                                   void *pToFind,
                                   UserCompareCallback DataCmp,
                                   EduDSErrCode *err);

EduDS_API void SDLList_traverse(SDLList *sdllList,
                                UserDataCallback handleData,
                                EduDSErrCode *err);

EduDS_API void SDLList_destroy(SDLList **sdllList,
                               UserDataCallback freeData,
                               EduDSErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_SENT_DL_LIST_H
