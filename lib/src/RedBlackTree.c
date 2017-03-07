/***********************************************\
*                 RedBlackTree.c                *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include <assert.h>
#include "RedBlackTree.h"

#define isLeafNode(x)    ( ((x)->item.pKey == NULL) )
#define isRootNode(T, x) ( (x)->parent == (T)->nil )
#define isLeftNode(x)    ( (x) == (x)->parent->left )

#define RotateRight(T, x, y) \
    do { \
        if ((x)->right) \
            (x)->right->parent = y; \
\
        (y)->left = (x)->right; \
        (x)->right = y; \
        (x)->parent = (y)->parent; \
\
        if ((y)->parent != (T)->nil) { \
            if ((y) == (y)->parent->left) \
                (y)->parent->left = x; \
            else \
                (y)->parent->right = x; \
        } \
\
        (y)->parent = x; \
    } while (0)

#define RotateLeft(T, x, y) \
    do { \
        if ((x)->left) \
            (x)->left->parent = y; \
\
        (y)->right = (x)->left; \
        (x)->left = y; \
        (x)->parent = (y)->parent; \
\
        if ((y)->parent != (T)->nil) { \
            if (y == (y)->parent->left) \
                (y)->parent->left = x; \
            else \
                (y)->parent->right = x; \
        } \
\
        (y)->parent = x; \
    } while (0)



static void pre_orderTraversal(RedBlackTreeNode *rbtNode, UserDataCallback callback);
static void in_orderTraversal(RedBlackTreeNode *rbtNode, UserDataCallback callback);
static void post_orderTraversal(RedBlackTreeNode *rbtNode, UserDataCallback callback);
static void breadth_firstTraversal(RedBlackTreeNode *rbtRoot, UserDataCallback callback);
static void eulerTraversal(RedBlackTreeNode *rbtNode, UserDataCallback callback);

static void rebalance_insertion(RedBlackTree *rbt, RedBlackTreeNode *curr);
static void rebalance_deletion(RedBlackTree *rbt, RedBlackTreeNode *curr);


RedBlackTree *RBTree_init(UserCompareCallback KeyCmp)
{
    RedBlackTree *rbt = NULL;

    if (KeyCmp) {
        rbt = malloc(sizeof(RedBlackTree));
        rbt->root = NULL;
        //create the sentinel node
        rbt->nil = malloc(sizeof(RedBlackTreeNode));
        //its data isn't important but its color is black
        rbt->nil->color = BLACK_NODE; //this is needed in fixup functions
        rbt->KeyCmp = KeyCmp;
    }

    return rbt;
}

RedBlackTreeNode *RBTree_insert(RedBlackTree *rbt, void *pKey, void *pData)
{
    RedBlackTreeNode *new_node = NULL;

    if (rbt && pKey) {

        new_node = malloc(sizeof(RedBlackTreeNode));

        new_node->item.pData = pData;
        new_node->item.pKey = pKey;

        new_node->right = new_node->left = rbt->nil;

        if (!rbt->root) {
            new_node->parent = rbt->nil;
            new_node->color = BLACK_NODE;
            rbt->root = new_node;
        } else {
            RedBlackTreeNode *curr = rbt->root, *parent = rbt->nil;
            int cmp_res;

            new_node->color = RED_NODE; //first we paint the node red
            while (1) {
                cmp_res = rbt->KeyCmp(pKey, curr->item.pKey);

                if (cmp_res > 0) {

                    parent = curr;

                    curr = curr->right;

                    if (curr == rbt->nil) {
                        new_node->parent = parent;
                        parent->right = new_node;
                        break;
                    }

                } else if (cmp_res < 0) {

                    parent = curr;

                    curr = curr->left;

                    if (curr == rbt->nil) {
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

            rebalance_insertion(rbt, new_node);

        }
    }

    return new_node;
}

void rebalance_insertion(RedBlackTree *rbt, RedBlackTreeNode *curr)
{
    if (rbt && curr) {
        RedBlackTreeNode *rbtTmp;

        while (curr->parent->color == RED_NODE) {

            //rbtTmp will point to the uncle node (or nil) after this line
            rbtTmp = (isLeftNode(curr->parent)) ? curr->parent->parent->right : curr->parent->parent->left;

            //1st case: if the uncle is black (nil) then we perform a rotation
            if (rbtTmp->color == BLACK_NODE) {

                //if the uncle is a left node
                if (!isLeftNode(curr->parent)) {

                    if (isLeftNode(curr)) {
                        /******************************
                            (B = curr->parent->parent)
                                  /            \
                             (B = nil)       (R = curr->parent)
                                               /
                                           (R = curr)
                        ***************************************/
                        rbtTmp = curr->parent;
                        RotateRight(rbt, curr, rbtTmp);
                        /******************************
                                (B = curr->parent)
                                  /          \
                             (B = nil)     (R = curr)
                                               \
                                             (R = curr->right)
                        ***************************************/
                    } else {
                        /******************************
                            (B = curr->parent->parent)
                                  /          \
                             (B = nil)     (R = curr->parent)
                                               \
                                             (R = curr)
                        ***************************************/
                        curr = curr->parent;
                        /******************************
                               (B = curr->parent)
                                  /          \
                             (B = nil)     (R = curr)
                                               \
                                             (R = curr->right)
                        ***************************************/
                    }

                    rbtTmp = curr->parent;
                    RotateLeft(rbt, curr, rbtTmp);
                    curr->color = BLACK_NODE;
                    curr->left->color = RED_NODE;

                    if (curr->left == rbt->root)
                        rbt->root = curr;

                    /******************************
                                (B = curr)
                                /        \
                              (R)        (R)
                    *******************************/
                } else {

                    if (!isLeftNode(curr)) {
                        /******************************
                             (B = curr->parent->parent)
                               /                   \
                           (R = curr->parent)    (B = nil)
                               \
                             (R = curr)
                        ***************************************/
                        rbtTmp = curr->parent;
                        RotateLeft(rbt, curr, rbtTmp);
                        /******************************
                              (B = curr->parent)
                               /              \
                           (R = curr)       (B = nil)
                             /
                         (R = curr->left)
                        ***************************************/
                    } else {
                        /******************************
                             (B = curr->parent->parent)
                               /                  \
                           (R = curr->parent)   (B = nil)
                             /
                         (R = curr)
                        ***************************************/
                        curr = curr->parent;
                        /******************************
                              (B = curr->parent)
                               /               \
                           (R = curr)        (B = nil)
                             /
                         (R = curr->left)
                        ***************************************/
                    }

                    rbtTmp = curr->parent;
                    RotateRight(rbt, curr, rbtTmp);
                    curr->color = BLACK_NODE;
                    curr->right->color = RED_NODE;

                    if (curr->right == rbt->root)
                        rbt->root = curr;

                    /******************************
                                (B = curr)
                                /        \
                              (R)        (R)
                    *******************************/
                }

                break;

            //2nd case: if the uncle is red then we perform recoloring and keep going up
            } else {

                /******************************
                    (B = curr->parent->parent)
                       /                 \
                   (R = curr->parent)    (R)
                     /
                 (R = curr)

                           ===or===

                    (B = curr->parent->parent)
                       /                 \
                   (R = curr->parent)    (R)
                       \
                     (R = curr)

                           ===or===

                    (B = curr->parent->parent)
                       /            \
                     (R)          (R = curr->parent)
                                      \
                                    (R = curr)

                           ===or===

                    (B = curr->parent->parent)
                       /            \
                     (R)          (R = curr->parent)
                                    /
                                (R = curr)
                ***************************************/
                curr->parent->color = rbtTmp->color = BLACK_NODE;
                curr->parent->parent->color = RED_NODE;
                curr = curr->parent->parent;

            }

        }

        rbt->root->color = BLACK_NODE;

    }
}

