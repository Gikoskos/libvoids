/***********************************************\
*                   LIFOstack.c                 *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "LIFOstack.h"


/* Prototypes for functions with local scope */
static LIFOnode *newLIFOnode(void *node_data);


static LIFOnode *newLIFOnode(void *node_data)
{
    LIFOnode *newnode = malloc(sizeof(LIFOnode));

    if (!newnode)
        return NULL;

    newnode->data = node_data;
    newnode->next = NULL;
    return newnode;
}

LIFOstack *LIFO_init(EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    LIFOstack *newstack = calloc(1, sizeof(LIFOstack));

    if (!newstack)
        tmp_err = EduDS_MALLOC_FAIL;

    SAVE_ERR(err, tmp_err);
    return newstack;
}

void LIFO_push(LIFOstack *stack,
               void *node_data,
               EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (stack) {
        LIFOnode *to_push = newLIFOnode(node_data);

        if (to_push) {
            if (!stack->total_nodes)
                stack->head = to_push;
            else
                stack->tail->next = to_push;

            stack->tail = to_push;
            stack->total_nodes++;
        } else
            tmp_err = EduDS_MALLOC_FAIL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void *LIFO_pop(LIFOstack *stack,
               EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    void *pData = NULL;

    if (stack && stack->total_nodes) {

        LIFOnode *to_pop = stack->tail, *curr;
        pData = to_pop->data;

        if (stack->total_nodes == 1) {
            stack->tail = stack->head = NULL;
        } else {
            for (curr = stack->head; curr->next != stack->tail; curr = curr->next);
            stack->tail = curr;
            stack->tail->next = NULL;
        }

        free((void*)to_pop);
        stack->total_nodes--;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pData;
}

void LIFO_destroy(LIFOstack **stack,
                  UserDataCallback freeData,
                  EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (stack && *stack) {

        if ((*stack)->total_nodes) {
            LIFOnode *curr;
            for (curr = (*stack)->head; curr && (*stack)->total_nodes;) {
                LIFOnode *to_delete = curr;
                curr = curr->next;

                if (to_delete->data && freeData)
                    freeData(to_delete->data);

                free((void*)to_delete);
                to_delete = NULL;
                (*stack)->total_nodes--;
            }
        }

        free(*stack);
        *stack = NULL;
    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void LIFO_traverse(LIFOstack *stack,
                   UserDataCallback handleData,
                   EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (stack && handleData)
        for (LIFOnode *curr = stack->head; curr; curr = curr->next)
            handleData(curr->data);
    else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
