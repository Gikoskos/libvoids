/***********************************************\
*                   FIFOqueue.c                 *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "FIFOqueue.h"


/* Prototypes for functions with local scope */
static FIFOnode *newFIFOnode(void *node_data);

FIFOnode *newFIFOnode(void *node_data)
{
    FIFOnode *newnode = (FIFOnode*)malloc(sizeof(FIFOnode));

    if (newnode) {

        newnode->data = node_data;
        newnode->next = (FIFOnode*)NULL;

    }

    return newnode;
}

FIFOqueue *FIFO_init(EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    FIFOqueue *newqueue = malloc(sizeof(FIFOqueue));

    if (newqueue) {
        newqueue->head = newqueue->tail = NULL;
        newqueue->total_nodes = 0;
    } else
        tmp_err = EduDS_MALLOC_FAIL;

    SAVE_ERR(err, tmp_err);

    return newqueue;
}

void FIFO_enqueue(FIFOqueue *queue,
                  void *node_data,
                  EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (queue) {
        FIFOnode *to_inject = newFIFOnode(node_data);

        if (to_inject) {
            if (!queue->total_nodes)
                queue->head = to_inject;
            else
                queue->tail->next = to_inject;

            queue->tail = to_inject;
            queue->total_nodes++;
        } else
            tmp_err = EduDS_MALLOC_FAIL;

    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void *FIFO_dequeue(FIFOqueue *queue,
                   EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    void *pData = NULL;

    if (queue && queue->total_nodes) {//short-circuit eval protection

        FIFOnode *to_pop = queue->head;
        pData = to_pop->data;

        queue->head = queue->head->next;
        free((void*)to_pop);
        queue->total_nodes--;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pData;
}

void FIFO_destroy(FIFOqueue **queue,
                  UserDataCallback freeData,
                  EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (queue && (*queue)) {

        if ((*queue)->total_nodes) {
            FIFOnode *curr;
            for (curr = (*queue)->head; curr && (*queue)->total_nodes;) {
                FIFOnode *to_delete = curr;
                curr = curr->next;

                if (to_delete->data && freeData)
                    freeData(to_delete->data);

                free((void*)to_delete);
                to_delete = NULL;
                (*queue)->total_nodes--;
            }
        }

        free(*queue);
        *queue = NULL;

    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void FIFO_traverse(FIFOqueue *queue,
                   UserDataCallback handleData,
                   EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (queue && handleData)
        for (FIFOnode *curr = queue->head; curr; curr = curr->next)
            handleData(curr->data);
    else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
