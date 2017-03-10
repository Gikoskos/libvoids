/***********************************************\
*           CircularDoublyLinkedList.h          *
*           George Koskeridis (C) 2016          *
\***********************************************/

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
                                      EduDSErrCode *err);

EduDS_API CDLListNode *CDLList_append(CDLListNode **cdllHead,
                                      void *pData,
                                      EduDSErrCode *err);

EduDS_API CDLListNode *CDLList_concat(CDLListNode **cdll_1,
                                      CDLListNode *cdll_2,
                                      EduDSErrCode *err);

EduDS_API CDLListNode *CDLList_insertAfter(CDLListNode *cdllPrev,
                                           void *pData,
                                           EduDSErrCode *err);

EduDS_API void *CDLList_deleteNode(CDLListNode **cdllHead,
                                   CDLListNode *cdllToDelete,
                                   EduDSErrCode *err);

EduDS_API CDLListNode *CDLList_find(CDLListNode *cdllHead,
                                    void *pToFind,
                                    UserCompareCallback DataCmp,
                                    EduDSErrCode *err);

EduDS_API void CDLList_traverse(CDLListNode *cdllHead,
                                UserDataCallback handleData,
                                EduDSErrCode *err);

EduDS_API void CDLList_destroy(CDLListNode **cdllHead,
                               UserDataCallback freeData,
                               EduDSErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_CDL_LIST_H
