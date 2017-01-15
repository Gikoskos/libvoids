/***********************************************\
*           SentinelSinglyLinkedList.c          *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "SentinelSinglyLinkedList.h"


SSLList *newSSLList(void)
{
    SSLList *newList = calloc(1, sizeof(SSLList));

    newList->head = calloc(1, sizeof(SLListNode));
    newList->sentinel = newList->head;

    return newList;
}

SLListNode *insertNodeSSLList(SSLList *ssllList, void *pData)
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

SLListNode *appendNodeSSLList(SSLList *ssllList, void *pData)
{
    SLListNode *new_node = NULL;

    if (ssllList) {
        if (ssllList->sentinel == ssllList->head) {

            new_node = insertNodeSSLList(ssllList, pData);
            
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

void *deleteNodeSSLList(SSLList *ssllList, void *pData)
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

SLListNode *findNodeSSLList(SSLList *ssllList, void *pToFind)
{
    SLListNode *curr = NULL;

    if (ssllList) {
        ssllList->sentinel->pData = pToFind;
        for (curr = ssllList->head; curr->pData != ssllList->sentinel; curr = curr->nxt);
    }

    return curr;
}

void printSSLList(SSLList *ssllList, CustomDataCallback printData)
{
    for (SLListNode *curr = ssllList->head; curr != ssllList->sentinel; curr = curr->nxt)
        printData(curr->pData);
}

void deleteSSLList(SSLList **ssllList, CustomDataCallback freeData)
{
    if (ssllList) {
        SLListNode *curr, *tmp;

        for (curr = (*ssllList)->head; curr != (*ssllList)->sentinel;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        if (*ssllList) {
            free((*ssllList)->sentinel);
            free(*ssllList);
        }
        *ssllList = NULL;
    }
}
