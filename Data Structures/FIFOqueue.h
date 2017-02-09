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


GiDS_API FIFOqueue *newFIFO(void);

GiDS_API void enqueueFIFO(FIFOqueue *queue, void *node_data);

GiDS_API void *dequeueFIFO(FIFOqueue *queue);

GiDS_API void deleteFIFO(FIFOqueue **queue, CustomDataCallback freeData);

GiDS_API void traverseFIFO(FIFOqueue *queue, CustomDataCallback handleData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_FIFO_QUEUE_H
