 /********************
 *  ArrayHeap.c
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include <stdlib.h>
#include "ArrayHeap.h"



ArrayHeap *ArrayHeap_init(UserCompareCallback DataCmp,
                          HeapPropertyType property,
                          size_t size,
                          EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    ArrayHeap *arrheap = NULL;

    if (DataCmp && size > 0) {

        switch (property) {
        case EDS_MAX_HEAP:
        case EDS_MIN_HEAP:
            arrheap = malloc(sizeof(ArrayHeap));

            if (arrheap) {

                arrheap->array = malloc(sizeof(void*) * size);

                if (arrheap->array) {

                    arrheap->property = property;
                    arrheap->DataCmp = DataCmp;
                    arrheap->size = size;
                    arrheap->idx = 0;

                } else
                    tmp_err = EDS_MALLOC_FAIL;

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

    return arrheap;
}

void *ArrayHeap_push(ArrayHeap *arrheap,
                     void *pData,
                     EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    void *pRet = NULL;

    if (arrheap && pData && arrheap->idx < arrheap->) {

        pRet = pData;

        switch (bheap->property) {
        case EDS_MAX_HEAP:
            heapify_max(new_node, bheap->DataCmp);
            break;
        case EDS_MIN_HEAP:
            fix_push_min(new_node, bheap->DataCmp);
            break;
        default:
            tmp_err = EDS_INVALID_ARGS;
            break;
        }

    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pRet;
}

void heapify_max(ArrayHeap *heap, void *pData)
{
    
}

void fix_push_max(BinaryHeapNode *curr, UserCompareCallback DataCmp)
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

void fix_push_min(BinaryHeapNode *curr, UserCompareCallback DataCmp)
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

int breadth_first_insert(BinaryHeap *bheap, BinaryHeapNode *new_node)
{
    EdsErrCode err;
    BinaryHeapNode *curr;
    FIFOqueue *levelFIFO = FIFO_init(&err);

    if (levelFIFO) {
        FIFO_enqueue(levelFIFO, (void *)bheap->root, &err);

        if (err == EDS_SUCCESS) {

            while (levelFIFO->total_nodes) {
                curr = (BinaryHeapNode *)FIFO_dequeue(levelFIFO, NULL);

                if (curr->left) {
                    FIFO_enqueue(levelFIFO, curr->left, &err);

                    if (err != EDS_SUCCESS)
                        break;
                } else {
                    new_node->parent = curr;
                    curr->left = new_node;
                    break;
                }

                if (curr->right) {
                    FIFO_enqueue(levelFIFO, curr->right, &err);

                    if (err != EDS_SUCCESS)
                        break;
                } else {
                    new_node->parent = curr;
                    curr->right = new_node;
                    break;
                }
            }

            FIFO_destroy(&levelFIFO, NULL, NULL);

        }

    }

    if (err == EDS_SUCCESS)
        return 1;

    return 0;
}

void *ArrayHeap_pop(ArrayHeap *arrheap,
                    EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    void *pDeleted = NULL;

    if (bheap && bheap->root) {
        //save the data of the deleted node
        pDeleted = bheap->root->pData;

        //if there's only one node on the tree
        if (!bheap->root->left && !bheap->root->right) {

            free(bheap->root);
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

                free(last_node);

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

void fix_pop_max(BinaryHeapNode *curr, UserCompareCallback DataCmp)
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

void fix_pop_min(BinaryHeapNode *curr, UserCompareCallback DataCmp)
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

BinaryHeapNode *breadth_first_get_last(BinaryHeap *bheap)
{
    EdsErrCode err;
    BinaryHeapNode *curr = NULL;
    FIFOqueue *levelFIFO = FIFO_init(&err);

    if (levelFIFO) {
        FIFO_enqueue(levelFIFO, (void *)bheap->root, &err);

        if (err == EDS_SUCCESS) {

            do {
                curr = (BinaryHeapNode *)FIFO_dequeue(levelFIFO, NULL);

                if (curr->left) {
                    FIFO_enqueue(levelFIFO, curr->left, &err);

                    if (err != EDS_SUCCESS)
                        break;
                }

                if (curr->right) {
                    FIFO_enqueue(levelFIFO, curr->right, &err);

                    if (err != EDS_SUCCESS)
                        break;
                }

            } while (levelFIFO->total_nodes > 1);

            if (err == EDS_SUCCESS)
                curr = (BinaryHeapNode *)FIFO_dequeue(levelFIFO, NULL);

            FIFO_destroy(&levelFIFO, NULL, NULL);

        }

    }

    if (err == EDS_SUCCESS)
        return curr;

    return NULL;
}

void *ArrayHeap_replace(ArrayHeap *arrheap,
                        void *pData,
                        EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    void *pDeleted = NULL;

    if (bheap && bheap->root && pData) {

        pDeleted = bheap->root->pData;
        bheap->root->pData = pData;
        
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
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pDeleted;
}

void ArrayHeap_destroy(ArrayHeap *arrheap,
                       UserDataCallback freeData,
                       EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;

    if (bheap && *bheap) {

        BinaryHeapNode *curr = (*bheap)->root, *to_delete;

        //basically my iterative version of post-property
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
                        free(curr->right);
                        curr->right = NULL;
                    } else {
                        free(curr->left);
                        curr->left = NULL;
                    }

                } else { //if curr is NULL, it means that to_delete holds the root node
                    free(to_delete);
                }
            }
        }

        free(*bheap);
        *bheap = NULL;
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
