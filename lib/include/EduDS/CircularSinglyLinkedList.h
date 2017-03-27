 /********************
 *  CircularSinglyLinkedList.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


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



EduDS_API CSLListNode *CSLList_insert(CSLListNode **csllHead,
                                      void *pData,
                                      EdsErrCode *err);

EduDS_API CSLListNode *CSLList_append(CSLListNode **csllHead,
                                      void *pData,
                                      EdsErrCode *err);

EduDS_API CSLListNode *CSLList_concat(CSLListNode *csll_1,
                                      CSLListNode *csll_2,
                                      EdsErrCode *err);

EduDS_API CSLListNode *CSLList_insertAfter(CSLListNode *csllPrev,
                                           void *pData,
                                           EdsErrCode *err);

EduDS_API void *CSLList_deleteNode(CSLListNode **csllHead,
                                   CSLListNode *csllToDelete,
                                   EdsErrCode *err);

EduDS_API void *CSLList_deleteData(CSLListNode **csllHead,
                                   void *pToDelete,
                                   UserCompareCallback DataCmp,
                                   EdsErrCode *err);

EduDS_API CSLListNode *CSLList_at(CSLListNode *csllHead,
                                  size_t idx,
                                  EdsErrCode *err);

EduDS_API CSLListNode *CSLList_find(CSLListNode *csllHead,
                                    void *pToFind,
                                    UserCompareCallback DataCmp,
                                    EdsErrCode *err);

EduDS_API void CSLList_traverse(CSLListNode *csllHead,
                                UserDataCallback handleData,
                                EdsErrCode *err);

EduDS_API void CSLList_destroy(CSLListNode **csllHead,
                               UserDataCallback freeData,
                               EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_CSL_LIST_H
