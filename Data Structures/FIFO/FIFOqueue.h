/***********************************************\
*                   FIFOqueue.h                 *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __FIFO_QUEUE_H
#define __FIFO_QUEUE_H

#include <stdbool.h>

#define MALLOC_FREE_DATA         0x000a
#define WIN_MALLOC_FREE_DATA     0x000b
#define DONT_DELETE_DATA         0x000c

typedef struct _FIFOnode {
    void *data;
    struct _FIFOnode *next;
} FIFOnode;

typedef struct _FIFOqueue {
    FIFOnode *head;
    FIFOnode *tail;
    unsigned int total_nodes;
} FIFOqueue;

#ifdef __cplusplus
extern "C" {
#endif

FIFOqueue *newFIFOqueue(void);
bool FIFOenqueue(FIFOqueue *queue, void *node_data);
void *FIFOdequeue(FIFOqueue *queue);
bool deleteFIFOqueue(FIFOqueue *queue, int flag);

#ifdef __cplusplus
}
#endif

#endif //__FIFO_QUEUE_H
