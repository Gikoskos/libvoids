/***********************************************\
*                   FIFOqueue.c                 *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "FIFOqueue.h"

#ifdef _WIN32
# include <windows.h>
# define q_free(x)          HeapFree(GetProcessHeap(), 0, x)
# define q_malloc(x)        HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY, x)
# define q_calloc(x, y)     win_malloc(x * y)
# define q_realloc(NULL, x) win_malloc(x)
#else
# define q_free(x)          free(x)
# define q_malloc(x)        malloc(x)
# define q_calloc(x, y)     mallox(x * y)
# define q_realloc(NULL, x) malloc(x)
#endif

/* Prototypes for functions with local scope */
static FIFOnode *newFIFOnode(void *node_data);


static FIFOnode *newFIFOnode(void *node_data)
{
    FIFOnode *newnode = (FIFOnode*)q_malloc(sizeof(FIFOnode));

    if (!newnode) {
        fprintf(stderr, "Failed allocating memory for new node!\n");
        return NULL;
    }

    newnode->data = node_data;
    newnode->next = (FIFOnode*)NULL;
    return (FIFOnode*)newnode;
}

FIFOqueue *newFIFOqueue(void)
{
    FIFOqueue *newqueue = (FIFOqueue*)q_malloc(sizeof(FIFOqueue));

    if (!newqueue) {
        fprintf(stderr, "Failed allocating memory for new queue!\n");
        return (FIFOqueue*)NULL;
    }

    newqueue->head = newqueue->tail = (FIFOnode*)NULL;
    newqueue->total_nodes = 0;
    return newqueue;
}

bool FIFOenqueue(FIFOqueue *queue, void *node_data)
{
    FIFOnode *to_inject = newFIFOnode(node_data);

    if (!to_inject || !queue) {
        fprintf(stderr, "Failed injecting new node to queue!\n");
        return false;
    }

    if (!queue->total_nodes)
        queue->head = to_inject;
    else
        queue->tail->next = to_inject;

    queue->tail = to_inject;
    queue->total_nodes++;
    return true;
}

void *FIFOdequeue(FIFOqueue *queue)
{
    if (!queue || !queue->total_nodes) { //short-circuit eval protection
        fprintf(stderr, "Dequeue operation failed!\n");
        return NULL;
    }

    FIFOnode *to_pop = queue->head;
    void *retvalue = to_pop->data;

    queue->head = queue->head->next;
    q_free((void*)to_pop);
    queue->total_nodes--;
    return retvalue;
}

bool deleteFIFOqueue(FIFOqueue *queue, int flag)
{
    if (!queue) {
        fprintf(stderr, "Empty queue given!\n");
        return false;
    }

    if (queue->total_nodes) {
        FIFOnode *curr;
        for (curr = queue->head; curr && queue->total_nodes;) {
            FIFOnode *to_delete = curr;
            curr = curr->next;
            if (to_delete->data && flag != DONT_DELETE_DATA) {
                switch (flag) {
                case MALLOC_FREE_DATA:
                    free(to_delete->data);
                    to_delete->data = NULL;
                    break;
                case WIN_MALLOC_FREE_DATA:
                    q_free(to_delete->data);
                    to_delete->data = NULL;
                    break;
                default:
                    break;
                }
            }
            q_free((void*)to_delete);
            to_delete = NULL;
            queue->total_nodes--;
        }
    }

    q_free((void*)queue);
    queue = (FIFOqueue*)NULL;
    return true;
}
