 /********************
 *  AssociationList.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License.
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/

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



EduDS_API DictListNode *DictList_insert(DictListNode **dictListHead,
                                        void *pData,
                                        void *pKey,
                                        UserCompareCallback KeyCmp,
                                        EdsErrCode *err);

EduDS_API DictListNode *DictList_append(DictListNode **dictListHead,
                                        void *pData,
                                        void *pKey,
                                        UserCompareCallback KeyCmp,
                                        EdsErrCode *err);

EduDS_API DictListNode *DictList_insertAfter(DictListNode *dictListPrev,
                                             void *pData,
                                             void *pKey,
                                             EdsErrCode *err);

EduDS_API KeyValuePair DictList_deleteByKey(DictListNode **dictListHead,
                                            void *pKey,
                                            UserCompareCallback KeyCmp,
                                            EdsErrCode *err);

EduDS_API DictListNode *DictList_findByKey(DictListNode *dictListHead,
                                           void *pKey,
                                           UserCompareCallback KeyCmp,
                                           EdsErrCode *err);

EduDS_API void DictList_traverse(DictListNode *dictListHead,
                                 UserDataCallback handleData,
                                 EdsErrCode *err);

EduDS_API void DictList_destroy(DictListNode **dictListHead,
                                UserDataCallback freeData,
                                EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_ASSOCIATION_LIST_H
