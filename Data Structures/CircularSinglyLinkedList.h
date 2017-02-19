/***********************************************\
*           CircularSinglyLinkedList.h          *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __GiDS_CSL_LIST_H
#define __GiDS_CSL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _CSLListNode {
    void *pData;
    struct _CSLListNode *nxt;
} CSLListNode;



GiDS_API CSLListNode *CSLList_insert(CSLListNode **csllHead, void *pData);

GiDS_API CSLListNode *CSLList_append(CSLListNode **csllHead, void *pData);

GiDS_API CSLListNode *CSLList_insertAfter(CSLListNode *csllPrev, void *pData);

GiDS_API void *CSLList_deleteNode(CSLListNode **csllHead, CSLListNode *cdllToDelete);

GiDS_API CSLListNode *CSLList_find(CSLListNode *csllHead, void *pToFind);

GiDS_API void CSLList_traverse(CSLListNode *csllHead, CustomDataCallback handleData);

GiDS_API void CSLList_destroy(CSLListNode **csllHead, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_CSL_LIST_H
