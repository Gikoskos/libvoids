/***********************************************\
*               AssociationList.h               *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __EduDS_ASSOCIATION_LIST_H
#define __EduDS_ASSOCIATION_LIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"



typedef struct _DictListNode {
    KeyValuePair item;
    struct _DictListNode *nxt;
} DictListNode;



EduDS_API DictListNode *DictList_insert(DictListNode **dictListHead, void *pData, void *pKey, UserCompareCallback KeyCmp);

EduDS_API DictListNode *DictList_append(DictListNode **dictListHead, void *pData, void *pKey, UserCompareCallback KeyCmp);

EduDS_API DictListNode *DictList_insertAfter(DictListNode *dictListPrev, void *pData, void *pKey);

EduDS_API KeyValuePair DictList_deleteByKey(DictListNode **dictListHead, void *pKey, UserCompareCallback KeyCmp);

EduDS_API DictListNode *DictList_findByKey(DictListNode *dictListHead, void *pKey, UserCompareCallback KeyCmp);

EduDS_API void DictList_traverse(DictListNode *dictListHead, UserDataCallback handleData);

EduDS_API void DictList_destroy(DictListNode **dictListHead, UserDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_ASSOCIATION_LIST_H
