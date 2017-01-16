/***********************************************\
*           SentinelDoublyLinkedList.c          *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "SentinelDoublyLinkedList.h"


SDLList *newSDLList(void)
{
    SDLList *newList = calloc(1, sizeof(SDLList));

    newList->head = calloc(1, sizeof(DLListNode));
    newList->sentinel = newList->head;

    return newList;
}

DLListNode *insertNodeSDLList(SDLList *sdllList, void *pData)
{
    DLListNode *new_node = NULL;

    if (sdllList) {
        new_node = malloc(sizeof(DLListNode));

        new_node->pData = pData;
        new_node->prv = NULL;
        new_node->nxt = sdllList->head;

        sdllList->head->prv = new_node;
        sdllList->head = new_node;
    }

    return new_node;
}

DLListNode *appendNodeSDLList(SDLList *sdllList, void *pData)
{
    DLListNode *new_node = NULL;

    if (sdllList) {
        if (sdllList->head == sdllList->sentinel) {

            new_node = insertNodeSDLList(sdllList, pData);

        } else {
            new_node = malloc(sizeof(DLListNode));
            new_node->pData = pData;
            new_node->nxt = sdllList->sentinel;
            new_node->prv = sdllList->sentinel->prv;
            sdllList->sentinel->prv->nxt = new_node;
            sdllList->sentinel->prv = new_node;
        }
    }

    return new_node;
}

void *deleteNodeSDLList(SDLList *sdllList, void *pToDelete)
{
    void *pRet = NULL;

    if (sdllList) {
        DLListNode *curr;
        sdllList->sentinel->pData = pToDelete;

        for (curr = sdllList->head; curr->pData != sdllList->sentinel->pData; curr = curr->nxt);

        if (curr != sdllList->sentinel) {
            pRet = curr->pData;

            curr->nxt->prv = curr->prv;

            if (curr->prv)
                curr->prv->nxt = curr->nxt;
            else
                sdllList->head = curr->nxt;

            free(curr);
        }
    }

    return pRet;
}

DLListNode *findNodeSDLList(SDLList *sdllList, void *pToFind)
{
    DLListNode *curr;

    if (sdllList) {
        sdllList->sentinel->pData = pToFind;
        for (curr = sdllList->head; curr->pData != sdllList->sentinel->pData; curr = curr->nxt);

        if (curr == sdllList->sentinel)
            curr = NULL;
    }

    return curr;
}

void printSDLList(SDLList *sdllList, CustomDataCallback printData)
{
    if (sdllList)
        for (DLListNode *curr = sdllList->head; curr != sdllList->sentinel; curr = curr->nxt)
            printData(curr->pData);
}

void deleteSDLList(SDLList **sdllList, CustomDataCallback freeData)
{
    if (sdllList) {
        DLListNode *curr, *tmp;

        for (curr = (*sdllList)->head; curr != (*sdllList)->sentinel;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        if (*sdllList) {
            free((*sdllList)->sentinel);
            free(*sdllList);
            *sdllList = NULL;
        }
    }
}
