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

    if (!newnode)
        return NULL;

    newnode->data = node_data;
    newnode->next = (FIFOnode*)NULL;
    return (FIFOnode*)newnode;
}

FIFOqueue *FIFO_init(void)
{
    FIFOqueue *newqueue = (FIFOqueue*)malloc(sizeof(FIFOqueue));

    if (!newqueue)
        return (FIFOqueue*)NULL;

    newqueue->head = newqueue->tail = (FIFOnode*)NULL;
    newqueue->total_nodes = 0;
    return newqueue;
}

void FIFO_enqueue(FIFOqueue *queue, void *node_data)
{
    if (queue) {
        FIFOnode *to_inject = newFIFOnode(node_data);

        if (to_inject) {
            if (!queue->total_nodes)
                queue->head = to_inject;
            else
                queue->tail->next = to_inject;

            queue->tail = to_inject;
            queue->total_nodes++;
        }

    }
}

void *FIFO_dequeue(FIFOqueue *queue)
{
    void *pData = NULL;

    if (queue && queue->total_nodes) {//short-circuit eval protection

        FIFOnode *to_pop = queue->head;
        pData = to_pop->data;

        queue->head = queue->head->next;
        free((void*)to_pop);
        queue->total_nodes--;
    }

    return pData;
}

void FIFO_destroy(FIFOqueue **queue, CustomDataCallback freeData)
{
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

    }
}

void FIFO_traverse(FIFOqueue *queue, CustomDataCallback handleData)
{
    if (queue && handleData)
        for (FIFOnode *curr = queue->head; curr; curr = curr->next)
            handleData(curr->data);
}
