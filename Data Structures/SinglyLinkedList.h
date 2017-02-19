/***********************************************\
*              SinglyLinkedList.h               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __GiDS_SL_LIST_H
#define __GiDS_SL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _SLListNode {
    void *pData;
    struct _SLListNode *nxt;
} SLListNode;



GiDS_API SLListNode *SLList_insert(SLListNode **sllHead, void *pData);

GiDS_API SLListNode *SLList_append(SLListNode **sllHead, void *pData);

GiDS_API SLListNode *SLList_insertAfter(SLListNode *sllPrev, void *pData);

GiDS_API void *SLList_deleteNode(SLListNode **sllHead, SLListNode *sllToDelete);

GiDS_API SLListNode *SLList_find(SLListNode *sllHead, void *pToFind);

GiDS_API void SLList_traverse(SLListNode *sllHead, CustomDataCallback handleData);

GiDS_API void SLList_destroy(SLListNode **sllHead, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_SL_LIST_H
