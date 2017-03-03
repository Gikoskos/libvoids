/***********************************************\
*           SentinelDoublyLinkedList.c          *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "SentinelDoublyLinkedList.h"


SDLList *SDLList_init(void)
{
    SDLList *newList = calloc(1, sizeof(SDLList));

    newList->head = calloc(1, sizeof(DLListNode));
    newList->sentinel = newList->head;

    return newList;
}

DLListNode *SDLList_insert(SDLList *sdllList, void *pData)
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

DLListNode *SDLList_append(SDLList *sdllList, void *pData)
{
    DLListNode *new_node = NULL;

    if (sdllList) {
        if (sdllList->head == sdllList->sentinel) {

            new_node = SDLList_insert(sdllList, pData);

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

void *SDLList_deleteNode(SDLList *sdllList, void *pToDelete)
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

DLListNode *SDLList_find(SDLList *sdllList, void *pToFind)
{
    DLListNode *curr = NULL;

    if (sdllList) {
        sdllList->sentinel->pData = pToFind;
        for (curr = sdllList->head; curr->pData != sdllList->sentinel->pData; curr = curr->nxt);

        if (curr == sdllList->sentinel)
            curr = NULL;
    }

    return curr;
}

void SDLList_traverse(SDLList *sdllList, UserDataCallback handleData)
{
    if (sdllList && handleData)
        for (DLListNode *curr = sdllList->head; curr != sdllList->sentinel; curr = curr->nxt)
            handleData(curr->pData);
}

void SDLList_destroy(SDLList **sdllList, UserDataCallback freeData)
{
    if (sdllList && *sdllList) {
        DLListNode *curr, *tmp;

        for (curr = (*sdllList)->head; curr != (*sdllList)->sentinel;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        free((*sdllList)->sentinel);
        free(*sdllList);
        *sdllList = NULL;
    }
}
