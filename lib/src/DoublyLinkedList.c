/***********************************************\
*              DoublyLinkedList.c               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "DoublyLinkedList.h"


DLListNode *DLList_insert(DLListNode **dllHead,
                          void *pData,
                          EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    DLListNode *new_node = NULL;

    if (dllHead) {
        new_node = malloc(sizeof(DLListNode));

        if (new_node) {
            new_node->pData = pData;
            new_node->prv = NULL;
            new_node->nxt = *dllHead;

            if (*dllHead)
                (*dllHead)->prv = new_node;

            *dllHead = new_node;
        } else
            tmp_err = EduDS_MALLOC_FAIL;

    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

DLListNode *DLList_append(DLListNode **dllHead,
                          void *pData,
                          EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    DLListNode *new_node = NULL;

    if (dllHead) {
        new_node = malloc(sizeof(DLListNode));

        if (new_node) {
            new_node->pData = pData;
            new_node->nxt = new_node->prv = NULL;

            if (!(*dllHead)) {
                *dllHead = new_node;
            } else {
                DLListNode *curr;

                for (curr = *dllHead; curr->nxt; curr = curr->nxt);

                curr->nxt = new_node;
                new_node->prv = curr;
            }
        } else
            tmp_err = EduDS_MALLOC_FAIL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

DLListNode *DLList_concat(DLListNode *dll_1,
                          DLListNode *dll_2,
                          EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (dll_1 && dll_2) {
        DLListNode *tail_1;

        for (tail_1 = dll_1; tail_1->nxt; tail_1 = tail_1->nxt);

        tail_1->nxt = dll_2;
        dll_2->prv = tail_1;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return dll_1;
}

DLListNode *DLList_insertAfter(DLListNode *dllPrev,
                               void *pData,
                               EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    DLListNode *new_node = NULL;

    if (dllPrev) {
        new_node = malloc(sizeof(DLListNode));

        if (new_node) {
            new_node->pData = pData;
            new_node->nxt = dllPrev->nxt;
            new_node->prv = dllPrev;

            dllPrev->nxt = new_node;
        } else
            tmp_err = EduDS_MALLOC_FAIL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

void *DLList_deleteNode(DLListNode **dllHead,
                        DLListNode *dllToDelete,
                        EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    void *pRet = NULL;

    if (dllHead && dllToDelete) {
        DLListNode *curr;

        for (curr = *dllHead; curr && (curr != dllToDelete); curr = curr->nxt);

        if (curr) {
            pRet = curr->pData;
               
            if (curr->nxt)
                curr->nxt->prv = curr->prv;

            if (curr->prv)
                curr->prv->nxt = curr->nxt;
            else
                *dllHead = curr->nxt;

            free(curr);
        }
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pRet;
}

DLListNode *DLList_find(DLListNode *dllHead,
                        void *pToFind,
                        UserCompareCallback DataCmp,
                        EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    DLListNode *curr;

    if (dllHead && DataCmp)
        for (curr = dllHead; curr && !DataCmp(curr->pData, pToFind); curr = curr->nxt);
    else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

void DLList_traverse(DLListNode *dllHead,
                     UserDataCallback handleData,
                     EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (dllHead && handleData)
        for (DLListNode *curr = dllHead; curr; curr = curr->nxt)
            handleData(curr->pData);
     else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void DLList_destroy(DLListNode **dllHead,
                    UserDataCallback freeData,
                    EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (dllHead) {
        DLListNode *curr, *tmp;

        for (curr = *dllHead; curr;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        *dllHead = NULL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
