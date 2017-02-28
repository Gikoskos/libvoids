/***********************************************\
*              DoublyLinkedList.c               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "DoublyLinkedList.h"


DLListNode *DLList_insert(DLListNode **dllHead, void *pData)
{
    DLListNode *new_node = NULL;

    if (dllHead) {
        new_node = malloc(sizeof(DLListNode));

        new_node->pData = pData;
        new_node->prv = NULL;
        new_node->nxt = *dllHead;

        if (*dllHead)
            (*dllHead)->prv = new_node;

        *dllHead = new_node;
    }

    return new_node;
}

DLListNode *DLList_append(DLListNode **dllHead, void *pData)
{
    DLListNode *new_node = NULL;

    if (dllHead) {
        new_node = malloc(sizeof(DLListNode));

        new_node->pData = pData;
        new_node->nxt = new_node->prv = NULL;

        if (!(*dllHead)) {
            *dllHead = new_node;
        } else {
            DLListNode *curr;

            for (curr = *dllHead; curr->nxt; curr = curr->nxt);

            curr->nxt = new_node;
            new_node->prv = curr;
        }
    }

    return new_node;
}

DLListNode *DLList_insertAfter(DLListNode *dllPrev, void *pData)
{
    DLListNode *new_node = NULL;

    if (dllPrev) {
        new_node = malloc(sizeof(DLListNode));

        new_node->pData = pData;
        new_node->nxt = dllPrev->nxt;
        new_node->prv = dllPrev;

        dllPrev->nxt = new_node;
    }

    return new_node;
}

void *DLList_deleteNode(DLListNode **dllHead, DLListNode *dllToDelete)
{
    void *pRet = NULL;

    if (dllHead && dllToDelete) {
        DLListNode *curr;

        for (curr = *dllHead; curr && (curr != dllToDelete); curr = curr->nxt);

        if (curr) {
            pRet = curr->pData;
               
            if (curr->nxt)
                curr->nxt->prv = curr->prv;

            if (curr->prv)
                curr->prv->nxt = curr->nxt;
            else
                *dllHead = curr->nxt;

            free(curr);
        }
    }

    return pRet;
}

DLListNode *DLList_find(DLListNode *dllHead, void *pToFind)
{
    DLListNode *curr;

    for (curr = dllHead; curr && (curr->pData != pToFind); curr = curr->nxt);

    return curr;
}

void DLList_traverse(DLListNode *dllHead, CustomDataCallback handleData)
{
    if (handleData)
        for (DLListNode *curr = dllHead; curr; curr = curr->nxt)
            handleData(curr->pData);
}

void DLList_destroy(DLListNode **dllHead, CustomDataCallback freeData)
{
    if (dllHead) {
        DLListNode *curr, *tmp;

        for (curr = *dllHead; curr;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        *dllHead = NULL;
    }
}
