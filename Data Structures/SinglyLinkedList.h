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



GiDS_API void insertNodeSLList(SLListNode **sllHead, void *pData);

GiDS_API void *deleteNodeSLList(SLListNode **sllHead, SLListNode *sllToDelete);

GiDS_API SLListNode *findNodeSLList(SLListNode *sllHead, void *pToFind);

GiDS_API void printSLList(SLListNode *sllHead, CustomDataCallback printData);

GiDS_API void deleteSLList(SLListNode **sllHead, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_SL_LIST_H
