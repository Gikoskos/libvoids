 /********************
 *  CircularSinglyLinkedList.c
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include <stdlib.h>
#include "CircularSinglyLinkedList.h"


CSLListNode *CSLList_insert(CSLListNode **csllHead,
                            void *pData,
                            EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
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
            tmp_err = EDS_MALLOC_FAIL;
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

CSLListNode *CSLList_append(CSLListNode **csllHead,
                            void *pData,
                            EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
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
                tmp_err = EDS_MALLOC_FAIL;
        }
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

CSLListNode *CSLList_concat(CSLListNode *csll_1,
                            CSLListNode *csll_2,
                            EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    CSLListNode *ret = NULL;

    if (csll_1 && csll_2) {
        CSLListNode *tail_1, *tail_2;

        for (tail_1 = csll_1; tail_1->nxt != csll_1; tail_1 = tail_1->nxt);
        for (tail_2 = csll_2; tail_2->nxt != csll_2; tail_2 = tail_2->nxt);

        tail_2->nxt = csll_1;
        tail_1->nxt = csll_2;

        ret = csll_1;
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return ret;
}

CSLListNode *CSLList_insertAfter(CSLListNode *csllPrev,
                                 void *pData,
                                 EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    CSLListNode *new_node = NULL;

    if (csllPrev) {
        new_node = malloc(sizeof(CSLListNode));

        if (new_node) {
            new_node->pData = pData;
            new_node->nxt = csllPrev->nxt;

            csllPrev->nxt = new_node;
        } else
            tmp_err = EDS_MALLOC_FAIL;
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

void *CSLList_deleteNode(CSLListNode **csllHead,
                         CSLListNode *csllToDelete,
                         EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_INVALID_ARGS;
    void *pRet = NULL;

    if (csllHead && *csllHead && csllToDelete) {
        CSLListNode *curr = *csllHead, *prev = NULL;

        do {
            if (curr == csllToDelete) {

                pRet = curr->pData;
                if (prev) {
                    prev->nxt = curr->nxt;
                } else {

                    if (curr->nxt == curr) {
                        *csllHead = NULL;
                    } else {
                        CSLListNode *tail;

                        for (tail = curr->nxt; tail->nxt != *csllHead; tail = tail->nxt);

                        tail->nxt = curr->nxt;

                        *csllHead = curr->nxt;
                    }
                }

                free(curr);

                tmp_err = EDS_SUCCESS;
                break;
            }

            prev = curr;
            curr = curr->nxt;
        } while (curr != *csllHead);
    }

    SAVE_ERR(err, tmp_err);

    return pRet;
}

void *CSLList_deleteData(CSLListNode **csllHead,
                         void *pToDelete,
                         UserCompareCallback DataCmp,
                         EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_INVALID_ARGS;
    void *pRet = NULL;

    if (csllHead && *csllHead && DataCmp) {
        CSLListNode *curr = *csllHead, *prev = NULL;

        do {
            if (!DataCmp(curr->pData, pToDelete)) {

                pRet = curr->pData;

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

                tmp_err = EDS_SUCCESS;
                break;
            }

            prev = curr;
            curr = curr->nxt;
        } while (curr != *csllHead);
    }

    SAVE_ERR(err, tmp_err);

    return pRet;
}

CSLListNode *CSLList_at(CSLListNode *csllHead,
                        size_t idx,
                        EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    CSLListNode *curr = NULL;

    if (csllHead) {
        size_t i = 0;
        curr = csllHead;

        while (1) {
            if (idx == i)
                break;

            curr = curr->nxt;
            i++;

            if (curr == csllHead) {
                curr = NULL;
                break;
            }
        }

    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

CSLListNode *CSLList_find(CSLListNode *csllHead,
                          void *pToFind,
                          UserCompareCallback DataCmp,
                          EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    CSLListNode *curr = NULL;

    if (csllHead && DataCmp) {
        curr = csllHead;

        do {
            if (!DataCmp(curr->pData, pToFind))
                break;

            curr = curr->nxt;
        } while (curr != csllHead);

    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

void CSLList_traverse(CSLListNode *csllHead,
                      UserDataCallback handleData,
                      EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;

    if (csllHead && handleData) {
        CSLListNode *curr = csllHead;

        do {
            handleData(curr->pData);
            curr = curr->nxt;
        } while (curr != csllHead);
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void CSLList_destroy(CSLListNode **csllHead,
                     UserDataCallback freeData,
                     EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;

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
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
