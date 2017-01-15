/***********************************************\
*                   LIFOstack.h                 *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __GiDS_LIFO_STACK_H
#define __GiDS_LIFO_STACK_H


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


GiDS_API LIFOstack *newLIFO(void);

GiDS_API void pushLIFO(LIFOstack *stack, void *node_data);

GiDS_API void *popLIFO(LIFOstack *stack);

GiDS_API void deleteLIFO(LIFOstack **stack, CustomDataCallback freeData);

GiDS_API void printLIFO(LIFOstack *stack, CustomDataCallback printData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_LIFO_STACK_H
