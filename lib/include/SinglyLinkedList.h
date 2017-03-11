/***********************************************\
*              SinglyLinkedList.h               *
*           George Koskeridis (C) 2016          *
\***********************************************/

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
                                    EduDSErrCode *err);

EduDS_API SLListNode *SLList_append(SLListNode **sllHead,
                                    void *pData,
                                    EduDSErrCode *err);

EduDS_API SLListNode *SLList_insertAfter(SLListNode *sllPrev,
                                         void *pData,
                                         EduDSErrCode *err);

EduDS_API void *SLList_deleteNode(SLListNode **sllHead,
                                  SLListNode *sllToDelete,
                                  EduDSErrCode *err);

EduDS_API void *SLList_deleteData(SLListNode **sllHead,
                                  void *pData,
                                  UserCompareCallback DataCmp,
                                  EduDSErrCode *err);

EduDS_API SLListNode *SLList_at(SLListNode *sllHead,
                                size_t idx,
                                EduDSErrCode *err);

EduDS_API SLListNode *SLList_concat(SLListNode *sll1,
                                    SLListNode *sll2,
                                    EduDSErrCode *err);

EduDS_API SLListNode *SLList_find(SLListNode *sllHead,
                                  void *pToFind,
                                  UserCompareCallback DataCmp,
                                  EduDSErrCode *err);

EduDS_API void SLList_traverse(SLListNode *sllHead,
                               UserDataCallback handleData,
                               EduDSErrCode *err);

EduDS_API void SLList_destroy(SLListNode **sllHead,
                              UserDataCallback freeData,
                              EduDSErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_SL_LIST_H
