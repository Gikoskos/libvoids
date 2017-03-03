/***********************************************\
*           CircularSinglyLinkedList.c          *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include "CircularSinglyLinkedList.h"


CSLListNode *CSLList_insert(CSLListNode **csllHead, void *pData)
{
    CSLListNode *new_node = NULL;

    if (csllHead) {
        new_node = malloc(sizeof(CSLListNode));

        new_node->pData = pData;

        if (!(*csllHead)) {
            new_node->nxt = new_node;
        } else {

            CSLListNode *curr;

            for (curr = *csllHead; curr->nxt != *csllHead; curr = curr->nxt);

            new_node->nxt = *csllHead;
            curr->nxt = new_node;
        }

        *csllHead = new_node;
    }

    return new_node;
}

CSLListNode *CSLList_append(CSLListNode **csllHead, void *pData)
{
    CSLListNode *new_node = NULL;

    if (csllHead) {

        if (!(*csllHead)) {
            new_node = CSLList_insert(csllHead, pData);
        } else {
            new_node = malloc(sizeof(CSLListNode));

            new_node->pData = pData;
            new_node->nxt = *csllHead;

            CSLListNode *curr;

            for (curr = *csllHead; curr->nxt != *csllHead; curr = curr->nxt);

            curr->nxt = new_node;
        }
    }

    return new_node;
}

CSLListNode *CSLList_insertAfter(CSLListNode *csllPrev, void *pData)
{
    CSLListNode *new_node = NULL;

    if (csllPrev) {
        new_node = malloc(sizeof(CSLListNode));

        new_node->pData = pData;
        new_node->nxt = csllPrev->nxt;

        csllPrev->nxt = new_node;
    }

    return new_node;

}

void *CSLList_deleteNode(CSLListNode **csllHead, CSLListNode *csllToDelete)
{
    void *pRet = NULL;

    if (csllHead && *csllHead && csllToDelete) {
        CSLListNode *curr = *csllHead, *prev = NULL;

        do {
            if (curr == csllToDelete) {

                if (prev) {
                    prev->nxt = curr->nxt;
                } else {
                    CSLListNode *n;

                    for (n = curr->nxt; n->nxt != *csllHead; n = n->nxt);
                    n->nxt = curr->nxt;
                }

                if (curr == *csllHead) {
                    if ((*csllHead)->nxt == *csllHead)
                        *csllHead = NULL;
                    else
                        *csllHead = curr->nxt;
                }

                free(curr);

                break;
            }

            prev = curr;
            curr = curr->nxt;
        } while (curr != *csllHead);
    }

    return pRet;
}

CSLListNode *CSLList_find(CSLListNode *csllHead, void *pToFind)
{
    if (csllHead) {
        CSLListNode *curr = csllHead;

        do {
            if (curr->pData == pToFind)
                return curr;

            curr = curr->nxt;
        } while (curr != csllHead);

    }

    return NULL;
}

void CSLList_traverse(CSLListNode *csllHead, UserDataCallback handleData)
{
    if (csllHead && handleData) {
        CSLListNode *curr = csllHead;

        do {
            handleData(curr->pData);
            curr = curr->nxt;
        } while (curr != csllHead);
    }
}

void CSLList_destroy(CSLListNode **csllHead, UserDataCallback freeData)
{
    if (csllHead && *csllHead) {
        CSLListNode *curr, *tmp;

        for (curr = (*csllHead)->nxt; curr != *csllHead;) {
            if (freeData)
                freeData(curr->pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        free(*csllHead);
        *csllHead = NULL;
    }
}
