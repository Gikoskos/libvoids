/***********************************************\
*              DoublyLinkedList.h               *
*           George Koskeridis (C) 2016          *
\***********************************************/

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
                                    EduDSErrCode *err);

EduDS_API DLListNode *DLList_append(DLListNode **dllHead,
                                    void *pData,
                                    EduDSErrCode *err);

EduDS_API DLListNode *DLList_concat(DLListNode *dll_1,
                                    DLListNode *dll_2,
                                    EduDSErrCode *err);

EduDS_API DLListNode *DLList_insertAfter(DLListNode *dllPrev,
                                         void *pData,
                                         EduDSErrCode *err);

EduDS_API void *DLList_deleteNode(DLListNode **dllHead,
                                  DLListNode *dllToDelete,
                                  EduDSErrCode *err);

EduDS_API void *DLList_deleteData(DLListNode **dllHead,
                                  void *pToDelete,
                                  UserCompareCallback DataCmp,
                                  EduDSErrCode *err);

EduDS_API DLListNode *DLList_at(DLListNode *dllHead,
                                size_t idx,
                                EduDSErrCode *err);

EduDS_API DLListNode *DLList_find(DLListNode *dllHead,
                                  void *pToFind,
                                  UserCompareCallback DataCmp,
                                  EduDSErrCode *err);

EduDS_API void DLList_traverse(DLListNode *dllHead,
                               UserDataCallback handleData,
                               EduDSErrCode *err);

EduDS_API void DLList_destroy(DLListNode **dllHead,
                              UserDataCallback freeData,
                              EduDSErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_DL_LIST_H
