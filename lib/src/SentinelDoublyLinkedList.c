 /********************
 *  SentinelDoublyLinkedList.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "HeapAllocation.h"
#include "SentinelDoublyLinkedList.h"


SDLList *SDLList_init(vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    SDLList *newList = VdsMalloc(sizeof(SDLList));

    if (newList) {

        newList->head = VdsCalloc(1, sizeof(DLListNode));

        if (newList->head) {
            newList->sentinel = newList->head;
        } else {
            VdsFree(newList);
            newList = NULL;
            tmp_err = VDS_MALLOC_FAIL;
        }

    } else
        tmp_err = VDS_MALLOC_FAIL;

    SAVE_ERR(err, tmp_err);

    return newList;
}

DLListNode *SDLList_insert(SDLList *sdllList,
                           void *pData,
                           vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DLListNode *new_node = NULL;

    if (sdllList) {
        new_node = VdsMalloc(sizeof(DLListNode));

        if (new_node) {

            new_node->pData = pData;
            new_node->prv = NULL;
            new_node->nxt = sdllList->head;

            sdllList->head->prv = new_node;
            sdllList->head = new_node;

        } else
            tmp_err = VDS_MALLOC_FAIL;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

DLListNode *SDLList_append(SDLList *sdllList,
                           void *pData,
                           vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DLListNode *new_node = NULL;

    if (sdllList) {

        if (sdllList->head == sdllList->sentinel) {

            new_node = SDLList_insert(sdllList, pData, &tmp_err);

        } else {
            new_node = VdsMalloc(sizeof(DLListNode));
            new_node->pData = pData;
            new_node->nxt = sdllList->sentinel;
            new_node->prv = sdllList->sentinel->prv;
            sdllList->sentinel->prv->nxt = new_node;
            sdllList->sentinel->prv = new_node;
        }

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

void *SDLList_deleteNode(SDLList *sdllList,
                         DLListNode *sdllToDelete,
                         vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_INVALID_ARGS;
    void *pRet = NULL;

    if (sdllList) {
        DLListNode *curr;

        for (curr = sdllList->head; curr != sdllList->sentinel && curr != sdllToDelete; curr = curr->nxt);

        if (curr != sdllList->sentinel) {
            pRet = curr->pData;

            curr->nxt->prv = curr->prv;

            if (curr->prv)
                curr->prv->nxt = curr->nxt;
            else
                sdllList->head = curr->nxt;

            VdsFree(curr);
            tmp_err = VDS_SUCCESS;
        }
    }

    SAVE_ERR(err, tmp_err);

    return pRet;
}

void *SDLList_deleteData(SDLList *sdllList,
                         void *pToDelete,
                         vdsUserCompareFunc DataCmp,
                         vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_INVALID_ARGS;
    void *pRet = NULL;

    if (sdllList) {
        DLListNode *curr;
        sdllList->sentinel->pData = pToDelete;

        for (curr = sdllList->head; DataCmp(curr->pData, sdllList->sentinel->pData); curr = curr->nxt);

        if (curr != sdllList->sentinel) {
            pRet = curr->pData;

            curr->nxt->prv = curr->prv;

            if (curr->prv)
                curr->prv->nxt = curr->nxt;
            else
                sdllList->head = curr->nxt;

            VdsFree(curr);
            tmp_err = VDS_SUCCESS;
        }
    }

    SAVE_ERR(err, tmp_err);

    return pRet;
}

DLListNode *SDLList_at(SDLList *sdllList,
                       size_t idx,
                       vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DLListNode *curr = NULL;

    if (sdllList) {
        size_t i = 0;

        for (curr = sdllList->head; curr != sdllList->sentinel && i < idx; curr = curr->nxt, i++);

        if (curr == sdllList->sentinel)
            curr = NULL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

SDLList *SDLList_concat(SDLList *sdll1,
                        SDLList *sdll2,
                        vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    SDLList *ret = NULL;

    if (sdll1 && sdll2) {

        if (sdll1->sentinel != sdll1->head && sdll2->sentinel != sdll2->head) {

            DLListNode *tail1;

            tail1 = sdll1->sentinel->prv;

            tail1->nxt = sdll2->head;
            sdll2->head->prv = tail1;

            //order of VdsFree()'s is important here
            VdsFree(sdll1->sentinel);

            sdll1->sentinel = sdll2->sentinel;

            VdsFree(sdll2);

            ret = sdll1;
        }

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return ret;
}

DLListNode *SDLList_find(SDLList *sdllList,
                         void *pToFind,
                         vdsUserCompareFunc DataCmp,
                         vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DLListNode *curr = NULL;

    if (sdllList) {
        if (sdllList->sentinel != sdllList->head) {

            sdllList->sentinel->pData = pToFind;
            for (curr = sdllList->head; DataCmp(pToFind, curr->pData); curr = curr->nxt);

            if (curr == sdllList->sentinel)
                curr = NULL;

        }
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

void SDLList_traverse(SDLList *sdllList,
                      vdsTraverseFunc handleData,
                      vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (sdllList && handleData) {
        for (DLListNode *curr = sdllList->head;
             (curr != sdllList->sentinel) && handleData(curr->pData);
             curr = curr->nxt);
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void SDLList_destroy(SDLList **sdllList,
                     vdsUserDataFunc freeData,
                     vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (sdllList && *sdllList) {

        DLListNode *curr, *tmp;

        for (curr = (*sdllList)->head; curr != (*sdllList)->sentinel;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            VdsFree(tmp);
        }

        VdsFree((*sdllList)->sentinel);
        VdsFree(*sdllList);
        *sdllList = NULL;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
