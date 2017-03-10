/***********************************************\
*           CircularSinglyLinkedList.h          *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __EduDS_CSL_LIST_H
#define __EduDS_CSL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _CSLListNode {
    void *pData;
    struct _CSLListNode *nxt;
} CSLListNode;



EduDS_API CSLListNode *CSLList_insert(CSLListNode **csllHead,
                                      void *pData,
                                      EduDSErrCode *err);

EduDS_API CSLListNode *CSLList_append(CSLListNode **csllHead,
                                      void *pData,
                                      EduDSErrCode *err);

EduDS_API CSLListNode *CSLList_concat(CSLListNode **csll_1,
                                      CSLListNode *csll_2,
                                      EduDSErrCode *err);

EduDS_API CSLListNode *CSLList_insertAfter(CSLListNode *csllPrev,
                                           void *pData,
                                           EduDSErrCode *err);

EduDS_API void *CSLList_deleteNode(CSLListNode **csllHead,
                                   CSLListNode *csllToDelete,
                                   EduDSErrCode *err);

EduDS_API CSLListNode *CSLList_find(CSLListNode *csllHead,
                                    void *pToFind,
                                    UserCompareCallback DataCmp,
                                    EduDSErrCode *err);

EduDS_API void CSLList_traverse(CSLListNode *csllHead,
                                UserDataCallback handleData,
                                EduDSErrCode *err);

EduDS_API void CSLList_destroy(CSLListNode **csllHead,
                               UserDataCallback freeData,
                               EduDSErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_CSL_LIST_H
