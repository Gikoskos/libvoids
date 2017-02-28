/***********************************************\
*           CircularSinglyLinkedList.h          *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __EduDS_CSL_LIST_H
#define __EduDS_CSL_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _CSLListNode {
    void *pData;
    struct _CSLListNode *nxt;
} CSLListNode;



EduDS_API CSLListNode *CSLList_insert(CSLListNode **csllHead, void *pData);

EduDS_API CSLListNode *CSLList_append(CSLListNode **csllHead, void *pData);

EduDS_API CSLListNode *CSLList_insertAfter(CSLListNode *csllPrev, void *pData);

EduDS_API void *CSLList_deleteNode(CSLListNode **csllHead, CSLListNode *cdllToDelete);

EduDS_API CSLListNode *CSLList_find(CSLListNode *csllHead, void *pToFind);

EduDS_API void CSLList_traverse(CSLListNode *csllHead, CustomDataCallback handleData);

EduDS_API void CSLList_destroy(CSLListNode **csllHead, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_CSL_LIST_H
