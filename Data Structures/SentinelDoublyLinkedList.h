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


GiDS_API SDLList *SDLList_init(void);

GiDS_API DLListNode *SDLList_insert(SDLList *sdllList, void *pData);

GiDS_API DLListNode *SDLList_append(SDLList *sdllList, void *pData);

GiDS_API void *SDLList_deleteNode(SDLList *sdllList, void *pToDelete);

GiDS_API DLListNode *SDLList_find(SDLList *sdllList, void *pToFind);

GiDS_API void SDLList_traverse(SDLList *sdllList, CustomDataCallback handleData);

GiDS_API void SDLList_destroy(SDLList **sdllList, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_SENT_DL_LIST_H
