/***********************************************\
*              DoublyLinkedList.c               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "DoublyLinkedList.h"

void insertNodeDLList(DLListNode **dllHead, void *pData)
{
    if (dllHead) {
        DLListNode *new_node = malloc(sizeof(DLListNode));

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
}

void *deleteNodeDLList(DLListNode **dllHead, DLListNode *dllToDelete)
{
    void *pRet = NULL;

    if (dllHead && dllToDelete) {
        DLListNode *curr;

        for (curr = *dllHead; curr && (curr != dllToDelete); curr = curr->nxt);

        if (curr) {
            pRet = curr->pData;
               
            if (curr->nxt) {
                curr->nxt->prv = curr->prv;
            }

            if (curr->prv) {
                curr->prv->nxt = curr->nxt;
            }

            if (curr == *dllHead)
                *dllHead = curr->nxt;

            free(curr);
        }
    }

    return pRet;
}

DLListNode *findNodeDLList(DLListNode *dllHead, void *pToFind)
{
    DLListNode *curr;

    for (curr = dllHead; curr && (curr->pData != pToFind); curr = curr->nxt);

    return curr;
}

void printDLList(DLListNode *dllHead, CustomDataCallback printData)
{
    for (DLListNode *curr = dllHead; curr; curr = curr->nxt)
        printData(curr->pData);
}

void deleteDLList(DLListNode **dllHead, CustomDataCallback freeData)
{
    if (dllHead) {
        DLListNode *curr;

        for (curr = *dllHead; curr;) {
            if (freeData)
                freeData(curr->pData);

            DLListNode *tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        *dllHead = NULL;
    }
}
