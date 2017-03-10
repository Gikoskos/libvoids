/***********************************************\
*           CircularSinglyLinkedList.c          *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include "CircularSinglyLinkedList.h"


CSLListNode *CSLList_insert(CSLListNode **csllHead,
                            void *pData,
                            EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    CSLListNode *new_node = NULL;

    if (csllHead) {
        new_node = malloc(sizeof(CSLListNode));

        if (new_node) {
            new_node->pData = pData;

            if (!(*csllHead)) {
                new_node->nxt = new_node;
            } else {

                CSLListNode *curr;

                for (curr = *csllHead; curr->nxt != *csllHead; curr = curr->nxt);

                new_node->nxt = *csllHead;
                curr->nxt = new_node;
            }

            *csllHead = new_node;
        } else
            tmp_err = EduDS_MALLOC_FAIL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

CSLListNode *CSLList_append(CSLListNode **csllHead,
                            void *pData,
                            EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    CSLListNode *new_node = NULL;

    if (csllHead) {

        if (!(*csllHead)) {
            new_node = CSLList_insert(csllHead, pData, &tmp_err);
        } else {
            new_node = malloc(sizeof(CSLListNode));

            if (new_node) {

                new_node->pData = pData;
                new_node->nxt = *csllHead;

                CSLListNode *curr;

                for (curr = *csllHead; curr->nxt != *csllHead; curr = curr->nxt);

                curr->nxt = new_node;

            } else
                tmp_err = EduDS_MALLOC_FAIL;
        }
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

CSLListNode *CSLList_concat(CSLListNode **csll_1,
                            CSLListNode *csll_2,
                            EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (csll_1 && *csll_1 && csll_2) {
        CSLListNode *tail_1, *tail_2;

        for (tail_1 = *csll_1; tail_1->nxt != *csll_1; tail_1 = tail_1->nxt);
        for (tail_2 = csll_2; tail_2->nxt != csll_2; tail_2 = tail_2->nxt);

        tail_2->nxt = *csll_1;
        tail_1->nxt = csll_2;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return *csll_1;
}

CSLListNode *CSLList_insertAfter(CSLListNode *csllPrev,
                                 void *pData,
                                 EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    CSLListNode *new_node = NULL;

    if (csllPrev) {
        new_node = malloc(sizeof(CSLListNode));

        if (new_node) {
            new_node->pData = pData;
            new_node->nxt = csllPrev->nxt;

            csllPrev->nxt = new_node;
        } else
            tmp_err = EduDS_MALLOC_FAIL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;

}

void *CSLList_deleteNode(CSLListNode **csllHead,
                         CSLListNode *csllToDelete,
                         EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    void *pRet = NULL;

    if (csllHead && *csllHead && csllToDelete) {
        CSLListNode *curr = *csllHead, *prev = NULL;

        do {
            if (curr == csllToDelete) {

                if (prev) {
                    prev->nxt = curr->nxt;
                } else {
                    CSLListNode *n;

                    for (n = curr->nxt; n->nxt != *csllHead; n = n->nxt);
                    n->nxt = curr->nxt;
                }

                if (curr == *csllHead) {
                    if ((*csllHead)->nxt == *csllHead)
                        *csllHead = NULL;
                    else
                        *csllHead = curr->nxt;
                }

                free(curr);

                break;
            }

            prev = curr;
            curr = curr->nxt;
        } while (curr != *csllHead);
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pRet;
}

CSLListNode *CSLList_find(CSLListNode *csllHead,
                          void *pToFind,
                          UserCompareCallback DataCmp,
                          EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (csllHead && DataCmp) {
        CSLListNode *curr = csllHead;

        do {
            if (!DataCmp(curr->pData, pToFind))
                return curr;

            curr = curr->nxt;
        } while (curr != csllHead);

    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return NULL;
}

void CSLList_traverse(CSLListNode *csllHead,
                      UserDataCallback handleData,
                      EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (csllHead && handleData) {
        CSLListNode *curr = csllHead;

        do {
            handleData(curr->pData);
            curr = curr->nxt;
        } while (curr != csllHead);
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void CSLList_destroy(CSLListNode **csllHead,
                     UserDataCallback freeData,
                     EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (csllHead && *csllHead) {
        CSLListNode *curr, *tmp;

        for (curr = (*csllHead)->nxt; curr != *csllHead;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        free(*csllHead);
        *csllHead = NULL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
