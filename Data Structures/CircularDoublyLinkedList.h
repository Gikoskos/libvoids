/***********************************************\
*           CircularDoublyLinkedList.h          *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __GiDS_CDL_LIST_H
#define __GiDS_CDL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _CDLListNode {
    void *pData;
    struct _CDLListNode *nxt, *prv;
} CDLListNode;



GiDS_API CDLListNode *CDLList_insert(CDLListNode **cdllHead, void *pData);

GiDS_API CDLListNode *CDLList_append(CDLListNode **cdllHead, void *pData);

GiDS_API CDLListNode *CDLList_insertAfter(CDLListNode *cdllPrev, void *pData);

GiDS_API void *CDLList_deleteNode(CDLListNode **cdllHead, CDLListNode *cdllToDelete);

GiDS_API CDLListNode *CDLList_find(CDLListNode *cdllHead, void *pToFind);

GiDS_API void CDLList_traverse(CDLListNode *cdllHead, CustomDataCallback handleData);

GiDS_API void CDLList_destroy(CDLListNode **cdllHead, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_CDL_LIST_H
