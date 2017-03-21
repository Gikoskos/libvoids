 /********************
 *  DoubleEndedQueue.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef __EduDS_DEQUEUE__H
#define __EduDS_DEQUEUE__H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"
#include "DoublyLinkedList.h"


typedef struct _Dequeue {
    DLListNode *head, *tail;
} Dequeue;


EduDS_API Dequeue *Dequeue_init(EdsErrCode *err);

EduDS_API DLListNode *Dequeue_push(Dequeue *dequeue,
                                   void *pData,
                                   EdsErrCode *err);

EduDS_API DLListNode *Dequeue_inject(Dequeue *dequeue,
                                     void *pData,
                                     EdsErrCode *err);

EduDS_API void *Dequeue_eject(Dequeue *dequeue,
                              EdsErrCode *err);

EduDS_API void *Dequeue_pop(Dequeue *dequeue,
                            EdsErrCode *err);

EduDS_API void Dequeue_destroy(Dequeue **dequeue,
                               UserDataCallback freeData,
                               EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_DEQUEUE__H
