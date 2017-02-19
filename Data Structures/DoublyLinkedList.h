/***********************************************\
*              DoublyLinkedList.h               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __GiDS_DL_LIST_H
#define __GiDS_DL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _DLListNode {
    void *pData;
    struct _DLListNode *nxt, *prv;
} DLListNode;



GiDS_API DLListNode *DLList_insert(DLListNode **dllHead, void *pData);

GiDS_API DLListNode *DLList_append(DLListNode **dllHead, void *pData);

GiDS_API DLListNode *DLList_insertAfter(DLListNode *dllPrev, void *pData);

GiDS_API void *DLList_deleteNode(DLListNode **dllHead, DLListNode *dllToDelete);

GiDS_API DLListNode *DLList_find(DLListNode *dllHead, void *pToFind);

GiDS_API void DLList_traverse(DLListNode *dllHead, CustomDataCallback handleData);

GiDS_API void DLList_destroy(DLListNode **dllHead, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_DL_LIST_H
