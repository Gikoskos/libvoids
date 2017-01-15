/***********************************************\
*              BinarySearchTree.c               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy
#include "BinarySearchTree.h"
#include "TreeTraversals.h"

BSTreeNode *insertNodeBSTree(BSTreeNode **bstRoot, unsigned long key, void *pData)
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

void *deleteNodeBSTree(BSTreeNode **bstRoot, BSTreeNode *bstToDelete)
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

                while (bstFirstLeaf->left && bstFirstLeaf->right) {
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
                    //so we change the right node of the parent so
                    //that it points to either the right node of the node we
                    //want to delete, or the right node, depending on which one
                    //is not NULL
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

void *deleteByKeyBSTree(BSTreeNode **bstRoot, unsigned long key)
{
    return deleteNodeBSTree(bstRoot, findNodeBSTree(*bstRoot, key));
}

BSTreeNode *findNodeBSTree(BSTreeNode *bstRoot, unsigned long key)
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

void traverseBSTree(BSTreeNode *bstRoot, BSTreeTraversalMethod traversal, CustomDataCallback callback)
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

void deleteBSTree(BSTreeNode **bstRoot, CustomDataCallback freeData)
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
