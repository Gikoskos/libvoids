 /********************
 *  FIFOqueue.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef EduDS_FIFO_QUEUE_H__
#define EduDS_FIFO_QUEUE_H__


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


EduDS_API FIFOqueue *FIFO_init(EdsErrCode *err);

EduDS_API void FIFO_enqueue(FIFOqueue *queue,
                            void *node_data,
                            EdsErrCode *err);

EduDS_API void *FIFO_dequeue(FIFOqueue *queue,
                             EdsErrCode *err);

EduDS_API void FIFO_destroy(FIFOqueue **queue,
                            UserDataCallback freeData,
                            EdsErrCode *err);

EduDS_API void FIFO_traverse(FIFOqueue *queue,
                             UserDataCallback handleData,
                             EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //EduDS_FIFO_QUEUE_H__
