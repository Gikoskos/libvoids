/***********************************************\
*           SentinelSinglyLinkedList.c          *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "SentinelSinglyLinkedList.h"


SSLList *SSLList_init(void)
{
    SSLList *newList = calloc(1, sizeof(SSLList));

    newList->head = calloc(1, sizeof(SLListNode));
    newList->sentinel = newList->head;

    return newList;
}

SLListNode *SSLList_insert(SSLList *ssllList, void *pData)
{
    SLListNode *new_node = NULL;

    if (ssllList) {

        new_node = malloc(sizeof(SLListNode));

        new_node->pData = pData;

        new_node->nxt = ssllList->head;
        ssllList->head = new_node;

    }

    return new_node;
}

SLListNode *SSLList_append(SSLList *ssllList, void *pData)
{
    SLListNode *new_node = NULL;

    if (ssllList) {
        if (ssllList->sentinel == ssllList->head) {

            new_node = SSLList_insert(ssllList, pData);
            
        } else {
            SLListNode *curr;

            new_node = malloc(sizeof(SLListNode));

            new_node->pData = pData;
            new_node->nxt = ssllList->sentinel;

            for (curr = ssllList->head; curr->nxt != ssllList->sentinel; curr = curr->nxt);

            curr->nxt = new_node;
        }
    }

    return new_node;
}

void *SSLList_deleteNode(SSLList *ssllList, void *pData)
{
    void *pRet = NULL;

    if (ssllList) {
        SLListNode *curr, *prev = NULL;

        ssllList->sentinel->pData = pData;
        for (curr = ssllList->head; curr->pData != pData; curr = curr->nxt)
            prev = curr;

        if (curr != ssllList->sentinel) {
            pRet = pData;

            if (prev)
                prev->nxt = curr->nxt;
            else
                ssllList->head = curr->nxt;

            free(curr);
        }
    }

    return pRet;
}

SLListNode *SSLList_find(SSLList *ssllList, void *pToFind)
{
    SLListNode *curr = NULL;

    if (ssllList) {
        ssllList->sentinel->pData = pToFind;
        for (curr = ssllList->head; curr->pData != ssllList->sentinel; curr = curr->nxt);

        if (curr == ssllList->sentinel)
            curr = NULL;
    }

    return curr;
}

void SSLList_traverse(SSLList *ssllList, UserDataCallback handleData)
{
    if (ssllList && handleData)
        for (SLListNode *curr = ssllList->head; curr != ssllList->sentinel; curr = curr->nxt)
            handleData(curr->pData);
}

void SSLList_destroy(SSLList **ssllList, UserDataCallback freeData)
{
    if (ssllList && *ssllList) {
        SLListNode *curr, *tmp;

        for (curr = (*ssllList)->head; curr != (*ssllList)->sentinel;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        free((*ssllList)->sentinel);
        free(*ssllList);
        *ssllList = NULL;
    }
}
