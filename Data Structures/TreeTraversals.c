/***********************************************\
*                TreeTraversals.c               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#include "BinarySearchTree.h"
#include "FIFOqueue.h"

//library internal functions to traverse binary tree data structures
//no error checking required

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
    FIFOqueue *levelFIFO = newFIFO();

    enqueueFIFO(levelFIFO, bstRoot);

    while (levelFIFO->total_nodes) {
        curr = (BSTreeNode *)dequeueFIFO(levelFIFO);
        callback(curr);

        if (curr->right)
            enqueueFIFO(levelFIFO, curr->right);
        if (curr->left)
            enqueueFIFO(levelFIFO, curr->left);
    }

    deleteFIFO(levelFIFO, 0);
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
