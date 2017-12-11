 /********************
 *  LeftistHeap.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "MemoryAllocation.h"
#include "LeftistHeap.h"

#define isLeafNode(x)      ( (x)->item.pKey == NULL )
#define isLeftNode(x)      ( (x) == (x)->parent->left )
#define nullPathLength(x)  ( (x) ? (x)->npl : 0 )

static void merge_heaps_max(LeftistHeap *lheap1, LeftistHeapNode *lheap2_root);
static void merge_heaps_min(LeftistHeap *lheap1, LeftistHeapNode *lheap2_root);


LeftistHeap *LeftistHeap_init(vdsUserCompareFunc DataCmp,
                              vdsHeapProperty property,
                              vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    LeftistHeap *lheap = NULL;

    if (DataCmp) {

        switch (property) {
        case VDS_MAX_HEAP:
        case VDS_MIN_HEAP:
            lheap = VdsMalloc(sizeof(LeftistHeap));

            if (lheap) {
                lheap->property = property;
                lheap->root = NULL;
                lheap->DataCmp = DataCmp;
            } else
                tmp_err = VDS_MALLOC_FAIL;
            break;
        default:
            tmp_err = VDS_INVALID_ARGS;
            break;
        }

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return lheap;
}

LeftistHeapNode *LeftistHeap_push(LeftistHeap *lheap,
                                  void *pData,
                                  vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    LeftistHeapNode *new_node = NULL;

    if (lheap && pData) {

        new_node = VdsMalloc(sizeof(LeftistHeapNode));

        if (new_node) {

            new_node->pData = pData;
            new_node->parent = new_node->right = new_node->left = NULL;
            new_node->npl = 1;

            if (!lheap->root) {
                new_node->parent = NULL;
                lheap->root = new_node;
            } else {

                switch (lheap->property) {
                case VDS_MAX_HEAP:
                    merge_heaps_max(lheap, new_node);
                    break;
                case VDS_MIN_HEAP:
                    merge_heaps_min(lheap, new_node);
                    break;
                default:
                    tmp_err = VDS_INVALID_ARGS;
                    break;
                }

            }

        } else
            tmp_err = VDS_MALLOC_FAIL;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

void merge_heaps_max(LeftistHeap *lheap1, LeftistHeapNode *lheap2_root)
{
    if (!lheap2_root) {
        return;
    } else if (!lheap1->root) {
        lheap1->root = lheap2_root;
        return;
    }

    LeftistHeapNode *curr1 = lheap1->root, *curr2 = lheap2_root, *tmp, *final_heap_root = NULL;
    int cmp_res;

    while (curr2) {

        cmp_res = lheap1->DataCmp(curr1->pData, curr2->pData);

        if (cmp_res > 0) {
            tmp = curr1->right;

            if (tmp) {
                tmp->parent = NULL;
            }

            //@FIXME: this check should only happen once before the loop
            if (!curr1->parent) {
                final_heap_root = curr1;
            }

            curr2->parent = curr1;
            curr1->right = curr2;

            curr1 = curr1->right;
        } else {
            tmp = curr2->right;

            if (tmp) {
                tmp->parent = NULL;
            }

            if (curr1->parent) {
                curr1->parent->right = curr2;
            } else {
                final_heap_root = curr2;
            }

            curr1->parent = curr2;
            curr2->right = curr1;

        }

        curr2 = tmp;
    }

    curr1 = curr1->parent;
    unsigned int npl_r, npl_l;

    while (curr1) {

        npl_r = nullPathLength(curr1->right);
        npl_l = nullPathLength(curr1->left);

        if (npl_r > npl_l) {
            tmp = curr1->right;
            curr1->right = curr1->left;
            curr1->left = tmp;
        }

        curr1->npl = (curr1->right) ? (curr1->right->npl + 1) : 1;

        curr1 = curr1->parent;
    }

    lheap1->root = final_heap_root;
}

void merge_heaps_min(LeftistHeap *lheap1, LeftistHeapNode *lheap2_root)
{
    if (!lheap2_root) {
        return;
    } else if (!lheap1->root) {
        lheap1->root = lheap2_root;
        return;
    }

    LeftistHeapNode *curr1 = lheap1->root, *curr2 = lheap2_root, *tmp, *final_heap_root = NULL;
    int cmp_res;

    while (curr2) {

        cmp_res = lheap1->DataCmp(curr1->pData, curr2->pData);

        if (cmp_res < 0) {
            tmp = curr1->right;

            if (tmp) {
                tmp->parent = NULL;
            }

            //@FIXME: this check should only happen once before the loop
            if (!curr1->parent) {
                final_heap_root = curr1;
            }

            curr2->parent = curr1;
            curr1->right = curr2;

            curr1 = curr1->right;
        } else {
            tmp = curr2->right;

            if (tmp) {
                tmp->parent = NULL;
            }

            if (curr1->parent) {
                curr1->parent->right = curr2;
            } else {
                final_heap_root = curr2;
            }

            curr1->parent = curr2;
            curr2->right = curr1;

        }

        curr2 = tmp;
    }

    curr1 = curr1->parent;
    unsigned int npl_r, npl_l;

    while (curr1) {

        npl_r = nullPathLength(curr1->right);
        npl_l = nullPathLength(curr1->left);

        if (npl_r > npl_l) {
            tmp = curr1->right;
            curr1->right = curr1->left;
            curr1->left = tmp;
        }

        curr1->npl = (curr1->right) ? (curr1->right->npl + 1) : 1;
        curr1 = curr1->parent;
    }

    lheap1->root = final_heap_root;
}

void *LeftistHeap_pop(LeftistHeap *lheap,
                      vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    void *pDeleted = NULL;

    if (lheap && lheap->root) {
        //save the data of the deleted node
        pDeleted = lheap->root->pData;

        //if there's only one node on the tree
        if (!lheap->root->left && !lheap->root->right) {

            VdsFree(lheap->root);
            lheap->root = NULL;

        } else {

            LeftistHeapNode *right_heap = lheap->root->right, *tmp = lheap->root;

            lheap->root = lheap->root->left;
            if (right_heap)
                right_heap->parent = NULL;
            if (lheap->root)
                lheap->root->parent = NULL;

            VdsFree(tmp);

            //merge the two subtrees
            switch (lheap->property) {
            case VDS_MAX_HEAP:
                merge_heaps_max(lheap, right_heap);
                break;
            case VDS_MIN_HEAP:
                merge_heaps_min(lheap, right_heap);
                break;
            default:
                tmp_err = VDS_INVALID_ARGS;
                break;
            }

        }

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pDeleted;
}

void LeftistHeap_destroy(LeftistHeap **lheap,
                         vdsUserDataFunc freeData,
                         vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (lheap && *lheap) {

        LeftistHeapNode *curr = (*lheap)->root, *to_delete;

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
                        VdsFree(curr->right);
                        curr->right = NULL;
                    } else {
                        VdsFree(curr->left);
                        curr->left = NULL;
                    }

                } else { //if curr is NULL, it means that to_delete holds the root node
                    VdsFree(to_delete);
                }
            }
        }

        VdsFree(*lheap);
        *lheap = NULL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
