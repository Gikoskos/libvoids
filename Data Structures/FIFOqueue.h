/***********************************************\
*                   FIFOqueue.h                 *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __GiDS_FIFO_QUEUE_H
#define __GiDS_FIFO_QUEUE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _FIFOnode {
    void *data;
    struct _FIFOnode *next;
} FIFOnode;

typedef struct _FIFOqueue {
    FIFOnode *head;
    FIFOnode *tail;
    unsigned int total_nodes;
} FIFOqueue;


GiDS_API FIFOqueue *FIFO_init(void);

GiDS_API void FIFO_enqueue(FIFOqueue *queue, void *node_data);

GiDS_API void *FIFO_dequeue(FIFOqueue *queue);

GiDS_API void FIFO_destroy(FIFOqueue **queue, CustomDataCallback freeData);

GiDS_API void FIFO_traverse(FIFOqueue *queue, CustomDataCallback handleData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_FIFO_QUEUE_H
