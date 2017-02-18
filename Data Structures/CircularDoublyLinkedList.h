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



GiDS_API CDLListNode *insertNodeCDLList(CDLListNode **cdllHead, void *pData);

GiDS_API CDLListNode *appendNodeCDLList(CDLListNode **cdllHead, void *pData);

GiDS_API void *deleteNodeCDLList(CDLListNode **cdllHead, CDLListNode *cdllToDelete);

GiDS_API CDLListNode *findNodeCDLList(CDLListNode *cdllHead, void *pToFind);

GiDS_API void traverseCDLList(CDLListNode *cdllHead, CustomDataCallback handleData);

GiDS_API void deleteCDLList(CDLListNode **cdllHead, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_CDL_LIST_H
