/***********************************************\
*                   LIFOstack.h                 *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __EduDS_LIFO_STACK_H
#define __EduDS_LIFO_STACK_H


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


EduDS_API LIFOstack *LIFO_init(EduDSErrCode *err);

EduDS_API void LIFO_push(LIFOstack *stack,
                         void *node_data,
                         EduDSErrCode *err);

EduDS_API void *LIFO_pop(LIFOstack *stack,
                         EduDSErrCode *err);

EduDS_API void LIFO_destroy(LIFOstack **stack,
                            UserDataCallback freeData,
                            EduDSErrCode *err);

EduDS_API void LIFO_traverse(LIFOstack *stack,
                             UserDataCallback handleData,
                             EduDSErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_LIFO_STACK_H
