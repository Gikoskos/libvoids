/***********************************************\
*               AssociationList.c               *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include "AssociationList.h"


DictListNode *DictList_insert(DictListNode **dictListHead, void *pData, void *pKey, UserCompareCallback KeyCmp)
{
    DictListNode *new_node = NULL;

    if (dictListHead) {

        //insert the new node ONLY if a node with the same key doesn't exist already in the list
        if (!DictList_findByKey(*dictListHead, pKey, KeyCmp)) {
            new_node = malloc(sizeof(DictListNode));

            new_node->item.pData = pData;
            new_node->item.pKey = pKey;
            new_node->nxt = *dictListHead;

            *dictListHead = new_node;
        }
    }

    return new_node;
}

DictListNode *DictList_append(DictListNode **dictListHead, void *pData, void *pKey, UserCompareCallback KeyCmp)
{
    DictListNode *new_node = NULL;

    if (dictListHead && !DictList_findByKey(*dictListHead, pKey, KeyCmp)) {
        new_node = malloc(sizeof(DictListNode));

        new_node->item.pData = pData;
        new_node->item.pKey = pKey;
        new_node->nxt = NULL;

        if (!(*dictListHead)) {
            *dictListHead = new_node;
        } else {
            DictListNode *curr;

            for (curr = *dictListHead; curr->nxt; curr = curr->nxt)
                if (!KeyCmp(curr->item.pKey, pKey)) { //if a node with the same key, already exists on the list
                    free(new_node);                  //we don't add it
                    new_node = NULL;
                    break;
                }

            curr->nxt = new_node;
        }
    }

    return new_node;
}

DictListNode *DictList_insertAfter(DictListNode *dictListPrev, void *pData, void *pKey)
{
    DictListNode *new_node = NULL;

    if (dictListPrev) {
        new_node = malloc(sizeof(DictListNode));

        new_node->item.pData = pData;
        new_node->item.pKey = pKey;
        new_node->nxt = dictListPrev->nxt;

        dictListPrev->nxt = new_node;
    }

    return new_node;
}

KeyValuePair DictList_deleteByKey(DictListNode **dictListHead, void *pKey, UserCompareCallback KeyCmp)
{
    KeyValuePair item = { 0 };

    if (dictListHead && KeyCmp) {
        DictListNode *curr, *prev = NULL;

        for (curr = *dictListHead; curr && KeyCmp(curr->item.pKey, pKey); curr = curr->nxt)
            prev = curr;

        if (curr) {
            item = curr->item;

            if (prev) {
                prev->nxt = curr->nxt;
            } else {
                *dictListHead = curr->nxt;
            }

            free(curr);
        }
    }

    return item;
}

DictListNode *DictList_findByKey(DictListNode *dictListHead, void *pKey, UserCompareCallback KeyCmp)
{
    DictListNode *curr = dictListHead;

    if (KeyCmp)
        for (; curr && KeyCmp(curr->item.pKey, pKey); curr = curr->nxt);

    return curr;
}

void DictList_traverse(DictListNode *dictListHead, UserDataCallback handleData)
{
    if (dictListHead && handleData)
        for (DictListNode *curr = dictListHead; curr; curr = curr->nxt)
            handleData((void *)&curr->item);
}

void DictList_destroy(DictListNode **dictListHead, UserDataCallback freeData)
{
    if (dictListHead) {
        DictListNode *curr, *tmp;

        for (curr = *dictListHead; curr;) {
            if (freeData)
                freeData((void *)&curr->item);

            tmp = curr;
            curr = curr->nxt;
            free(tmp);
        }

        *dictListHead = NULL;
    }
}
