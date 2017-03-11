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


EduDS_API FIFOqueue *FIFO_init(EduDSErrCode *err);

EduDS_API void FIFO_enqueue(FIFOqueue *queue,
                            void *node_data,
                            EduDSErrCode *err);

EduDS_API void *FIFO_dequeue(FIFOqueue *queue,
                             EduDSErrCode *err);

EduDS_API void FIFO_destroy(FIFOqueue **queue,
                            UserDataCallback freeData,
                            EduDSErrCode *err);

EduDS_API void FIFO_traverse(FIFOqueue *queue,
                             UserDataCallback handleData,
                             EduDSErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_FIFO_QUEUE_H
