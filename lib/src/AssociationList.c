/***********************************************\
*               AssociationList.c               *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include "AssociationList.h"


DictListNode *DictList_insert(DictListNode **dictListHead, void *pData, key_type key)
{
    DictListNode *new_node = NULL;

    if (dictListHead) {

        //insert the new node ONLY if a node with the same key doesn't exist already in the list
        if (!DictList_findByKey(*dictListHead, key)) {
            new_node = malloc(sizeof(DictListNode));

            new_node->item.pData = pData;
            new_node->item.key = key;
            new_node->nxt = *dictListHead;

            *dictListHead = new_node;
        }
    }

    return new_node;
}

DictListNode *DictList_append(DictListNode **dictListHead, void *pData, key_type key)
{
    DictListNode *new_node = NULL;

    if (dictListHead) {
        new_node = malloc(sizeof(DictListNode));

        new_node->item.pData = pData;
        new_node->item.key = key;
        new_node->nxt = NULL;

        if (!(*dictListHead)) {
            *dictListHead = new_node;
        } else {
            DictListNode *curr;

            for (curr = *dictListHead; curr->nxt; curr = curr->nxt);

            curr->nxt = new_node;
        }
    }

    return new_node;
}

DictListNode *DictList_insertAfter(DictListNode *sllPrev, void *pData, key_type key)
{
    DictListNode *new_node = NULL;

    if (sllPrev) {
        new_node = malloc(sizeof(DictListNode));

        new_node->item.pData = pData;
        new_node->item.key = key;
        new_node->nxt = sllPrev->nxt;

        sllPrev->nxt = new_node;
    }

    return new_node;
}

void *DictList_deleteByKey(DictListNode **dictListHead, key_type key)
{
    void *pRet = NULL;

    if (dictListHead) {
        DictListNode *curr, *prev = NULL;

        for (curr = *dictListHead; curr && (curr->item.key != key); curr = curr->nxt)
            prev = curr;

        if (curr) {
            pRet = curr->item.pData;

            if (prev) {
                prev->nxt = curr->nxt;
            } else {
                *dictListHead = curr->nxt;
            }

            free(curr);
        }
    }

    return pRet;
}

DictListNode *DictList_findByKey(DictListNode *dictListHead, key_type key)
{
    DictListNode *curr;

    for (curr = dictListHead; curr && (curr->item.key != key); curr = curr->nxt);

    return curr;
}

void DictList_traverse(DictListNode *dictListHead, CustomDataCallback handleData)
{
    if (dictListHead && handleData)
        for (DictListNode *curr = dictListHead; curr; curr = curr->nxt)
            handleData((void *)&curr->item);
}

void DictList_destroy(DictListNode **dictListHead, CustomDataCallback freeData)
{
    if (dictListHead) {
        DictListNode *curr, *tmp;

        for (curr = *dictListHead; curr;) {
            if (freeData)
                freeData(curr->item.pData);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        *dictListHead = NULL;
    }
}
