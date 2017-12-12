 /********************
 *  AssociationList.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "MemoryAllocation.h"
#include "AssociationList.h"


DictListNode *DictList_insert(DictListNode **dictListHead,
                              void *pData,
                              void *pKey,
                              vdsUserCompareFunc KeyCmp,
                              vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DictListNode *new_node = NULL;

    if (dictListHead && pKey && KeyCmp) {

        //insert the new node ONLY if a node with the same key doesn't exist already in the list
        if (!(new_node = DictList_findByKey(*dictListHead, pKey, KeyCmp, NULL))) {
            new_node = VdsMalloc(sizeof(DictListNode));

            if (new_node) {

                new_node->item.pData = pData;
                new_node->item.pKey = pKey;
                new_node->nxt = *dictListHead;

                *dictListHead = new_node;

            } else
                tmp_err = VDS_MALLOC_FAIL;
        } else
            tmp_err = VDS_KEY_EXISTS;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

DictListNode *DictList_append(DictListNode **dictListHead,
                              void *pData,
                              void *pKey,
                              vdsUserCompareFunc KeyCmp,
                              vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DictListNode *new_node = NULL;

    if (dictListHead && pKey && KeyCmp) {

        new_node = VdsMalloc(sizeof(DictListNode));

        if (new_node) {

            new_node->item.pData = pData;
            new_node->item.pKey = pKey;
            new_node->nxt = NULL;

            if (!(*dictListHead)) {
                *dictListHead = new_node;
            } else {
                DictListNode *curr;

                for (curr = *dictListHead; curr->nxt; curr = curr->nxt)
                    if (!KeyCmp(curr->item.pKey, pKey)) { //if a node with the same key, already exists on the list
                        VdsFree(new_node);                  //we don't add it
                        new_node = curr;
                        tmp_err = VDS_KEY_EXISTS;
                        break;
                    }

                curr->nxt = new_node;
            }
        } else
            tmp_err = VDS_MALLOC_FAIL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

DictListNode *DictList_insertAfter(DictListNode *dictListPrev,
                                   void *pData,
                                   void *pKey,
                                   vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DictListNode *new_node = NULL;

    if (dictListPrev && pKey) {
        new_node = VdsMalloc(sizeof(DictListNode));

        if (new_node) {

            new_node->item.pData = pData;
            new_node->item.pKey = pKey;
            new_node->nxt = dictListPrev->nxt;

            dictListPrev->nxt = new_node;

        } else
            tmp_err = VDS_MALLOC_FAIL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

KeyValuePair DictList_deleteByKey(DictListNode **dictListHead,
                                  void *pKey,
                                  vdsUserCompareFunc KeyCmp,
                                  vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_INVALID_ARGS;
    KeyValuePair item = { 0 };

    if (dictListHead && KeyCmp && pKey) {
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

            VdsFree(curr);
            tmp_err = VDS_SUCCESS;
        }
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return item;
}

DictListNode *DictList_findByKey(DictListNode *dictListHead,
                                 void *pKey,
                                 vdsUserCompareFunc KeyCmp,
                                 vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    DictListNode *curr = dictListHead;

    if (KeyCmp && pKey)
        for (; curr && KeyCmp(curr->item.pKey, pKey); curr = curr->nxt);
    else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

void DictList_traverse(DictListNode *dictListHead,
                       vdsUserDataFunc handleData,
                       vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (dictListHead && handleData)
        for (DictListNode *curr = dictListHead; curr; curr = curr->nxt)
            handleData((void *)&curr->item);
    else
        tmp_err = VDS_INVALID_ARGS;


    SAVE_ERR(err, tmp_err);
}

void DictList_destroy(DictListNode **dictListHead,
                      vdsUserDataFunc freeData,
                      vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (dictListHead) {
        DictListNode *curr, *tmp;

        for (curr = *dictListHead; curr;) {
            if (freeData)
                freeData((void *)&curr->item);

            tmp = curr;
            curr = curr->nxt;
            VdsFree(tmp);
        }

        *dictListHead = NULL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
