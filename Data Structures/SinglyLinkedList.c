/***********************************************\
*              SinglyLinkedList.c               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "SinglyLinkedList.h"

void insertNodeSLList(SLListNode **sllHead, void *pData)
{
    if (sllHead) {
        SLListNode *new_node = malloc(sizeof(SLListNode));

        new_node->pData = pData;
        new_node->nxt = NULL;

        if (!(*sllHead)) {
            *sllHead = new_node;
        } else {
            SLListNode *curr;

            for (curr = *sllHead; curr->nxt; curr = curr->nxt);

            curr->nxt = new_node;
        }
    }
}

void *deleteNodeSLList(SLListNode **sllHead, SLListNode *sllToDelete)
{
    void *pRet = NULL;

    if (sllHead && sllToDelete) {
        SLListNode *curr, *prev = NULL;

        for (curr = *sllHead; curr && (curr != sllToDelete); curr = curr->nxt)
            prev = curr;

        if (curr) {
            pRet = curr->pData;

            if (prev) {
                prev->nxt = curr->nxt;
                *sllHead = prev;
            } else {
                *sllHead = curr->nxt;
            }

            free(curr);
        }
    }

    return pRet;
}

SLListNode *findNodeSLList(SLListNode *sllHead, void *pToFind)
{
    SLListNode *curr;

    for (curr = sllHead; curr && (curr->pData != pToFind); curr = curr->nxt);

    return curr;
}

void printSLList(SLListNode *sllHead, CustomDataCallback printData)
{
    for (SLListNode *curr = sllHead; curr; curr = curr->nxt)
        printData(curr->pData);
}

void deleteSLList(SLListNode **sllHead, CustomDataCallback freeData)
{
    if (sllHead) {
        SLListNode *curr;

        for (curr = *sllHead; curr;) {
            if (freeData)
                freeData(curr->pData);

            SLListNode *tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        *sllHead = NULL;
    }
}
