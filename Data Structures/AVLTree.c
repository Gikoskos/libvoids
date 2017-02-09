/***********************************************\
*                   AVLTree.c                   *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "AVLTree.h"

#define isLeafNode(x) (!(x->right || x->left))

static void pre_orderTraversal(AVLTreeNode *avltRoot, CustomDataCallback callback);
static void in_orderTraversal(AVLTreeNode *avltRoot, CustomDataCallback callback);
static void post_orderTraversal(AVLTreeNode *avltRoot, CustomDataCallback callback);
static void breadth_firstTraversal(AVLTreeNode *avltRoot, CustomDataCallback callback);
static void eulerTraversal(AVLTreeNode *avltRoot, CustomDataCallback callback);

static long balanceFactor(AVLTreeNode *avltNode);
static void correctNodeHeight(AVLTreeNode *avltNode);
static void rebalanceAVLTree(AVLTreeNode **avltRoot, AVLTreeNode *avltStartNode);


static int isBSTUtil(AVLTreeNode* node, unsigned long min, unsigned long max);


int isBST(AVLTreeNode* node)
{
    return(isBSTUtil(node, 0, ULONG_MAX)); 
}

int isBSTUtil(AVLTreeNode* node, unsigned long min, unsigned long max) 
{
    /* an empty tree is BST */
    if (node==NULL)
        return 1;

    /* false if this node violates the min/max constraint */
    if (node->key < min || node->key > max)
        return 0;

    /* otherwise check the subtrees recursively,
    tightening the min or max constraint */
    return
        isBSTUtil(node->left, min, node->key-1) &&  // Allow only distinct values
        isBSTUtil(node->right, node->key+1, max);  // Allow only distinct values
}

AVLTreeNode *insertNodeAVLTree(AVLTreeNode **avltRoot, unsigned long key, void *pData)
{
    AVLTreeNode *new_node = NULL;

    if (avltRoot && key < ULONG_MAX) {

        new_node = calloc(1, sizeof(AVLTreeNode));

        new_node->key = key;
        new_node->pData = pData;

        //done by calloc
        //new_node->height = 0;
        //new_node->right = new_node->left = new_node->parent = NULL;

        if (!(*avltRoot)) {
            *avltRoot = new_node;
        } else {
            AVLTreeNode *curr = *avltRoot, *parent = NULL;

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

            rebalanceAVLTree(avltRoot, new_node);

        }
    }

    return new_node;
}

long balanceFactor(AVLTreeNode *avltNode)
{
    long bf = 0;

    if (avltNode) {

        unsigned long right_height, left_height;

        right_height = left_height = (unsigned long)-1;

        if (avltNode->right)
            right_height = avltNode->right->height;

        if (avltNode->left)
            left_height = avltNode->left->height;

        bf = (long)(right_height - left_height);
    }

    return bf;
} 