KeyValuePair RBTree_deleteNode(RedBlackTree *rbt, RedBlackTreeNode *rbtToDelete)
{
    KeyValuePair item = { 0 };

    if (rbt && rbt->root && rbtToDelete) {

        //temporarily store the color of the node that is about to be deleted OR the color of the node
        //that replaces the node that is about to be deleted
        RedBlackTreeColor clr;

        //null the key of the sentinel node, to use on conditionals
        rbt->nil->item.pKey = NULL;

        //if the node we want to delete has two children nodes
        //we switch it with the first leftmost leaf node from the right subtree
        if (rbtToDelete->right->item.pKey && rbtToDelete->left->item.pKey) {
            //temporary value to store the data that is being swapped
            KeyValuePair swapped_item;
            RedBlackTreeNode *rbtSuccessor = rbtToDelete->right;

            while (rbtSuccessor->left)
                rbtSuccessor = rbtSuccessor->left;

            //swap the data (key and value) of the two nodes
            swapped_item = rbtToDelete->item;
            rbtToDelete->item = rbtSuccessor->item;
            rbtSuccessor->item = swapped_item;

            rbtToDelete = rbtSuccessor;
        }

        //now the node we want to delete has AT MOST one child node

        //we save the parent and the child of the node that is about to be deleted
        RedBlackTreeNode *parent = rbtToDelete->parent, *child;

        //if rbtToDelete has no children, child will point to nil and will be a black node, after this line
        child = (rbtToDelete->right->item.pKey) ? (rbtToDelete->right) : (rbtToDelete->left);

        //if the node we want to delete ISN'T the root node
        if (parent->item.pKey) {
            //if the node we want to delete is a right node, then the right child
            //of its parent has to point to the valid child of rbtToDelete. If there's
            //no valid child available, then parent will point to nil instead.
            if ( !isLeftNode(rbtToDelete) ) {
                //we change the right node of the parent so
                //that it points to either the right node of the node we
                //want to delete, or the left node, depending on which one
                //is not nil (if both are nil then we point to nil)
                parent->right = (rbtToDelete->right->item.pKey) ? rbtToDelete->right : rbtToDelete->left;
            } else { //if the key of the parent is smaller, it's a left node
                parent->left = (rbtToDelete->right->item.pKey) ? rbtToDelete->right : rbtToDelete->left;
            }
        //else if the node we want to delete IS the root node
        } else {
            //change the tree root accordingly, so that it points to the new root (or NULL, if it's the only node in the tree)
            rbt->root = (rbtToDelete->right->item.pKey) ? rbtToDelete->right : rbtToDelete->left;
        }

        //don't forget to change the parent of the child node too
        //it doesn't matter at this point, if the child is the nil sentinel, since we'll use
        //the child's parent pointer in the fixup function.
        child->parent = parent;

        /* Balance the RBTree after the deletion */
        //if the child is a red node (and the deleted node was black), then we paint it black
        //since we can't have two consecutive red nodes in the tree, so this is the easiest case
        if (child->color == RED_NODE) {
            //we have to paint black the child node in order to preserve the rule:
            //"every path from the root to a null link has the same number of black links"
            child->color = BLACK_NODE;

        //else if both the child of the deleted node, and the deleted node itself, are black nodes
        } else if (child->color == BLACK_NODE && rbtToDelete->color == BLACK_NODE) {

            //we call the fixup function with, with the child of the deleted node, as argument.
            //Even if the child is the nil, its parent is still set to point to the node above it
            rebalance_deletion(rbt, child);
        }
        /* Balancing is over */

        //store the node's item to return it
        item = rbtToDelete->item;

        //delete the node because we don't need it anymore
        //and no other nodes point to it
        free(rbtToDelete);
        
    }

    return item;
}

