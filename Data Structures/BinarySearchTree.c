/***********************************************\
*              BinarySearchTree.c               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTree.h"
#include "FIFOqueue.h"

#define isLeafNode(x) (!(x->right || x->left))


static void pre_orderTraversal(BSTreeNode *bstRoot, CustomDataCallback callback);
static void in_orderTraversal(BSTreeNode *bstRoot, CustomDataCallback callback);
static void post_orderTraversal(BSTreeNode *bstRoot, CustomDataCallback callback);
static void breadth_firstTraversal(BSTreeNode *bstRoot, CustomDataCallback callback);
static void eulerTraversal(BSTreeNode *bstRoot, CustomDataCallback callback);


BSTreeNode *BSTree_insert(BSTreeNode **bstRoot, key_type key, void *pData)
{
    BSTreeNode *new_node = NULL;

    if (bstRoot) {

        new_node = calloc(1, sizeof(BSTreeNode));

        new_node->key = key;
        new_node->pData = pData;
        //done by calloc
        //new_node->right = new_node->left = new_node->parent = NULL;

        if (!(*bstRoot)) {
            *bstRoot = new_node;
        } else {
            BSTreeNode *curr = *bstRoot, *parent = NULL;

            while (1) {

                if (key > curr->key) {

                    parent = curr;
                    curr = curr->right;

                    if (!curr) {
                        new_node->parent = parent;
                        parent->right = new_node;
                        break;
                    }

                } else if (key < curr->key) {
                    parent = curr;
                    curr = curr->left;

                    if (!curr) {
                        new_node->parent = parent;
                        parent->left = new_node;
                        break;
                    }

                } else { //if there's another node with the same key already on the tree
                    free(new_node); //return without doing anything
                    new_node = NULL;
                    break;
                }
            }
        }
    }

    return new_node;
}

void *BSTree_deleteNode(BSTreeNode **bstRoot, BSTreeNode *bstToDelete)
{
    void *pData = NULL;

    if (bstRoot) {
        if (*bstRoot && bstToDelete) {

            //if the node we want to delete has two children nodes
            //we switch it with the first leftmost leaf node from the right subtree
            if (bstToDelete->right && bstToDelete->left) {

                //temporary value to store the data that is being swapped
                BSTreeNode *bstTmp;
                BSTreeNode *bstFirstLeaf = bstToDelete->right;

                while ( !isLeafNode(bstFirstLeaf) ) {
                    if (bstFirstLeaf->left)
                        bstFirstLeaf = bstFirstLeaf->left;
                    else
                        bstFirstLeaf = bstFirstLeaf->right;
                }

                //swap the *parent, *left and *right pointers of the two nodes
                bstTmp = bstToDelete->parent;
                bstToDelete->parent = bstFirstLeaf->parent;
                bstFirstLeaf->parent = bstTmp;
                bstFirstLeaf->left = bstToDelete->left;
                bstFirstLeaf->right = bstToDelete->right;
                //since the node we want to delete, becomes a leaf now,
                //its children are NULLed
                bstToDelete->left = bstToDelete->right = NULL;

            }

            //now the node we want to delete has AT MOST one child node

            BSTreeNode *parent = bstToDelete->parent;

            //if the node we want to delete ISN'T the root node
            if (parent) {
                //if the key of the node we want to delete, is bigger
                //than the key of its parent, then it's a right node
                if (bstToDelete->key > parent->key) {
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
                //change bstRoot accordingly, so that it points to the new root (or NULL, if it's the only node in the tree)
                *bstRoot = (bstToDelete->right) ? bstToDelete->right : bstToDelete->left;
            }

            //don't forget to change the parents of the children node too
            //(if they exist)
            if (bstToDelete->right)
                bstToDelete->right->parent = parent;
            else if (bstToDelete->left)
                bstToDelete->left->parent = parent;

            pData = bstToDelete->pData;

            //delete the node because we don't need it anymore
            //and no other nodes point to it
            free(bstToDelete);
        }
    }

    return pData;
}

void *BSTree_deleteByKey(BSTreeNode **bstRoot, key_type key)
{
    return BSTree_deleteNode(bstRoot, BSTree_find(*bstRoot, key));
}

BSTreeNode *BSTree_find(BSTreeNode *bstRoot, key_type key)
{
    BSTreeNode *curr = bstRoot;

    while (curr) {
        if (curr->key == key)
            break;

        if (key > curr->key)
            curr = curr->right;

        if (key < curr->key)
            curr = curr->left;
    }

    return curr;
}

void BSTree_traverse(BSTreeNode *bstRoot, TreeTraversalMethod traversal, CustomDataCallback callback)
{
    if (callback && bstRoot) {
        switch (traversal) {
        case PRE_ORDER:
            pre_orderTraversal(bstRoot, callback);
            break;
        case IN_ORDER:
            in_orderTraversal(bstRoot, callback);
            break;
        case POST_ORDER:
            post_orderTraversal(bstRoot, callback);
            break;
        case BREADTH_FIRST:
            breadth_firstTraversal(bstRoot, callback);
            break;
        case EULER:
            eulerTraversal(bstRoot, callback);
            break;
        default:
            break;
        }
    }
}

void BSTree_destroy(BSTreeNode **bstRoot, CustomDataCallback freeData)
{
    if (bstRoot) {

        BSTreeNode *curr = *bstRoot, *to_delete;

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

        *bstRoot = NULL;
    }
}


//library internal functions to traverse binary tree data structures
//no error checking required

#include "FIFOqueue.h"

void pre_orderTraversal(BSTreeNode *bstRoot, CustomDataCallback callback)
{
    if (bstRoot) {
        callback(bstRoot);
        pre_orderTraversal(bstRoot->left, callback);
        pre_orderTraversal(bstRoot->right, callback);
    }
}

void in_orderTraversal(BSTreeNode *bstRoot, CustomDataCallback callback)
{
    if (bstRoot) {
        in_orderTraversal(bstRoot->left, callback);
        callback(bstRoot);
        in_orderTraversal(bstRoot->right, callback);
    }
}

void post_orderTraversal(BSTreeNode *bstRoot, CustomDataCallback callback)
{
    if (bstRoot) {
        post_orderTraversal(bstRoot->left, callback);
        post_orderTraversal(bstRoot->right, callback);
        callback(bstRoot);
    }
}

void breadth_firstTraversal(BSTreeNode *bstRoot, CustomDataCallback callback)
{
    BSTreeNode *curr;
    FIFOqueue *levelFIFO = FIFO_init();

    FIFO_enqueue(levelFIFO, bstRoot);

    while (levelFIFO->total_nodes) {
        curr = (BSTreeNode *)FIFO_dequeue(levelFIFO);
        callback(curr);

        if (curr->right)
            FIFO_enqueue(levelFIFO, curr->right);
        if (curr->left)
            FIFO_enqueue(levelFIFO, curr->left);
    }

    FIFO_destroy(&levelFIFO, NULL);
}

void eulerTraversal(BSTreeNode *bstRoot, CustomDataCallback callback)
{
    if (bstRoot) {
        callback(bstRoot);

        eulerTraversal(bstRoot->left, callback);
        callback(bstRoot);
        eulerTraversal(bstRoot->right, callback);
        callback(bstRoot);
    }
}
