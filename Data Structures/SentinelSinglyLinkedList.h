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


GiDS_API SSLList *newSSLList(void);

GiDS_API SLListNode *insertNodeSSLList(SSLList *ssllList, void *pData);

GiDS_API SLListNode *appendNodeSSLList(SSLList *ssllList, void *pData);

GiDS_API void *deleteNodeSSLList(SSLList *ssllList, void *pData);

GiDS_API SLListNode *findNodeSSLList(SSLList *ssllList, void *pToFind);

GiDS_API void printSSLList(SSLList *ssllList, CustomDataCallback printData);

GiDS_API void deleteSSLList(SSLList **ssllList, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_SENT_SL_LIST_H