void rebalance_deletion(RedBlackTree *rbt, RedBlackTreeNode *curr)
{
    
}

KeyValuePair RBTree_deleteByKey(RedBlackTree *rbt, void *pKey)
{
    return RBTree_deleteNode(rbt, RBTree_find(rbt, pKey));
}

RedBlackTreeNode *RBTree_find(RedBlackTree *rbt, void *pKey)
{
    RedBlackTreeNode *curr = NULL;

    if (rbt && rbt->root && pKey) {
        int cmp_res;

        rbt->nil->item.pKey = NULL;
        curr = rbt->root;

        while (curr->item.pKey) {
            cmp_res = rbt->KeyCmp(pKey, curr->item.pKey);
            
            if (!cmp_res)
                break;

            if (cmp_res > 0)
                curr = curr->right;
            else /*if (cmp_res < 0)*/
                curr = curr->left;
        }

        //if curr points to the sentinel, then it means that the
        //search has failed and we have to return NULL
        if (!curr->item.pKey)
            curr = NULL;
    }

    return curr;
}

void RBTree_traverse(RedBlackTree *rbt, TreeTraversalMethod traversal, UserDataCallback callback)
{
    if (callback && rbt && rbt->root) {
        //To make recursion work just by passing two arguments on each traversal function, I'll
        //nullify the key of the nil sentinel and check against that on each recursive call.
        rbt->nil->item.pKey = NULL;

        switch (traversal) {
        case PRE_ORDER:
            pre_orderTraversal(rbt->root, callback);
            break;
        case IN_ORDER:
            in_orderTraversal(rbt->root, callback);
            break;
        case POST_ORDER:
            post_orderTraversal(rbt->root, callback);
            break;
        case BREADTH_FIRST:
            breadth_firstTraversal(rbt->root, callback);
            break;
        case EULER:
            eulerTraversal(rbt->root, callback);
            break;
        default:
            break;
        }
    }
}

