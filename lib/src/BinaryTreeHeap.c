 /********************
 *  BinaryTreeHeap.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "HeapAllocation.h"
#include "BinaryTreeHeap.h"
#include "FIFOqueue.h" //for breadth-first
#include <math.h> //log2, floor



static void iter_insert(BTHeapNode *subtree, unsigned int total_nodes, BTHeapNode *new_node);
static void fix_push_max(BTHeapNode *curr, vdsUserCompareFunc DataCmp);
static void fix_push_min(BTHeapNode *curr, vdsUserCompareFunc DataCmp);
static BTHeapNode *breadth_first_get_last(BTHeap *btheap);
//static BTHeapNode *recur_get_last(BTHeapNode *subtree, unsigned int total_nodes);
static void fix_pop_max(BTHeapNode *curr, vdsUserCompareFunc DataCmp);
static void fix_pop_min(BTHeapNode *curr, vdsUserCompareFunc DataCmp);


BTHeap *BTHeap_init(vdsUserCompareFunc DataCmp,
                    vdsHeapProperty property,
                    vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    BTHeap *btheap = NULL;

    if (DataCmp) {

        switch (property) {
        case VDS_MAX_HEAP:
        case VDS_MIN_HEAP:
            btheap = VdsMalloc(sizeof(BTHeap));

            if (btheap) {
                btheap->property = property;
                btheap->root = NULL;
                btheap->total_nodes = 0;
                btheap->DataCmp = DataCmp;
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

    return btheap;
}

BTHeapNode *BTHeap_push(BTHeap *btheap,
                        void *pData,
                        vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    BTHeapNode *new_node = NULL;

    if (btheap && pData) {

        new_node = VdsMalloc(sizeof(BTHeapNode));

        if (new_node) {

            new_node->pData = pData;
            new_node->right = new_node->left = NULL;

            if (!btheap->root) {
                new_node->parent = NULL;
                btheap->root = new_node;
                btheap->total_nodes = 1;
            } else {

                iter_insert(btheap->root, btheap->total_nodes, new_node);
                btheap->total_nodes++;

                switch (btheap->property) {
                case VDS_MAX_HEAP:
                    fix_push_max(new_node, btheap->DataCmp);
                    break;
                case VDS_MIN_HEAP:
                    fix_push_min(new_node, btheap->DataCmp);
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

void fix_push_max(BTHeapNode *curr, vdsUserCompareFunc DataCmp)
{
    int cmp_res;
    void *pTmp;

    while (curr->parent) {
        cmp_res = DataCmp(curr->pData, curr->parent->pData);

        if (cmp_res > 0) {
            pTmp = curr->pData;
            curr->pData = curr->parent->pData;
            curr->parent->pData = pTmp;
            curr = curr->parent;
        } else
            break;
    }
}

void fix_push_min(BTHeapNode *curr, vdsUserCompareFunc DataCmp)
{
    int cmp_res;
    void *pTmp;

    while (curr->parent) {
        cmp_res = DataCmp(curr->pData, curr->parent->pData);

        if (cmp_res < 0) {
            pTmp = curr->pData;
            curr->pData = curr->parent->pData;
            curr->parent->pData = pTmp;
            curr = curr->parent;
        } else
            break;
    }
}

/* my algorithm that locates the inserts a new node in a complete binary tree, in a way
 * that maintains the tree's completeness */
/* TODO: add description of how it works */
void iter_insert(BTHeapNode *subtree, unsigned int total_nodes, BTHeapNode *new_node)
{
    unsigned int depth, two_to_depth, last_node_left_subtree;

    while (total_nodes > 2) {
        depth = (unsigned int)floor(log2(total_nodes));

        two_to_depth = (unsigned int)pow(2, depth);

        last_node_left_subtree = two_to_depth + (unsigned int)pow(2, depth - 1) - 1;

        if (total_nodes < last_node_left_subtree) {

            total_nodes = total_nodes - (two_to_depth / 2);
            subtree = subtree->left;

        } else if (!( (total_nodes + 1) & (total_nodes) )) {

            total_nodes = total_nodes - two_to_depth;
            subtree = subtree->left;

        } else {

            total_nodes = total_nodes - two_to_depth;
            subtree = subtree->right;

        }
    }

    new_node->parent = subtree;

    if (!subtree->left)
        subtree->left = new_node;
    else
        subtree->right = new_node;
}

