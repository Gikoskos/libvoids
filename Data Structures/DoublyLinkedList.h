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



GiDS_API void insertNodeDLList(DLListNode **dllHead, void *pData);

GiDS_API void *deleteNodeDLList(DLListNode **dllHead, DLListNode *dllToDelete);

GiDS_API DLListNode *findNodeDLList(DLListNode *dllHead, void *pToFind);

GiDS_API void printDLList(DLListNode *dllHead, CustomDataCallback printData);

GiDS_API void deleteDLList(DLListNode **dllHead, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_DL_LIST_H