void RBTree_destroy(RedBlackTree **rbt, UserDataCallback freeData)
{
    if (rbt && *rbt) {

        RedBlackTreeNode *curr = (*rbt)->root, *to_delete;

        (*rbt)->nil->item.pKey = NULL;

        while (curr->item.pKey) {
            if (curr->left->item.pKey) {

                curr = curr->left;

            } else if (curr->right->item.pKey) {

                curr = curr->right;

            } else {

                //if we're here we want to delete AND nil the to_delete node
                to_delete = curr;
                //we make curr the parent
                curr = curr->parent;

                if (freeData)
                    freeData((void *)&to_delete->item);

                if (curr->item.pKey) {

                    if (curr->right == to_delete) {
                        free(curr->right);
                        curr->right = (*rbt)->nil;
                    } else {
                        free(curr->left);
                        curr->left = (*rbt)->nil;
                    }

                } else { //if curr is nil, it means that to_delete holds the root node
                    free(to_delete);
                }
            }
        }

        free((*rbt)->nil);
        free(*rbt);
        *rbt = NULL;
    }
}


//library internal functions to traverse binary tree data structures
//no error checking required

#include "FIFOqueue.h"

void pre_orderTraversal(RedBlackTreeNode *rbtNode, UserDataCallback callback)
{
    if (rbtNode->item.pKey) {
        callback((void *)&rbtNode->item);
        pre_orderTraversal(rbtNode->left, callback);
        pre_orderTraversal(rbtNode->right, callback);
    }
}

void in_orderTraversal(RedBlackTreeNode *rbtNode, UserDataCallback callback)
{
    if (rbtNode->item.pKey) {
        in_orderTraversal(rbtNode->left, callback);
        callback((void *)rbtNode);
        in_orderTraversal(rbtNode->right, callback);
    }
}

void post_orderTraversal(RedBlackTreeNode *rbtNode, UserDataCallback callback)
{
    if (rbtNode->item.pKey) {
        post_orderTraversal(rbtNode->left, callback);
        post_orderTraversal(rbtNode->right, callback);
        callback((void *)&rbtNode->item);
    }
}

void breadth_firstTraversal(RedBlackTreeNode *rbtRoot, UserDataCallback callback)
{
    RedBlackTreeNode *curr;
    FIFOqueue *levelFIFO = FIFO_init();

    FIFO_enqueue(levelFIFO, (void *)&rbtRoot->item);

    while (levelFIFO->total_nodes) {
        curr = (RedBlackTreeNode *)FIFO_dequeue(levelFIFO);
        callback((void *)&curr->item);

        if (curr->right->item.pKey)
            FIFO_enqueue(levelFIFO, curr->right);
        if (curr->left->item.pKey)
            FIFO_enqueue(levelFIFO, curr->left);
    }

    FIFO_destroy(&levelFIFO, NULL);
}

void eulerTraversal(RedBlackTreeNode *rbtNode, UserDataCallback callback)
{
    if (rbtNode->item.pKey) {
        callback((void *)&rbtNode->item);

        eulerTraversal(rbtNode->left, callback);
        callback((void *)&rbtNode->item);
        eulerTraversal(rbtNode->right, callback);
        callback((void *)&rbtNode->item);
    }
}
