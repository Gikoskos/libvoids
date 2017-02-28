/***********************************************\
*                   FIFOqueue.h                 *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __EduDS_FIFO_QUEUE_H
#define __EduDS_FIFO_QUEUE_H


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


EduDS_API FIFOqueue *FIFO_init(void);

EduDS_API void FIFO_enqueue(FIFOqueue *queue, void *node_data);

EduDS_API void *FIFO_dequeue(FIFOqueue *queue);

EduDS_API void FIFO_destroy(FIFOqueue **queue, CustomDataCallback freeData);

EduDS_API void FIFO_traverse(FIFOqueue *queue, CustomDataCallback handleData);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_FIFO_QUEUE_H
