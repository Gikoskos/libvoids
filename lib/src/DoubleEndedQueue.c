 /********************
 *  DoubleEndedQueue.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "HeapAllocation.h"
#include "DoubleEndedQueue.h"


Dequeue *Dequeue_init(vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    Dequeue *newDequeue = VdsCalloc(1, sizeof(Dequeue));

    if (!newDequeue)
        tmp_err = VDS_MALLOC_FAIL;

    SAVE_ERR(err, tmp_err);

    return newDequeue;
}

DLListNode *Dequeue_push(Dequeue *dequeue,
                         void *pData,
                         vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DLListNode *new_node = NULL;

    if (dequeue && pData) {
        new_node = VdsMalloc(sizeof(DLListNode));

        if (new_node) {
            new_node->pData = pData;
            new_node->prv = NULL;
            new_node->nxt = dequeue->head;

            if (!dequeue->head)
                dequeue->tail = new_node;
            else
                dequeue->head->prv = new_node;

            dequeue->head = new_node;

        } else
            tmp_err = VDS_MALLOC_FAIL;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

DLListNode *Dequeue_inject(Dequeue *dequeue,
                           void *pData,
                           vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DLListNode *new_node = NULL;

    if (dequeue && pData) {

        if (!dequeue->tail) {
            new_node = Dequeue_push(dequeue, pData, &tmp_err);
        } else {
            new_node = VdsMalloc(sizeof(DLListNode));

            if (new_node) {
                new_node->pData = pData;
                new_node->nxt = NULL;
                new_node->prv = dequeue->tail;

                dequeue->tail->nxt = new_node;
                dequeue->tail = new_node;
            } else
                tmp_err = VDS_MALLOC_FAIL;
        }
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

void *Dequeue_eject(Dequeue *dequeue,
                    vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    void *pEjected = NULL;

    if (dequeue && dequeue->head) {
        DLListNode *tmp = dequeue->tail;

        pEjected = tmp->pData;

        dequeue->tail = tmp->prv;

        if (dequeue->tail)
            dequeue->tail->nxt = NULL;
        else
            dequeue->head = NULL;

        VdsFree(tmp);
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pEjected;
}

void *Dequeue_pop(Dequeue *dequeue,
                  vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    void *pPopped = NULL;

    if (dequeue && dequeue->head) {
        DLListNode *tmp = dequeue->head;

        pPopped = tmp->pData;

        dequeue->head = tmp->nxt;

        if (dequeue->head)
            dequeue->head->prv = NULL;
        else
            dequeue->tail = NULL;

        VdsFree(tmp);
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pPopped;
}

void Dequeue_destroy(Dequeue **dequeue,
                     vdsUserDataFunc freeData,
                     vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (dequeue && *dequeue) {

        DLListNode *curr, *tmp;

        for (curr = (*dequeue)->head; curr;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            VdsFree(tmp);
        }

        VdsFree(*dequeue);
        *dequeue = NULL;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
