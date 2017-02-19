/***********************************************\
*           SentinelSinglyLinkedList.h          *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __GiDS_SENT_SL_LIST_H
#define __GiDS_SENT_SL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "SinglyLinkedList.h"


typedef struct _SSLList {
    SLListNode *head, *sentinel;
} SSLList;


GiDS_API SSLList *SSLList_init(void);

GiDS_API SLListNode *SSLList_insert(SSLList *ssllList, void *pData);

GiDS_API SLListNode *SSLList_append(SSLList *ssllList, void *pData);

GiDS_API void *SSLList_deleteNode(SSLList *ssllList, void *pData);

GiDS_API SLListNode *SSLList_find(SSLList *ssllList, void *pToFind);

GiDS_API void SSLList_traverse(SSLList *ssllList, CustomDataCallback handleData);

GiDS_API void SSLList_destroy(SSLList **ssllList, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_SENT_SL_LIST_H