void rebalanceAVLTree(AVLTreeNode **avltRoot, AVLTreeNode *avltStartNode)
{
    if (*avltRoot && avltStartNode) {

        AVLTreeNode *curr = avltStartNode->parent;

        //climb the path up to the root
        while (curr) {

            correctNodeHeight(curr);
            long bf = balanceFactor(curr);

            //if the left subtree is heavier
            if (bf < -1) {

                //if the right subtree of the left subtree is heavier
                if (balanceFactor(curr->left) > 0) {
                    /**************************************
                     perform left-right rotation
                      a                a
                     /                /                 c
                    b         ->     c        ->       / \
                     \              /                 b   a
                      c            b               
                    ***************************************/
                    AVLTreeNode *a, *b, *c;

                    a = curr;
                    b = a->left;
                    c = b->right;

                    //left rotation
                    c->left = b;
                    c->parent = a;
                    b->parent = c;
                    a->left = c;
                    b->right = NULL;

                    //right rotation
                    //a->left = c->right;
                    c->right = a;
                    a->left = c;
                    a->parent = c;
                    a->left = NULL;

                } else {
                    /**********************
                     perform right rotation
                        a
                       /                b
                      b       ->       / \
                     /                c   a
                    c   
                    ***********************/
                    AVLTreeNode *a, *b;

                    a = curr;
                    b = a->left;

                    //a->left = b->right;
                    b->right = a;
                    b->parent = a->parent;

                    //b->parent->left = b;
                    a->parent = b;

                }

                break;
            //else if the right subtree is heavier
            } else if (bf > 1) {

                //if the left subtree of the right subtree is heavier
                if (balanceFactor(curr->right) < 0) {
                    /***************************************
                     perform right-left rotation
                    a                a
                     \                \                  c
                      b       ->       c       ->       / \
                     /                  \              a   b
                    c                    b
                    ****************************************/
                    AVLTreeNode *a, *b, *c;

                    a = curr;
                    b = a->right;
                    c = b->left;

                    //right rotation
                    c->right = b;
                    a->right = c;
                    c->parent = a;
                    b->parent = c;

                    //left rotation
                    a->right = c->left;
                    c->left = a;
                    c->parent = a->parent;
                    c->parent->left = c;
                    a->parent = c;

                } else {
                    /**********************
                     perform left rotation
                    a
                     \                  b
                      b       ->       / \
                       \              a   c
                        c
                    ***********************/
                    AVLTreeNode *a, *b;

                    a = curr;
                    b = a->right;

                    a->right = b->left;
                    b->left = a;
                    b->parent = a->parent;
                    b->parent->left = b;
                    a->parent = b;

                }

                break;
            }

            curr = curr->parent;
        }

    }
}

void correctNodeHeight(AVLTreeNode *avltNode)
{
    if (avltNode) {

        unsigned long right_height, left_height;

        right_height = left_height = (unsigned long)-1; //ULONG_MAX

        if (avltNode->right)
            right_height = avltNode->right->height;

        if (avltNode->left)
            left_height = avltNode->left->height;

        avltNode->height = (right_height > left_height) ? right_height + 1 : left_height + 1;

    }
}

void *deleteNodeAVLTree(AVLTreeNode **avltRoot, AVLTreeNode *avltToDelete)
{
    void *pData = NULL;

    if (avltRoot) {
        if (*avltRoot && avltToDelete) {

            //if the node we want to delete has two children nodes
            //we switch it with the first leftmost leaf node from the right subtree
            if (avltToDelete->right && avltToDelete->left) {

                //temporary value to store the parent node that is being swapped
                AVLTreeNode *avltTmp;
                AVLTreeNode *avltFirstLeaf = avltToDelete->right;

                //@TODO: optimize swapped node choice
                while ( !isLeafNode(avltFirstLeaf) ) {
                    if (avltFirstLeaf->left)
                        avltFirstLeaf = avltFirstLeaf->left;
                    else
                        avltFirstLeaf = avltFirstLeaf->right;
                }

                //swap the *parent pointers of the two nodes
                avltTmp = avltToDelete->parent;
                avltToDelete->parent = avltFirstLeaf->parent;
                avltFirstLeaf->parent = avltTmp;

                //the swapped leaf node inherits the height and the children of the node that is to be deleted
                avltFirstLeaf->height = avltToDelete->height;
                avltFirstLeaf->left = avltToDelete->left;
                avltFirstLeaf->right = avltToDelete->right;

                //since the node we want to delete, becomes a leaf now,
                //its children and height are zero'd out
                avltToDelete->height = 0;
                avltToDelete->left = avltToDelete->right = NULL;

            }

            //now the node we want to delete has AT MOST one child node

            AVLTreeNode *parent = avltToDelete->parent;

            //if the node we want to delete ISN'T the root node
            if (parent) {
                //if the key of the node we want to delete, is bigger
                //than the key of its parent, then it's a right node
                if (avltToDelete->key > parent->key) {
                    //and we change the right node of the parent so
                    //that it points to either the right node of the node we
                    //want to delete, or the left node, depending on which one
                    //is not NULL (if both are NULL then we point to NULL)
                    parent->right = (avltToDelete->right) ? avltToDelete->right : avltToDelete->left;
                } else { //if the key of the parent is smaller, it's a left node
                    parent->left = (avltToDelete->right) ? avltToDelete->right : avltToDelete->left;
                }
            //else if the node we want to delete IS the root node
            } else {
                //change avltRoot accordingly, so that it points to the new root (or NULL, if it's the only node in the tree)
                *avltRoot = (avltToDelete->right) ? avltToDelete->right : avltToDelete->left;
            }

            //don't forget to change the parents of the children node too
            //(if they exist)
            if (avltToDelete->right)
                avltToDelete->right->parent = parent;
            else if (avltToDelete->left)
                avltToDelete->left->parent = parent;

            pData = avltToDelete->pData;

            //delete the node because we don't need it anymore
            //and no other nodes point to it
            free(avltToDelete);
        }
    }

    return pData;
}

