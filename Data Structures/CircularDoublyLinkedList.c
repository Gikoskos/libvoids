/***********************************************\
*           CircularDoublyLinkedList.c          *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdlib.h>
#include "CircularDoublyLinkedList.h"

CDLListNode *insertFirstNodeCDLList(CDLListNode **cdllHead, void *pData)
{
    CDLListNode *new_node = NULL;

    if (cdllHead) {
        new_node = malloc(sizeof(CDLListNode));

        new_node->pData = pData;

        if (!(*cdllHead)) {
            new_node->nxt = new_node->prv = new_node;
        } else {
            new_node->prv = (*cdllHead)->prv;
            (*cdllHead)->prv->nxt = new_node;
            (*cdllHead)->prv = new_node;
            new_node->nxt = *cdllHead;
        }

        *cdllHead = new_node;
    }

    return new_node;
}

CDLListNode *insertLastNodeCDLList(CDLListNode **cdllHead, void *pData)
{
    CDLListNode *new_node = NULL;

    if (cdllHead) {
        new_node = malloc(sizeof(CDLListNode));

        new_node->pData = pData;

        if (!(*cdllHead)) {
            new_node->nxt = new_node->prv = NULL;
        } else {
            new_node->prv = (*cdllHead)->prv;
            new_node->nxt = *cdllHead;
            (*cdllHead)->prv->nxt = new_node;
            (*cdllHead)->prv = new_node;
        }
    }

    return new_node;
}

void *deleteNodeCDLList(CDLListNode **cdllHead, CDLListNode *cdllToDelete)
{
    void *pRet = NULL;

    if (cdllHead && *cdllHead && cdllToDelete) {
        CDLListNode *curr = *cdllHead;

        do {
            if (curr == cdllToDelete) {

                if (curr == *cdllHead) {
                    if ((*cdllHead)->nxt == *cdllHead)
                        *cdllHead = NULL;
                    else
                        *cdllHead = curr->nxt;
                }
                
                curr->nxt->prv = curr->prv;
                curr->prv->nxt = curr->nxt;

                free(curr);

                break;
            }

            curr = curr->nxt;
        } while (curr != *cdllHead);
    }

    return pRet;
}

CDLListNode *findNodeCDLList(CDLListNode *cdllHead, void *pToFind)
{
    if (cdllHead) {
        CDLListNode *curr = cdllHead;

        do {
            if (curr->pData == pToFind)
                return curr;

            curr = curr->nxt;
        } while (curr != cdllHead);

    }

    return NULL;
}

void traverseCDLList(CDLListNode *cdllHead, CustomDataCallback handleData)
{
    if (cdllHead && handleData) {
        CDLListNode *curr = cdllHead;

        do {
            handleData(curr->pData);
            curr = curr->nxt;
        } while (curr != cdllHead);
    }
}

void deleteCDLList(CDLListNode **cdllHead, CustomDataCallback freeData)
{
    if (cdllHead && *cdllHead) {
        CDLListNode *curr, *tmp;

        //make the last node point to NULL
        //so that we can traverse the list as a non-circular list
        (*cdllHead)->prv->nxt = NULL;

        for (curr = *cdllHead; curr;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        *cdllHead = NULL;
    }
}
