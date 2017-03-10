/***********************************************\
*                  BinaryHeap.c                 *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include "BinaryHeap.h"
#include "FIFOqueue.h" //for breadth-first

#define isLeafNode(x) ( !(x->right || x->left) )


static int breadth_first_insert(BinaryHeap *bheap, BinaryHeapNode *new_node);
static void fix_push_max(BinaryHeapNode *curr, UserCompareCallback DataCmp);
static void fix_push_min(BinaryHeapNode *curr, UserCompareCallback DataCmp);
static BinaryHeapNode *breadth_first_get_last(BinaryHeap *bheap);
static void fix_pop_max(BinaryHeapNode *curr, UserCompareCallback DataCmp);
static void fix_pop_min(BinaryHeapNode *curr, UserCompareCallback DataCmp);


BinaryHeap *BinaryHeap_init(UserCompareCallback DataCmp,
                            HeapType type,
                            EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    BinaryHeap *bheap = NULL;

    if (DataCmp) {

        switch (type) {
        case MAX_ORDER_HEAP:
        case MIN_ORDER_HEAP:
            bheap = malloc(sizeof(BinaryHeap));

            if (bheap) {
                bheap->type = type;
                bheap->root = NULL;
                bheap->DataCmp = DataCmp;
            } else
                tmp_err = EduDS_MALLOC_FAIL;
            break;
        default:
            tmp_err = EduDS_INVALID_ARGS;
            break;
        }

    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return bheap;
}

BinaryHeapNode *BinaryHeap_push(BinaryHeap *bheap,
                                void *pData,
                                EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    BinaryHeapNode *new_node = NULL;

    if (bheap && pData) {

        new_node = malloc(sizeof(BinaryHeapNode));

        if (new_node) {

            new_node->pData = pData;
            new_node->right = new_node->left = NULL;

            if (!bheap->root) {
                new_node->parent = NULL;
                bheap->root = new_node;
            } else {

                if (breadth_first_insert(bheap, new_node)) {

                    switch (bheap->type) {
                    case MAX_ORDER_HEAP:
                        fix_push_max(new_node, bheap->DataCmp);
                        break;
                    case MIN_ORDER_HEAP:
                        fix_push_min(new_node, bheap->DataCmp);
                        break;
                    default:
                        tmp_err = EduDS_INVALID_ARGS;
                        break;
                    }

                } else {
                    free(new_node);
                    tmp_err = EduDS_MALLOC_FAIL;
                }
            }

        } else
            tmp_err = EduDS_MALLOC_FAIL;

    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
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
    EduDSErrCode err;
    BinaryHeapNode *curr;
    FIFOqueue *levelFIFO = FIFO_init(&err);

    if (levelFIFO) {
        FIFO_enqueue(levelFIFO, (void *)bheap->root, &err);

        if (err == EduDS_SUCCESS) {

            while (levelFIFO->total_nodes) {
                curr = (BinaryHeapNode *)FIFO_dequeue(levelFIFO, NULL);

                if (curr->left) {
                    FIFO_enqueue(levelFIFO, curr->left, &err);

                    if (err != EduDS_SUCCESS)
                        break;
                } else {
                    new_node->parent = curr;
                    curr->left = new_node;
                    break;
                }

                if (curr->right) {
                    FIFO_enqueue(levelFIFO, curr->right, &err);

                    if (err != EduDS_SUCCESS)
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

    if (err == EduDS_SUCCESS)
        return 1;

    return 0;
}

void *BinaryHeap_pop(BinaryHeap *bheap,
                     EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
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

                //restore the order of the heap
                switch (bheap->type) {
                case MAX_ORDER_HEAP:
                    fix_pop_max(bheap->root, bheap->DataCmp);
                    break;
                case MIN_ORDER_HEAP:
                    fix_pop_min(bheap->root, bheap->DataCmp);
                    break;
                default:
                    tmp_err = EduDS_INVALID_ARGS;
                    break;
                }

            } else
                tmp_err = EduDS_MALLOC_FAIL;

        }

    } else
        tmp_err = EduDS_INVALID_ARGS;

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

                //if the child is bigger than the father, we swap the nodes to maintain max heap order
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

                //if the child is bigger than the father, we swap the nodes to maintain max heap order
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

                //if the child is smaller than the father, we swap the nodes to maintain max heap order
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

                //if the child is smaller than the father, we swap the nodes to maintain max heap order
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
    EduDSErrCode err;
    BinaryHeapNode *curr;
    FIFOqueue *levelFIFO = FIFO_init(&err);

    if (levelFIFO) {
        FIFO_enqueue(levelFIFO, (void *)bheap->root, &err);

        if (err == EduDS_SUCCESS) {

            do {
                curr = (BinaryHeapNode *)FIFO_dequeue(levelFIFO, NULL);

                if (curr->left) {
                    FIFO_enqueue(levelFIFO, curr->left, &err);

                    if (err != EduDS_SUCCESS)
                        break;
                }

                if (curr->right) {
                    FIFO_enqueue(levelFIFO, curr->right, &err);

                    if (err != EduDS_SUCCESS)
                        break;
                }

            } while (levelFIFO->total_nodes > 1);

            if (err == EduDS_SUCCESS)
                curr = (BinaryHeapNode *)FIFO_dequeue(levelFIFO, NULL);

            FIFO_destroy(&levelFIFO, NULL, NULL);

        }

    }

    if (err == EduDS_SUCCESS)
        return curr;

    return NULL;
}

void *BinaryHeap_replace(BinaryHeap *bheap,
                         void *pData,
                         EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;
    void *pDeleted = NULL;

    if (bheap && bheap->root && pData) {

        pDeleted = bheap->root->pData;
        bheap->root->pData = pData;
        
        switch (bheap->type) {
        case MAX_ORDER_HEAP:
            fix_pop_max(bheap->root, bheap->DataCmp);
            break;
        case MIN_ORDER_HEAP:
            fix_pop_min(bheap->root, bheap->DataCmp);
            break;
        default:
            tmp_err = EduDS_INVALID_ARGS;
            break;
        }

    } else
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pDeleted;
}

void BinaryHeap_destroy(BinaryHeap **bheap,
                        UserDataCallback freeData,
                        EduDSErrCode *err)
{
    EduDSErrCode tmp_err = EduDS_SUCCESS;

    if (bheap && *bheap) {

        BinaryHeapNode *curr = (*bheap)->root, *to_delete;

        //basically my iterative version of post-order
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
        tmp_err = EduDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