void *BTHeap_pop(BTHeap *btheap,
                 vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    void *pDeleted = NULL;

    if (btheap && btheap->root) {
        //save the data of the deleted node
        pDeleted = btheap->root->pData;

        //if there's only one node on the tree
        if (!btheap->root->left && !btheap->root->right) {

            VdsFree(btheap->root);
            btheap->root = NULL;

        } else {

            BTHeapNode *last_node = breadth_first_get_last(btheap);
            if (last_node) {

                void *pTmp = last_node->pData;
                last_node->pData = btheap->root->pData;
                btheap->root->pData = pTmp;

                //don't forget to NULL the parent of the last node (the node
                //that will be technically deleted)
                //if the last node is a left node
                if (last_node->parent->left == last_node)
                    last_node->parent->left = NULL;
                else
                    last_node->parent->right = NULL;

                VdsFree(last_node);

                //restore the property of the heap
                switch (btheap->property) {
                case VDS_MAX_HEAP:
                    fix_pop_max(btheap->root, btheap->DataCmp);
                    break;
                case VDS_MIN_HEAP:
                    fix_pop_min(btheap->root, btheap->DataCmp);
                    break;
                default:
                    tmp_err = VDS_INVALID_ARGS;
                    break;
                }

            } else
                tmp_err = VDS_MALLOC_FAIL;

        }

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pDeleted;
}

void fix_pop_max(BTHeapNode *curr, vdsUserCompareFunc DataCmp)
{
    int cmp_res;
    void *pTmp;

    //while the current node isn't a leaf node
    while (curr->left) {

        //if it has two children
        if (curr->right) {
            //compare them to get the max/min
            cmp_res = DataCmp(curr->left->pData, curr->right->pData);

            //if the left node is bigger than or equal to the right node
            if (cmp_res >= 0) {
                //compare the current node with the left child
                cmp_res = DataCmp(curr->left->pData, curr->pData);

                //if the child is bigger than the father, we swap the nodes to maintain max heap property
                if (cmp_res > 0) {
                    pTmp = curr->pData;
                    curr->pData = curr->left->pData;
                    curr->left->pData = pTmp;
                    curr = curr->left;
                } else
                    break; //there's no need to keep going

            //else if the right node is bigger than the left node
            } else {
                //compare the current node with the left child (the bigger one of the two)
                cmp_res = DataCmp(curr->right->pData, curr->pData);

                //if the child is bigger than the father, we swap the nodes to maintain max heap property
                if (cmp_res > 0) {
                    pTmp = curr->pData;
                    curr->pData = curr->right->pData;
                    curr->right->pData = pTmp;
                    curr = curr->right;
                } else
                    break;
            }

        //if it has just one left child
        } else {
            //compare the parent and the child
            cmp_res = DataCmp(curr->left->pData, curr->pData);

            //if the child is bigger we swap them and continue doing the same
            //from the child, until we hit a leaf node
            if (cmp_res > 0) {
                pTmp = curr->pData;
                curr->pData = curr->left->pData;
                curr->left->pData = pTmp;
                curr = curr->left;
            } else
                break;
        }

    }
}

void fix_pop_min(BTHeapNode *curr, vdsUserCompareFunc DataCmp)
{
    int cmp_res;
    void *pTmp;

    //while the current node isn't a leaf node
    while (curr->left) {

        //if it has two children
        if (curr->right) {
            //compare them to get the min
            cmp_res = DataCmp(curr->left->pData, curr->right->pData);

            //if the left node is smaller than or equal to the right node
            if (cmp_res <= 0) {
                //compare the current node with the left child
                cmp_res = DataCmp(curr->left->pData, curr->pData);

                //if the child is smaller than the father, we swap the nodes to maintain max heap property
                if (cmp_res < 0) {
                    pTmp = curr->pData;
                    curr->pData = curr->left->pData;
                    curr->left->pData = pTmp;
                    curr = curr->left;
                } else
                    break; //there's no need to keep going

            //else if the right node is smaller than the left node
            } else {
                //compare the current node with the left child (the smaller one of the two)
                cmp_res = DataCmp(curr->right->pData, curr->pData);

                //if the child is smaller than the father, we swap the nodes to maintain max heap property
                if (cmp_res < 0) {
                    pTmp = curr->pData;
                    curr->pData = curr->right->pData;
                    curr->right->pData = pTmp;
                    curr = curr->right;
                } else
                    break;
            }

        //if it has just one left child
        } else {
            //compare the parent and the child
            cmp_res = DataCmp(curr->left->pData, curr->pData);

            //if the child is smaller we swap them and continue doing the same
            //from the child, until we hit a leaf node
            if (cmp_res < 0) {
                pTmp = curr->pData;
                curr->pData = curr->left->pData;
                curr->left->pData = pTmp;
                curr = curr->left;
            } else
                break;
        }

    }
}
#if 0
BTHeapNode *recur_get_last(BTHeapNode *subtree, unsigned int total_nodes)
{
    if (total_nodes <= 4) {

        if (subtree->right)
            return subtree->right;

        if (subtree->left)
            return subtree->left;

        return subtree;
    }

    unsigned int depth, two_to_depth, last_node_left_subtree;


    depth = (unsigned int)floor(log2(total_nodes));

    two_to_depth = (unsigned int)pow(2, depth);

    last_node_left_subtree = two_to_depth + (unsigned int)pow(2, depth - 1) - 1;


    if (total_nodes < last_node_left_subtree)
        return recur_get_last(subtree->left, total_nodes - (two_to_depth / 2));

    if (!( (total_nodes + 1) & (total_nodes) ))
        return recur_get_last(subtree->left, total_nodes - two_to_depth);

    return recur_get_last(subtree->right, total_nodes - two_to_depth);
}
#endif
BTHeapNode *breadth_first_get_last(BTHeap *btheap)
{
    vdsErrCode err;
    BTHeapNode *curr = NULL;
    FIFOqueue *levelFIFO = FIFO_init(&err);

    if (levelFIFO) {
        FIFO_enqueue(levelFIFO, (void *)btheap->root, &err);

        if (err == VDS_SUCCESS) {

            do {
                curr = (BTHeapNode *)FIFO_dequeue(levelFIFO, NULL);

                if (curr->left) {
                    FIFO_enqueue(levelFIFO, curr->left, &err);

                    if (err != VDS_SUCCESS)
                        break;
                }

                if (curr->right) {
                    FIFO_enqueue(levelFIFO, curr->right, &err);

                    if (err != VDS_SUCCESS)
                        break;
                }

            } while (levelFIFO->total_nodes > 1);

            if (err == VDS_SUCCESS)
                curr = (BTHeapNode *)FIFO_dequeue(levelFIFO, NULL);

            FIFO_destroy(&levelFIFO, NULL, NULL);

        }

    }

    if (err == VDS_SUCCESS)
        return curr;

    return NULL;
}

void *BTHeap_replace(BTHeap *btheap,
                     void *pData,
                     vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    void *pDeleted = NULL;

    if (btheap && btheap->root && pData) {

        pDeleted = btheap->root->pData;
        btheap->root->pData = pData;

        switch (btheap->property) {
        case VDS_MAX_HEAP:
            fix_pop_max(btheap->root, btheap->DataCmp);
            break;
        case VDS_MIN_HEAP:
            fix_pop_min(btheap->root, btheap->DataCmp);
            break;
        default:
            tmp_err = VDS_INVALID_ARGS;
            break;
        }

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pDeleted;
}

void BTHeap_destroy(BTHeap **btheap,
                    vdsUserDataFunc freeData,
                    vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (btheap && *btheap) {

        BTHeapNode *curr = (*btheap)->root, *to_delete;

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

        VdsFree(*btheap);
        *btheap = NULL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
