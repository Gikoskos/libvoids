 /********************
 *  LeftistHeap.c
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "MemoryAllocation.h"
#include "LeftistHeap.h"
/*

static LeftistHeap *merge_heaps_max(LeftistHeap *lheap1, LeftistHeapNode *lheap2_root);
static LeftistHeap *merge_heaps_min(LeftistHeap *lheap1, LeftistHeapNode *lheap2_root);


LeftistHeap *LeftistHeap_init(UserCompareCallback DataCmp,
                              HeapPropertyType property,
                              EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    LeftistHeap *lheap = NULL;

    if (DataCmp) {

        switch (property) {
        case EDS_MAX_HEAP:
        case EDS_MIN_HEAP:
            lheap = EdsMalloc(sizeof(LeftistHeap));

            if (lheap) {
                lheap->property = property;
                lheap->root = NULL;
                lheap->DataCmp = DataCmp;
            } else
                tmp_err = EDS_MALLOC_FAIL;
            break;
        default:
            tmp_err = EDS_INVALID_ARGS;
            break;
        }

    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return lheap;
}

LeftistHeapNode *LeftistHeap_push(LeftistHeap *lheap,
                                  void *pData,
                                  EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    LeftistHeapNode *new_node = NULL;

    if (lheap && pData) {

        new_node = EdsMalloc(sizeof(LeftistHeapNode));

        if (new_node) {

            new_node->pData = pData;
            new_node->right = new_node->left = NULL;
            new_node->npl = 1;

            if (!lheap->root) {
                new_node->parent = NULL;
                lheap->root = new_node;
            } else {

                switch (lheap->property) {
                case EDS_MAX_HEAP:
                    merge_heaps_max(lheap, new_node);
                    break;
                case EDS_MIN_HEAP:
                    merge_heaps_min(lheap, new_node);
                    break;
                default:
                    tmp_err = EDS_INVALID_ARGS;
                    break;
                }

            }

        } else
            tmp_err = EDS_MALLOC_FAIL;

    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

unsigned int null_path_length(LeftistHeapNode *lheapnode)
{
    if (lheapnode)
        return lheapnode->npl;

    return 0;
}

LeftistHeap *merge_heaps_max(LeftistHeap *lheap1, LeftistHeapNode *lheap2_root)
{
    //handle edge cases
    if (!lheap1->root)
        return lheap2_root;

    if (!lheap2_root)
        return curr;

    LeftistHeapNode curr = lheap1->root;
    int cmp_res;

    while (1) {

        cmp_res = lheap1->DataCmp(curr->pData, lheap2_root->pData);

        if (cmp_res > 0) {
            
        }

    }
}

LeftistHeap *merge_heaps_min(LeftistHeap *lheap1, LeftistHeapNode *lheap2_root)
{
    
}

void *LeftistHeap_pop(LeftistHeap *lheap,
                      EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    void *pDeleted = NULL;

    if (bheap && bheap->root) {
        //save the data of the deleted node
        pDeleted = bheap->root->pData;

        //if there's only one node on the tree
        if (!bheap->root->left && !bheap->root->right) {

            EdsFree(bheap->root);
            bheap->root = NULL;

        } else {

            BinaryHeapNode *last_node = breadth_first_get_last(bheap);
            if (last_node) {

                void *pTmp = last_node->pData;
                last_node->pData = bheap->root->pData;
                bheap->root->pData = pTmp;

                //don't forget to NULL the parent of the last node (the node
                //that will be technically deleted)
                //if the last node is a left node
                if (last_node->parent->left == last_node)
                    last_node->parent->left = NULL;
                else
                    last_node->parent->right = NULL;

                EdsFree(last_node);

                //restore the property of the heap
                switch (bheap->property) {
                case EDS_MAX_HEAP:
                    fix_pop_max(bheap->root, bheap->DataCmp);
                    break;
                case EDS_MIN_HEAP:
                    fix_pop_min(bheap->root, bheap->DataCmp);
                    break;
                default:
                    tmp_err = EDS_INVALID_ARGS;
                    break;
                }

            } else
                tmp_err = EDS_MALLOC_FAIL;

        }

    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pDeleted;
}

void LeftistHeap_destroy(LeftistHeap **lheap,
                         UserDataCallback freeData,
                         EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;

    if (lheap && *lheap) {

        BinaryHeapNode *curr = (*lheap)->root, *to_delete;

        //iterative version of post-order
        while (curr) {
            if (curr->left) {

                curr = curr->left;

            } else if (curr->right) {

                curr = curr->right;

            } else {

                //if we're here we want to delete AND NULL the to_delete node
                to_delete = curr;
                //we make curr the parent
                curr = curr->parent;

                if (freeData)
                    freeData(to_delete->pData);

                if (curr) {

                    if (curr->right == to_delete) {
                        EdsFree(curr->right);
                        curr->right = NULL;
                    } else {
                        EdsFree(curr->left);
                        curr->left = NULL;
                    }

                } else { //if curr is NULL, it means that to_delete holds the root node
                    EdsFree(to_delete);
                }
            }
        }

        EdsFree(*lheap);
        *lheap = NULL;
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
*/
