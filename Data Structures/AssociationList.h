/***********************************************\
*               AssociationList.h               *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __GiDS_ASSOCIATION_LIST_H
#define __GiDS_ASSOCIATION_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _DictListItem {
    void *pData;
    key_type key;
} DictListItem;

typedef struct _DictListNode {
    DictListItem item;
    struct _DictListNode *nxt;
} DictListNode;



GiDS_API DictListNode *DictList_insert(DictListNode **dictListHead, void *pData, key_type key);

GiDS_API DictListNode *DictList_append(DictListNode **dictListHead, void *pData, key_type key);

GiDS_API DictListNode *DictList_insertAfter(DictListNode *sllPrev, void *pData, key_type key);

GiDS_API void *DictList_deleteByKey(DictListNode **dictListHead, key_type key);

GiDS_API DictListNode *DictList_findByKey(DictListNode *dictListHead, key_type key);

GiDS_API void DictList_traverse(DictListNode *dictListHead, CustomDataCallback handleData);

GiDS_API void DictList_destroy(DictListNode **dictListHead, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_ASSOCIATION_LIST_H
