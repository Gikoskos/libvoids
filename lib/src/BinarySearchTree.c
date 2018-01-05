 /********************
 *  BinarySearchTree.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "HeapAllocation.h"
#include "BinarySearchTree.h"

#define isLeafNode(x) ( !((x)->right || (x)->left) )
#define isLeftNode(x) ( (x) == (x)->parent->left )

static void pre_orderTraversal(BSTreeNode *bstNode, vdsUserDataFunc callback);
static void in_orderTraversal(BSTreeNode *bstNode, vdsUserDataFunc callback);
static void post_orderTraversal(BSTreeNode *bstNode, vdsUserDataFunc callback);
static int breadth_firstTraversal(BSTreeNode *bstRoot, vdsUserDataFunc callback);
static void eulerTraversal(BSTreeNode *bstNode, vdsUserDataFunc callback);



BSTree *BSTree_init(vdsUserCompareFunc KeyCmp,
                    vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    BSTree *bst = NULL;

    if (KeyCmp) {
        bst = VdsMalloc(sizeof(BSTree));

        if (bst) {
            bst->root = NULL;
            bst->KeyCmp = KeyCmp;
        } else
            tmp_err = VDS_MALLOC_FAIL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return bst;
}

BSTreeNode *BSTree_insert(BSTree *bst,
                          void *pData,
                          void *pKey,
                          vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    BSTreeNode *new_node = NULL;

    if (bst && pKey) {

        new_node = VdsMalloc(sizeof(BSTreeNode));

        if (new_node) {

            new_node->item.pData = pData;
            new_node->item.pKey = pKey;
            new_node->right = new_node->left = new_node->parent = NULL;

            if (!bst->root) {
                bst->root = new_node;
            } else {
                BSTreeNode *curr = bst->root, *parent = NULL;
                int cmp_res;

                while (1) {
                    cmp_res = bst->KeyCmp(pKey, curr->item.pKey);

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
            }

        } else
            tmp_err = VDS_MALLOC_FAIL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

KeyValuePair BSTree_deleteNode(BSTree *bst,
                               BSTreeNode *bstToDelete,
                               vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    KeyValuePair item = { 0 };

    if (bst && bst->root && bstToDelete) {

        //if the node we want to delete has two children nodes
        //we switch it with its inorder successor from the right subtree
        if (bstToDelete->right && bstToDelete->left) {
            KeyValuePair swapped_item;
            BSTreeNode *bstSuccessor = bstToDelete->right;

            while (bstSuccessor->left)
                bstSuccessor = bstSuccessor->left;

            //swap the data (key and value) of the two nodes
            swapped_item = bstToDelete->item;
            bstToDelete->item = bstSuccessor->item;
            bstSuccessor->item = swapped_item;

            bstToDelete = bstSuccessor;
        }

        //now the node we want to delete has AT MOST one child node

        BSTreeNode *parent = bstToDelete->parent;

        //if the node we want to delete ISN'T the root node
        if (parent) {
            //if the node we want to delete is a right node
            if (!isLeftNode(bstToDelete)) {
                //and we change the right node of the parent so
                //that it points to either the right node of the node we
                //want to delete, or the left node, depending on which one
                //is not NULL (if both are NULL then we point to NULL)
                parent->right = (bstToDelete->right) ? bstToDelete->right : bstToDelete->left;
            } else { //if the key of the parent is smaller, it's a left node
                parent->left = (bstToDelete->right) ? bstToDelete->right : bstToDelete->left;
            }
        //else if the node we want to delete IS the root node
        } else {
            //change bst->root accordingly, so that it points to the new root (or NULL, if it's the only node in the tree)
            bst->root = (bstToDelete->right) ? bstToDelete->right : bstToDelete->left;
        }

        //don't forget to change the parents of the children node too
        //(if they exist)
        if (bstToDelete->right)
            bstToDelete->right->parent = parent;
        else if (bstToDelete->left)
            bstToDelete->left->parent = parent;

        //copy the item of the node we are about to delete, to keep it as a return value
        item = bstToDelete->item;

        //delete the node because we don't need it anymore
        //and no other nodes point to it
        VdsFree(bstToDelete);
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return item;
}

KeyValuePair BSTree_deleteByKey(BSTree *bst,
                                void *pKey,
                                vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    KeyValuePair item = { 0 };
    BSTreeNode *to_delete = BSTree_findNode(bst, pKey, &tmp_err);

    if (to_delete) {
        item = BSTree_deleteNode(bst, to_delete, err);
    }

    SAVE_ERR(err, tmp_err);

    return item;
}

BSTreeNode *BSTree_findNode(BSTree *bst,
                            void *pKey,
                            vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    BSTreeNode *curr;

    if (bst && pKey) {
        int cmp_res;

        curr = bst->root;
        while (curr) {
            cmp_res = bst->KeyCmp(curr->item.pKey, pKey);

            if (!cmp_res)
                break;

            if (cmp_res < 0)
                curr = curr->right;

            if (cmp_res > 0)
                curr = curr->left;
        }
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

void *BSTree_findData(BSTree *bst,
                      void *pKey,
                      vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    BSTreeNode *curr = NULL;

    if (bst && pKey) {
        int cmp_res;

        curr = bst->root;
        while (curr) {
            cmp_res = bst->KeyCmp(curr->item.pKey, pKey);

            if (!cmp_res)
                break;

            if (cmp_res < 0)
                curr = curr->right;

            if (cmp_res > 0)
                curr = curr->left;
        }
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return (curr) ? curr->item.pData : NULL;
}

void BSTree_traverse(BSTree *bst,
                     vdsTreeTraversal traversal,
                     vdsUserDataFunc callback,
                     vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (bst && bst->root && callback) {
        switch (traversal) {
        case VDS_PRE_ORDER:
            pre_orderTraversal(bst->root, callback);
            break;
        case VDS_IN_ORDER:
            in_orderTraversal(bst->root, callback);
            break;
        case VDS_POST_ORDER:
            post_orderTraversal(bst->root, callback);
            break;
        case VDS_BREADTH_FIRST:
            if (!breadth_firstTraversal(bst->root, callback))
                tmp_err = VDS_MALLOC_FAIL;
            break;
        case VDS_EULER:
            eulerTraversal(bst->root, callback);
            break;
        default:
            break;
        }
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void BSTree_destroy(BSTree **bst,
                    vdsUserDataFunc freeData,
                    vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (bst && *bst) {

        BSTreeNode *curr = (*bst)->root, *to_delete;

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

        VdsFree(*bst);
        //this line is the reason for the double pointer parameter **
        *bst = NULL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}


//library internal functions to traverse binary tree data structures
//no error checking required

#include "FIFOqueue.h"

void pre_orderTraversal(BSTreeNode *bstNode, vdsUserDataFunc callback)
{
    if (bstNode) {
        callback((void *)&bstNode->item);
        pre_orderTraversal(bstNode->left, callback);
        pre_orderTraversal(bstNode->right, callback);
    }
}

void in_orderTraversal(BSTreeNode *bstNode, vdsUserDataFunc callback)
{
    if (bstNode) {
        in_orderTraversal(bstNode->left, callback);
        callback((void *)&bstNode->item);
        in_orderTraversal(bstNode->right, callback);
    }
}

void post_orderTraversal(BSTreeNode *bstNode, vdsUserDataFunc callback)
{
    if (bstNode) {
        post_orderTraversal(bstNode->left, callback);
        post_orderTraversal(bstNode->right, callback);
        callback((void *)&bstNode->item);
    }
}

int breadth_firstTraversal(BSTreeNode *bstNode, vdsUserDataFunc callback)
{
    vdsErrCode err;
    BSTreeNode *curr;
    FIFOqueue *levelFIFO = FIFO_init(&err);

    if (levelFIFO) {
        FIFO_enqueue(levelFIFO, (void *)bstNode, &err);

        if (err == VDS_SUCCESS) {

            while (levelFIFO->total_nodes) {
                curr = (BSTreeNode *)FIFO_dequeue(levelFIFO, NULL);

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

void eulerTraversal(BSTreeNode *bstNode, vdsUserDataFunc callback)
{
    if (bstNode) {
        callback((void *)&bstNode->item);

        eulerTraversal(bstNode->left, callback);
        callback((void *)&bstNode->item);
        eulerTraversal(bstNode->right, callback);
        callback((void *)&bstNode->item);
    }
}
