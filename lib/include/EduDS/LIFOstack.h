 /********************
 *  LIFOstack.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef EduDS_LIFO_STACK_H__
#define EduDS_LIFO_STACK_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _LIFOnode {
    void *data;
    struct _LIFOnode *next;
} LIFOnode;

typedef struct _LIFOstack {
    LIFOnode *head;
    LIFOnode *tail;
    unsigned int total_nodes;
} LIFOstack;


EduDS_API LIFOstack *LIFO_init(EdsErrCode *err);

EduDS_API void LIFO_push(LIFOstack *stack,
                         void *node_data,
                         EdsErrCode *err);

EduDS_API void *LIFO_pop(LIFOstack *stack,
                         EdsErrCode *err);

EduDS_API void LIFO_destroy(LIFOstack **stack,
                            UserDataCallback freeData,
                            EdsErrCode *err);

EduDS_API void LIFO_traverse(LIFOstack *stack,
                             UserDataCallback handleData,
                             EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //EduDS_LIFO_STACK_H__
