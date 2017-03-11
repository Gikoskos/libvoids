/***********************************************\
*           SentinelSinglyLinkedList.h          *
*           George Koskeridis (C) 2016          *
\***********************************************/

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


EduDS_API SSLList *SSLList_init(EduDSErrCode *err);

EduDS_API SLListNode *SSLList_insert(SSLList *ssllList,
                                     void *pData,
                                     EduDSErrCode *err);

EduDS_API SLListNode *SSLList_append(SSLList *ssllList,
                                     void *pData,
                                     EduDSErrCode *err);

EduDS_API void *SSLList_deleteData(SSLList *ssllList,
                                   void *pData,
                                   UserCompareCallback DataCmp,
                                   EduDSErrCode *err);

EduDS_API void *SSLList_deleteNode(SSLList *ssllList,
                                   SLListNode *sllToDelete,
                                   EduDSErrCode *err);

EduDS_API SLListNode *SSLList_at(SSLList *ssllList,
                                 size_t idx,
                                 EduDSErrCode *err);

EduDS_API SSLList *SSLList_concat(SSLList *ssll1,
                                  SSLList *ssll2,
                                  EduDSErrCode *err);

EduDS_API SLListNode *SSLList_find(SSLList *ssllList,
                                   void *pToFind,
                                   UserCompareCallback DataCmp,
                                   EduDSErrCode *err);

EduDS_API void SSLList_traverse(SSLList *ssllList,
                                UserDataCallback handleData,
                                EduDSErrCode *err);

EduDS_API void SSLList_destroy(SSLList **ssllList,
                               UserDataCallback freeData,
                               EduDSErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_SENT_SL_LIST_H
