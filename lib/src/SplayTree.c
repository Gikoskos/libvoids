 /********************
 *  SplayTree.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015-2018 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "HeapAllocation.h"
#include "SplayTree.h"

#define isLeafNode(x) ( !((x)->right || (x)->left) )
#define isLeftNode(x) ( (x) == (x)->parent->left )

#define RotateRight(x, y) \
    do { \
        if ((x)->right) \
            (x)->right->parent = y; \
\
        (y)->left = (x)->right; \
        (x)->right = y; \
        (x)->parent = (y)->parent; \
\
        if ((y)->parent) { \
            if (y == (y)->parent->left) \
                (y)->parent->left = x; \
            else \
                (y)->parent->right = x; \
        } \
\
        (y)->parent = x; \
    } while (0)

#define RotateLeft(x, y) \
    do { \
        if ((x)->left) \
            (x)->left->parent = y; \
\
        (y)->right = (x)->left; \
        (x)->left = y; \
        (x)->parent = (y)->parent; \
\
        if ((y)->parent) { \
            if (y == (y)->parent->left) \
                (y)->parent->left = x; \
            else \
                (y)->parent->right = x; \
        } \
\
        (y)->parent = x; \
    } while (0)

static void pre_orderTraversal(SplayTreeNode *sptNode, vdsUserDataFunc callback);
static void in_orderTraversal(SplayTreeNode *sptNode, vdsUserDataFunc callback);
static void post_orderTraversal(SplayTreeNode *sptNode, vdsUserDataFunc callback);
static int breadth_firstTraversal(SplayTreeNode *sptRoot, vdsUserDataFunc callback);
static void eulerTraversal(SplayTreeNode *sptNode, vdsUserDataFunc callback);

static void splay(SplayTreeNode *sptNode);


SplayTree *SplayTree_init(vdsUserCompareFunc KeyCmp,
                          vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    SplayTree *spt = NULL;

    if (KeyCmp) {
        spt = VdsMalloc(sizeof(SplayTree));

        if (spt) {
            spt->root = NULL;
            spt->KeyCmp = KeyCmp;
        } else
            tmp_err = VDS_MALLOC_FAIL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return spt;
}

SplayTreeNode *SplayTree_insert(SplayTree *spt,
                                void *pData,
                                void *pKey,
                                vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    SplayTreeNode *new_node = NULL;

    if (spt && pKey) {

        new_node = VdsMalloc(sizeof(SplayTreeNode));

        if (new_node) {

            new_node->item.pData = pData;
            new_node->item.pKey = pKey;
            new_node->right = new_node->left = new_node->parent = NULL;

            if (spt->root) {
                SplayTreeNode *curr = spt->root, *parent = NULL;
                int cmp_res;

                while (1) {
                    cmp_res = spt->KeyCmp(pKey, curr->item.pKey);

                    if (cmp_res > 0) {

                        parent = curr;

                        curr = curr->right;

                        if (!curr) {
                            new_node->parent = parent;
                            parent->right = new_node;
                            break;
                        }

                    } else if (cmp_res < 0) {

                        parent = curr;

                        curr = curr->left;

                        if (!curr) {
                            new_node->parent = parent;
                            parent->left = new_node;
                            break;
                        }

                    } else { //if there's another node with the same key already on the tree
                        VdsFree(new_node); //return without doing anything
                        new_node = NULL;
                        tmp_err = VDS_KEY_EXISTS;
                        break;
                    }
                }

                splay(new_node);
            }

            spt->root = new_node;

        } else
            tmp_err = VDS_MALLOC_FAIL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

void splay(SplayTreeNode *sptNode)
{
    if (sptNode) {
        SplayTreeNode *sptGrandpa, *sptFather;

        sptFather = sptNode->parent;

        while (sptFather) {

            sptGrandpa = sptFather->parent;

            if (sptGrandpa) {

                if (isLeftNode(sptNode)) {
                    if (isLeftNode(sptFather)) {
                        //zig zig
                        RotateRight(sptFather, sptGrandpa);
                        RotateRight(sptNode, sptFather);
                    } else {
                        //zag zig
                        RotateRight(sptNode, sptFather);
                        RotateLeft(sptNode, sptGrandpa);
                    }
                } else {
                    if (isLeftNode(sptFather)) {
                        //zig zag
                        RotateLeft(sptNode, sptFather);
                        RotateRight(sptNode, sptGrandpa);
                    } else {
                        //zag zag
                        RotateLeft(sptFather, sptGrandpa);
                        RotateLeft(sptNode, sptFather);
                    }
                }

            } else {

                if (isLeftNode(sptNode)) {
                    //zig
                    RotateRight(sptNode, sptFather);
                } else {
                    //zag
                    RotateLeft(sptNode, sptFather);
                }

            }

            sptFather = sptNode->parent;
        }
    }
}

KeyValuePair SplayTree_deleteNode(SplayTree *spt,
                                  SplayTreeNode *sptToDelete,
                                  vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    KeyValuePair item = { 0 };

    if (spt && spt->root && sptToDelete) {

        //if the node we want to delete has two children nodes
        //we switch it with its inorder successor from the right subtree
        if (sptToDelete->right && sptToDelete->left) {
            KeyValuePair swapped_item;
            SplayTreeNode *sptSuccessor = sptToDelete->right;

            while (sptSuccessor->left)
                sptSuccessor = sptSuccessor->left;

            //swap the data (key and value) of the two nodes
            swapped_item = sptToDelete->item;
            sptToDelete->item = sptSuccessor->item;
            sptSuccessor->item = swapped_item;

            sptToDelete = sptSuccessor;
        }

        //now the node we want to delete has AT MOST one child node

        SplayTreeNode *parent = sptToDelete->parent;

        //if the node we want to delete ISN'T the root node
        if (parent) {
            //if the node we want to delete is a right node
            if (!isLeftNode(sptToDelete)) {
                //and we change the right node of the parent so
                //that it points to either the right node of the node we
                //want to delete, or the left node, depending on which one
                //is not NULL (if both are NULL then we point to NULL)
                parent->right = (sptToDelete->right) ? sptToDelete->right : sptToDelete->left;
            } else { //if the key of the parent is smaller, it's a left node
                parent->left = (sptToDelete->right) ? sptToDelete->right : sptToDelete->left;
            }
        //else if the node we want to delete IS the root node
        } else {
            //change spt->root accordingly, so that it points to the new root (or NULL, if it's the only node in the tree)
            spt->root = (sptToDelete->right) ? sptToDelete->right : sptToDelete->left;
        }

        //don't forget to change the parents of the children node too
        //(if they exist)
        if (sptToDelete->right)
            sptToDelete->right->parent = parent;
        else if (sptToDelete->left)
            sptToDelete->left->parent = parent;

        //copy the item of the node we are about to delete, to keep it as a return value
        item = sptToDelete->item;

        splay(parent);

        //delete the node because we don't need it anymore
        //and no other nodes point to it
        VdsFree(sptToDelete);
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return item;
}

KeyValuePair SplayTree_deleteByKey(SplayTree *spt,
                                   void *pKey,
                                   vdsErrCode *err)
{
    if (spt && pKey) {
        SplayTreeNode *curr = spt->root;
        int cmp_res;

        curr = spt->root;
        while (curr) {
            cmp_res = spt->KeyCmp(curr->item.pKey, pKey);

            if (!cmp_res)
                break;

            if (cmp_res < 0)
                curr = curr->right;

            if (cmp_res > 0)
                curr = curr->left;
        }

        return SplayTree_deleteNode(spt, curr, err);

    }

    if (err)
        *err = VDS_INVALID_ARGS;

    return (KeyValuePair){NULL, NULL};
}

SplayTreeNode *SplayTree_findNode(SplayTree *spt,
                                  void *pKey,
                                  vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    SplayTreeNode *curr = NULL, *parent = NULL;

    if (spt && pKey) {
        int cmp_res;

        curr = spt->root;
        while (curr) {
            cmp_res = spt->KeyCmp(curr->item.pKey, pKey);

            if (!cmp_res)
                break;

            if (cmp_res < 0) {
                parent = curr;
                curr = curr->right;
            }

            if (cmp_res > 0) {
                parent = curr;
                curr = curr->left;
            }
        }

        if (curr)
            splay(curr);
        else
            splay(parent);
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

void *SplayTree_findData(SplayTree *spt,
                         void *pKey,
                         vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    SplayTreeNode *curr = NULL, *parent = NULL;

    if (spt && pKey) {
        int cmp_res;

        curr = spt->root;
        while (curr) {
            cmp_res = spt->KeyCmp(curr->item.pKey, pKey);

            if (!cmp_res)
                break;

            if (cmp_res < 0) {
                parent = curr;
                curr = curr->right;
            }

            if (cmp_res > 0) {
                parent = curr;
                curr = curr->left;
            }
        }

        if (curr)
            splay(curr);
        else
            splay(parent);
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return (curr) ? curr->item.pData : NULL;
}

void SplayTree_traverse(SplayTree *spt,
                        vdsTreeTraversal traversal,
                        vdsUserDataFunc callback,
                        vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (spt && spt->root && callback) {
        switch (traversal) {
        case VDS_PRE_ORDER:
            pre_orderTraversal(spt->root, callback);
            break;
        case VDS_IN_ORDER:
            in_orderTraversal(spt->root, callback);
            break;
        case VDS_POST_ORDER:
            post_orderTraversal(spt->root, callback);
            break;
        case VDS_BREADTH_FIRST:
            if (!breadth_firstTraversal(spt->root, callback))
                tmp_err = VDS_MALLOC_FAIL;
            break;
        case VDS_EULER:
            eulerTraversal(spt->root, callback);
            break;
        default:
            break;
        }
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void SplayTree_destroy(SplayTree **spt,
                       vdsUserDataFunc freeData,
                       vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (spt && *spt) {

        SplayTreeNode *curr = (*spt)->root, *to_delete;

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
                    freeData((void *)&to_delete->item);

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

        VdsFree(*spt);
        //this line is the reason for the double pointer parameter **
        *spt = NULL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}


//library internal functions to traverse binary tree data structures
//no error checking required

#include "FIFOqueue.h"

void pre_orderTraversal(SplayTreeNode *sptNode, vdsUserDataFunc callback)
{
    if (sptNode) {
        callback((void *)&sptNode->item);
        pre_orderTraversal(sptNode->left, callback);
        pre_orderTraversal(sptNode->right, callback);
    }
}

void in_orderTraversal(SplayTreeNode *sptNode, vdsUserDataFunc callback)
{
    if (sptNode) {
        in_orderTraversal(sptNode->left, callback);
        callback((void *)&sptNode->item);
        in_orderTraversal(sptNode->right, callback);
    }
}

void post_orderTraversal(SplayTreeNode *sptNode, vdsUserDataFunc callback)
{
    if (sptNode) {
        post_orderTraversal(sptNode->left, callback);
        post_orderTraversal(sptNode->right, callback);
        callback((void *)&sptNode->item);
    }
}

int breadth_firstTraversal(SplayTreeNode *sptRoot, vdsUserDataFunc callback)
{
    vdsErrCode err;
    SplayTreeNode *curr;
    FIFOqueue *levelFIFO = FIFO_init(&err);

    if (levelFIFO) {
        FIFO_enqueue(levelFIFO, (void *)sptRoot, &err);

        if (err == VDS_SUCCESS) {

            while (levelFIFO->total_nodes) {
                curr = (SplayTreeNode *)FIFO_dequeue(levelFIFO, NULL);

                callback((void *)&curr->item);

                if (curr->right) {
                    FIFO_enqueue(levelFIFO, curr->right, &err);

                    if (err != VDS_SUCCESS)
                        break;
                }

                if (curr->left) {
                    FIFO_enqueue(levelFIFO, curr->left, &err);

                    if (err != VDS_SUCCESS)
                        break;
                }
            }

            FIFO_destroy(&levelFIFO, NULL, NULL);

        }
    }

    if (err == VDS_SUCCESS)
        return 1;

    return 0;
}

void eulerTraversal(SplayTreeNode *sptNode, vdsUserDataFunc callback)
{
    if (sptNode) {
        callback((void *)&sptNode->item);

        eulerTraversal(sptNode->left, callback);
        callback((void *)&sptNode->item);
        eulerTraversal(sptNode->right, callback);
        callback((void *)&sptNode->item);
    }
}
