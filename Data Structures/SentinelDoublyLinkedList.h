/***********************************************\
*           SentinelDoublyLinkedList.h          *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __EduDS_SENT_DL_LIST_H
#define __EduDS_SENT_DL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "DoublyLinkedList.h"


typedef struct _SDLList {
    DLListNode *head, *sentinel;
} SDLList;


EduDS_API SDLList *SDLList_init(void);

EduDS_API DLListNode *SDLList_insert(SDLList *sdllList, void *pData);

EduDS_API DLListNode *SDLList_append(SDLList *sdllList, void *pData);

EduDS_API void *SDLList_deleteNode(SDLList *sdllList, void *pToDelete);

EduDS_API DLListNode *SDLList_find(SDLList *sdllList, void *pToFind);

EduDS_API void SDLList_traverse(SDLList *sdllList, CustomDataCallback handleData);

EduDS_API void SDLList_destroy(SDLList **sdllList, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_SENT_DL_LIST_H