void *deleteByKeyAVLTree(AVLTreeNode **avltRoot, unsigned long key)
{
    return deleteNodeAVLTree(avltRoot, findNodeAVLTree(*avltRoot, key));
}

AVLTreeNode *findNodeAVLTree(AVLTreeNode *avltRoot, unsigned long key)
{
    AVLTreeNode *curr = avltRoot;

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

void traverseAVLTree(AVLTreeNode *avltRoot, TreeTraversalMethod traversal, CustomDataCallback callback)
{
    if (callback && avltRoot) {
        switch (traversal) {
        case PRE_ORDER:
            pre_orderTraversal(avltRoot, callback);
            break;
        case IN_ORDER:
            in_orderTraversal(avltRoot, callback);
            break;
        case POST_ORDER:
            post_orderTraversal(avltRoot, callback);
            break;
        case BREADTH_FIRST:
            breadth_firstTraversal(avltRoot, callback);
            break;
        case EULER:
            eulerTraversal(avltRoot, callback);
            break;
        default:
            break;
        }
    }
}

void deleteAVLTree(AVLTreeNode **avltRoot, CustomDataCallback freeData)
{
    if (avltRoot) {

        AVLTreeNode *curr = *avltRoot, *to_delete;

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

        *avltRoot = NULL;
    }
}


//library internal functions to traverse binary tree data structures
//no error checking required

#include "FIFOqueue.h"

void pre_orderTraversal(AVLTreeNode *avltRoot, CustomDataCallback callback)
{
    if (avltRoot) {
        callback(avltRoot);
        pre_orderTraversal(avltRoot->left, callback);
        pre_orderTraversal(avltRoot->right, callback);
    }
}

void in_orderTraversal(AVLTreeNode *avltRoot, CustomDataCallback callback)
{
    if (avltRoot) {
        in_orderTraversal(avltRoot->left, callback);
        callback(avltRoot);
        in_orderTraversal(avltRoot->right, callback);
    }
}

void post_orderTraversal(AVLTreeNode *avltRoot, CustomDataCallback callback)
{
    if (avltRoot) {
        post_orderTraversal(avltRoot->left, callback);
        post_orderTraversal(avltRoot->right, callback);
        callback(avltRoot);
    }
}

void breadth_firstTraversal(AVLTreeNode *avltRoot, CustomDataCallback callback)
{
    AVLTreeNode *curr;
    FIFOqueue *levelFIFO = newFIFO();

    enqueueFIFO(levelFIFO, avltRoot);

    while (levelFIFO->total_nodes) {
        curr = (AVLTreeNode *)dequeueFIFO(levelFIFO);
        callback(curr);

        if (curr->right)
            enqueueFIFO(levelFIFO, curr->right);
        if (curr->left)
            enqueueFIFO(levelFIFO, curr->left);
    }

    deleteFIFO(&levelFIFO, 0);
}

void eulerTraversal(AVLTreeNode *avltRoot, CustomDataCallback callback)
{
    if (avltRoot) {
        callback(avltRoot);

        eulerTraversal(avltRoot->left, callback);
        callback(avltRoot);
        eulerTraversal(avltRoot->right, callback);
        callback(avltRoot);
    }
}
