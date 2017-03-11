/***********************************************\
*           CircularDoublyLinkedList.c          *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "CircularDoublyLinkedList.h"


CDLListNode *CDLList_insert(CDLListNode **cdllHead,
                            void *pData,
                            EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    CDLListNode *new_node = NULL;

    if (cdllHead) {
        new_node = malloc(sizeof(CDLListNode));

        if (new_node) {
            new_node->pData = pData;

            if (!(*cdllHead)) {
                new_node->nxt = new_node->prv = new_node;
            } else {
                new_node->prv = (*cdllHead)->prv;
                (*cdllHead)->prv->nxt = new_node;
                (*cdllHead)->prv = new_node;
                new_node->nxt = *cdllHead;
            }

            *cdllHead = new_node;

        } else
            tmp_err = EduDS_MALLOC_FAIL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

CDLListNode *CDLList_append(CDLListNode **cdllHead,
                            void *pData,
                            EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    CDLListNode *new_node = NULL;

    if (cdllHead) {

        if (!(*cdllHead)) {
            new_node = CDLList_insert(cdllHead, pData, &tmp_err);
        } else {
            new_node = malloc(sizeof(CDLListNode));

            if (new_node) {
                new_node->pData = pData;
                new_node->prv = (*cdllHead)->prv;
                new_node->nxt = *cdllHead;
                (*cdllHead)->prv->nxt = new_node;
                (*cdllHead)->prv = new_node;
            } else
                tmp_err = EduDS_MALLOC_FAIL;
        }

    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

CDLListNode *CDLList_concat(CDLListNode *cdll_1,
                            CDLListNode *cdll_2,
                            EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    CDLListNode *ret = NULL;

    if (cdll_1 && cdll_2) {
        CDLListNode *tmp = cdll_2->prv;

        cdll_2->prv->nxt = cdll_1;
        cdll_2->prv = cdll_1->prv;
        cdll_1->prv->nxt = cdll_2;
        cdll_1->prv = tmp;

        ret = cdll_1;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return ret;
}

CDLListNode *CDLList_insertAfter(CDLListNode *cdllPrev,
                                 void *pData,
                                 EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    CDLListNode *new_node = NULL;

    if (cdllPrev) {
        new_node = malloc(sizeof(CDLListNode));

        if (new_node) {
            new_node->pData = pData;
            new_node->nxt = cdllPrev->nxt;
            new_node->prv = cdllPrev;

            cdllPrev->nxt = new_node;
        } else
            tmp_err = EduDS_MALLOC_FAIL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

void *CDLList_deleteNode(CDLListNode **cdllHead,
                         CDLListNode *cdllToDelete,
                         EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_INVALID_ARGS;
    void *pRet = NULL;

    if (cdllHead && *cdllHead && cdllToDelete) {
        CDLListNode *curr = *cdllHead;

        do {
            if (curr == cdllToDelete) {

                if (curr == *cdllHead) {
                    if ((*cdllHead)->nxt == *cdllHead)
                        *cdllHead = NULL;
                    else
                        *cdllHead = curr->nxt;
                }

                curr->nxt->prv = curr->prv;
                curr->prv->nxt = curr->nxt;

                pRet = curr->pData;
                free(curr);

                tmp_err = EduDS_SUCCESS;

                break;
            }

            curr = curr->nxt;
        } while (curr != *cdllHead);

    }

    SAVE_ERR(err, tmp_err);

    return pRet;
}

void *CDLList_deleteData(CDLListNode **cdllHead,
                         void *pToDelete,
                         UserCompareCallback DataCmp,
                         EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_INVALID_ARGS;
    void *pRet = NULL;

    if (cdllHead && *cdllHead && DataCmp) {
        CDLListNode *curr = *cdllHead;

        do {
            if (!DataCmp(curr->pData, pToDelete)) {

                if (curr == *cdllHead) {
                    if ((*cdllHead)->nxt == *cdllHead)
                        *cdllHead = NULL;
                    else
                        *cdllHead = curr->nxt;
                }

                curr->nxt->prv = curr->prv;
                curr->prv->nxt = curr->nxt;

                pRet = curr->pData;
                free(curr);

                tmp_err = EduDS_SUCCESS;

                break;
            }

            curr = curr->nxt;
        } while (curr != *cdllHead);
    }

    SAVE_ERR(err, tmp_err);

    return pRet;
}

CDLListNode *CDLList_at(CDLListNode *cdllHead,
                        size_t idx,
                        EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    CDLListNode *curr = NULL;

    if (cdllHead) {
        size_t i = 0;
        curr = cdllHead;
        do {
            if (idx == i)
                break;

            curr = curr->nxt;
            i++;
        } while (curr != cdllHead);

        if (i != idx)
            curr = NULL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

CDLListNode *CDLList_find(CDLListNode *cdllHead,
                          void *pToFind,
                          UserCompareCallback DataCmp,
                          EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    CDLListNode *ret = NULL;

    if (cdllHead && DataCmp) {
        CDLListNode *curr = cdllHead;

        do {
            if (!DataCmp(curr->pData, pToFind)) {
                ret = curr;
                break;
            }

            curr = curr->nxt;
        } while (curr != cdllHead);

        
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return ret;
}

void CDLList_traverse(CDLListNode *cdllHead,
                      UserDataCallback handleData,
                      EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (cdllHead && handleData) {
        CDLListNode *curr = cdllHead;

        do {
            handleData(curr->pData);
            curr = curr->nxt;
        } while (curr != cdllHead);
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void CDLList_destroy(CDLListNode **cdllHead,
                     UserDataCallback freeData,
                     EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (cdllHead && *cdllHead) {
        CDLListNode *curr, *tmp;

        //make the last node point to NULL
        //so that we can traverse the list as a non-circular list
        (*cdllHead)->prv->nxt = NULL;

        for (curr = *cdllHead; curr;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        *cdllHead = NULL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
