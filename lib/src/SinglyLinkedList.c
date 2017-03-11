/***********************************************\
*              SinglyLinkedList.c               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "SinglyLinkedList.h"


SLListNode *SLList_insert(SLListNode **sllHead,
                          void *pData,
                          EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    SLListNode *new_node = NULL;

    if (sllHead) {
        new_node = malloc(sizeof(SLListNode));

        if (new_node) {

            new_node->pData = pData;
            new_node->nxt = *sllHead;

            *sllHead = new_node;

        } else
            tmp_err = EduDS_MALLOC_FAIL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

SLListNode *SLList_append(SLListNode **sllHead,
                          void *pData,
                          EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    SLListNode *new_node = NULL;

    if (sllHead) {
        new_node = malloc(sizeof(SLListNode));

        if (new_node) {

            new_node->pData = pData;
            new_node->nxt = NULL;

            if (!(*sllHead)) {
                *sllHead = new_node;
            } else {
                SLListNode *curr;

                for (curr = *sllHead; curr->nxt; curr = curr->nxt);

                curr->nxt = new_node;
            }

        } else
            tmp_err = EduDS_MALLOC_FAIL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

SLListNode *SLList_insertAfter(SLListNode *sllPrev,
                               void *pData,
                               EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    SLListNode *new_node = NULL;

    if (sllPrev) {
        new_node = malloc(sizeof(SLListNode));

        if (new_node) {

            new_node->pData = pData;
            new_node->nxt = sllPrev->nxt;

            sllPrev->nxt = new_node;

        } else
            tmp_err = EduDS_MALLOC_FAIL;

    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

void *SLList_deleteNode(SLListNode **sllHead,
                        SLListNode *sllToDelete,
                        EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_INVALID_ARGS;
    void *pRet = NULL;

    if (sllHead && sllToDelete) {
        SLListNode *curr, *prev = NULL;

        for (curr = *sllHead; curr && (curr != sllToDelete); curr = curr->nxt)
            prev = curr;

        if (curr) {
            pRet = curr->pData;

            if (prev)
                prev->nxt = curr->nxt;
            else
                *sllHead = curr->nxt;

            free(curr);
            tmp_err = EduDS_SUCCESS;
        }
    }

    SAVE_ERR(err, tmp_err);

    return pRet;
}

void *SLList_deleteData(SLListNode **sllHead,
                        void *pData,
                        UserCompareCallback DataCmp,
                        EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_INVALID_ARGS;
    void *pRet = NULL;

    if (sllHead && *sllHead && DataCmp) {
        SLListNode *curr, *prev = NULL;

        for (curr = *sllHead; curr && DataCmp(curr->pData, pData); curr = curr->nxt)
            prev = curr;

        if (curr) {
            pRet = curr->pData;

            if (prev)
                prev->nxt = curr->nxt;
            else
                *sllHead = curr->nxt;

            free(curr);
            tmp_err = EduDS_SUCCESS;
        }
    }

    SAVE_ERR(err, tmp_err);

    return pRet;
}

SLListNode *SLList_at(SLListNode *sllHead,
                      size_t idx,
                      EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    SLListNode *curr = NULL;

    if (sllHead) {
        size_t i = 0;
        for (curr = sllHead; curr && i < idx; curr = curr->nxt, i++);
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

SLListNode *SLList_concat(SLListNode *sll1,
                          SLListNode *sll2,
                          EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    SLListNode *ret = NULL;

    if (sll1 && sll2) {
        SLListNode *tail1;

        for (tail1 = sll1; tail1->nxt; tail1 = tail1->nxt);
        tail1->nxt = sll2;

        ret = sll1;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return ret;
}

SLListNode *SLList_find(SLListNode *sllHead,
                        void *pToFind,
                        UserCompareCallback DataCmp,
                        EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    SLListNode *curr = NULL;

    if (sllHead && DataCmp)
        for (curr = sllHead; curr && DataCmp(curr->pData, pToFind); curr = curr->nxt);
    else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

void SLList_traverse(SLListNode *sllHead,
                     UserDataCallback handleData,
                     EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (sllHead && handleData)
        for (SLListNode *curr = sllHead; curr; curr = curr->nxt)
            handleData(curr->pData);
    else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void SLList_destroy(SLListNode **sllHead,
                    UserDataCallback freeData,
                    EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (sllHead) {
        SLListNode *curr, *tmp;

        for (curr = *sllHead; curr;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        *sllHead = NULL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
