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



EduDS_API DLListNode *DLList_insert(DLListNode **dllHead, void *pData);

EduDS_API DLListNode *DLList_append(DLListNode **dllHead, void *pData);

EduDS_API DLListNode *DLList_insertAfter(DLListNode *dllPrev, void *pData);

EduDS_API void *DLList_deleteNode(DLListNode **dllHead, DLListNode *dllToDelete);

EduDS_API DLListNode *DLList_find(DLListNode *dllHead, void *pToFind);

EduDS_API void DLList_traverse(DLListNode *dllHead, CustomDataCallback handleData);

EduDS_API void DLList_destroy(DLListNode **dllHead, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_DL_LIST_H
