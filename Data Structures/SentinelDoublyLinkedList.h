/***********************************************\
*           SentinelDoublyLinkedList.h          *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __GiDS_SENT_DL_LIST_H
#define __GiDS_SENT_DL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "DoublyLinkedList.h"

typedef struct _SDLList {
    DLListNode *head, *sentinel;
} SDLList;


GiDS_API SDLList *newSDLList(void);

GiDS_API DLListNode *insertNodeSDLList(SDLList *sdllList, void *pData);

GiDS_API DLListNode *appendNodeSDLList(SDLList *sdllList, void *pData);

GiDS_API void *deleteNodeSDLList(SDLList *sdllList, void *pToDelete);

GiDS_API DLListNode *findNodeSDLList(SDLList *sdllList, void *pToFind);

GiDS_API void printSDLList(SDLList *sdllList, CustomDataCallback printData);

GiDS_API void deleteSDLList(SDLList **sdllList, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_SENT_DL_LIST_H
