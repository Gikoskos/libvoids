/***********************************************\
*                   AVLTree.c                   *
*           George Koskeridis (C) 2017          *
\***********************************************/

#include <stdlib.h>
#include "AVLTree.h"

#define isLeafNode(x) (!(x->right || x->left))

#define RotateRight(x, y) \
    do { \
        if (x->right) \
            x->right->parent = y; \
\
        y->left = x->right; \
        x->right = y; \
        x->parent = y->parent; \
\
        if (y->parent) { \
            if (y == y->parent->left) \
                y->parent->left = x; \
            else \
                y->parent->right = x; \
        } \
\
        y->parent = x; \
    } while (0)

#define RotateLeft(x, y) \
    do { \
        if (x->left) \
            x->left->parent = y; \
\
        y->right = x->left; \
        x->left = y; \
        x->parent = y->parent; \
\
        if (y->parent) { \
            if (y == y->parent->left) \
                y->parent->left = x; \
            else \
                y->parent->right = x; \
        } \
\
        y->parent = x; \
    } while (0)



static void pre_orderTraversal(AVLTreeNode *avltNode, UserDataCallback callback);
static void in_orderTraversal(AVLTreeNode *avltNode, UserDataCallback callback);
static void post_orderTraversal(AVLTreeNode *avltNode, UserDataCallback callback);
static void breadth_firstTraversal(AVLTreeNode *avltRoot, UserDataCallback callback);
static void eulerTraversal(AVLTreeNode *avltNode, UserDataCallback callback);

static int balanceFactor(AVLTreeNode *avltNode);
static void correctNodeHeight(AVLTreeNode *avltNode);
static void AVLTree_rebalance(AVLTreeNode **avltRoot, AVLTreeNode *avltStartNode);


AVLTree *AVLTree_init(UserCompareCallback KeyCmp)
{
    AVLTree *avlt = NULL;

    if (KeyCmp) {
        avlt = malloc(sizeof(AVLTree));
        avlt->root = NULL;
        avlt->KeyCmp = KeyCmp;
    }

    return avlt;
}

AVLTreeNode *AVLTree_insert(AVLTree *avlt, void *pKey, void *pData)
{
    AVLTreeNode *new_node = NULL;

    if (avlt && pKey) {

        new_node = calloc(1, sizeof(AVLTreeNode));

        new_node->item.pData = pData;
        new_node->item.pKey = pKey;

        //done by calloc
        //new_node->height = 0;
        //new_node->right = new_node->left = new_node->parent = NULL;

        if (!avlt->root) {
            avlt->root = new_node;
        } else {
            AVLTreeNode *curr = avlt->root, *parent = NULL;
            int cmp_res;

            while (1) {
                cmp_res = avlt->KeyCmp(pKey, curr->item.pKey);

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
                    free(new_node); //return without doing anything
                    parent = new_node = NULL; //nullify the parent so that the rebalancing call below won't do anything
                    break;
                }

            }

            AVLTree_rebalance(&avlt->root, parent);

        }
    }

    return new_node;
}

int balanceFactor(AVLTreeNode *avltNode)
{
    int bf = 0;

    if (avltNode) {

        int right_height, left_height;

        right_height = left_height = -1;

        if (avltNode->right)
            right_height = avltNode->right->height;

        if (avltNode->left)
            left_height = avltNode->left->height;

        bf = right_height - left_height;
    }

    return bf;
}

void correctNodeHeight(AVLTreeNode *avltNode)
{
    if (avltNode) {

        int right_height, left_height;

        right_height = left_height = -1;

        if (avltNode->right)
            right_height = avltNode->right->height;

        if (avltNode->left)
            left_height = avltNode->left->height;

        avltNode->height = (right_height > left_height) ? (right_height + 1) : (left_height + 1);

    }
}

void AVLTree_rebalance(AVLTreeNode **avltRoot, AVLTreeNode *avltStartNode)
{
    if (*avltRoot && avltStartNode) {

        AVLTreeNode *curr = avltStartNode;
        AVLTreeNode *a = NULL, *b = NULL, *c = NULL;

        //climb the path up to the root
        while (curr) {

            correctNodeHeight(curr);
            int bf = balanceFactor(curr);

            //if the left subtree is heavier
            if (bf < -1) {

                //if the right subtree of the left subtree is heavier
                if (balanceFactor(curr->left) > 0) {
                    /**************************************
                     perform left-right rotation
                      a               (a)
                     /                /                 b
                   (c)        ->     b        ->       / \
                     \              /                 c   a
                      b            c
                    ***************************************/
                    a = curr;
                    c = a->left;
                    b = c->right;

                    //rotate (c)-(b) to the left
                    RotateLeft(b, c);

                    //rotate (a)-(b) to the right
                    RotateRight(b, a);

                } else {
                    /**********************
                     perform right rotation
                        a
                       /                b
                      b       ->       / \
                     /                c   a
                    c
                    ***********************/
                    a = curr;
                    b = a->left;

                    RotateRight(b, a);
                }

                break;

            //else if the right subtree is heavier
            } else if (bf > 1) {

                //if the left subtree of the right subtree is heavier
                if (balanceFactor(curr->right) < 0) {
                    /***************************************
                     perform right-left rotation
                    a               (a)
                     \                \                  b
                     (c)      ->       b       ->       / \
                     /                  \              a   c
                    b                    c
                    ****************************************/
                    a = curr;
                    c = a->right;
                    b = c->left;

                    //rotate (c)-(b) to the right
                    RotateRight(b, c);

                    //rotate (a)-(b) to the left
                    RotateLeft(b, a);

                } else {
                    /**********************
                     perform left rotation
                    a
                     \                  b
                      b       ->       / \
                       \              a   c
                        c
                    ***********************/
                    a = curr;
                    b = a->right;

                    RotateLeft(b, a);
                }

                break;
            }

            curr = curr->parent;
        }

        //if the root of the tree changed, we have to update
        //the old root so that it points to the new root
        if (curr == *avltRoot)
            *avltRoot = curr->parent;

        //fix the heights of the 3 nodes involved in the rotation
        correctNodeHeight(a);
        correctNodeHeight(c);
        correctNodeHeight(b);
    }
}

KeyValuePair AVLTree_deleteNode(AVLTree *avlt, AVLTreeNode *avltToDelete)
{
    KeyValuePair item = { 0 };

    if (avlt && avlt->root && avltToDelete) {

        //if the node we want to delete has two children nodes
        //we switch it with the first leftmost leaf node from the right subtree
        if (avltToDelete->right && avltToDelete->left) {

            //temporary value to store the parent node that is being swapped
            AVLTreeNode *avltTmp;
            AVLTreeNode *avltFirstLeaf = avltToDelete->right;

            //@TODO: optimize swapped node choice (swap with smallest node from smaller child subtree)
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
            if (avlt->KeyCmp(avltToDelete->item.pKey, parent->item.pKey) > 0) {
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
            //change the tree root accordingly, so that it points to the new root (or NULL, if it's the only node in the tree)
            avlt->root = (avltToDelete->right) ? avltToDelete->right : avltToDelete->left;
        }

        //don't forget to change the parents of the children node too
        //(if they exist)
        if (avltToDelete->right)
            avltToDelete->right->parent = parent;
        else if (avltToDelete->left)
            avltToDelete->left->parent = parent;

        item = avltToDelete->item;

        //delete the node because we don't need it anymore
        //and no other nodes point to it
        free(avltToDelete);

        AVLTree_rebalance(&avlt->root, parent);
    }

    return item;
}

KeyValuePair AVLTree_deleteByKey(AVLTree *avlt, void *pKey)
{
    return AVLTree_deleteNode(avlt, AVLTree_find(avlt, pKey));
}

AVLTreeNode *AVLTree_find(AVLTree *avlt, void *pKey)
{
    AVLTreeNode *curr = NULL;

    if (avlt && pKey) {
        curr = avlt->root;
        int cmp_res;

        while (curr) {
            cmp_res = avlt->KeyCmp(pKey, curr->item.pKey);
            
            if (!cmp_res)
                break;

            if (cmp_res > 0)
                curr = curr->right;
            else /*if (cmp_res < 0)*/
                curr = curr->left;
        }
    }

    return curr;
}

void AVLTree_traverse(AVLTree *avlt, TreeTraversalMethod traversal, UserDataCallback callback)
{
    if (callback && avlt && avlt->root) {
        switch (traversal) {
        case PRE_ORDER:
            pre_orderTraversal(avlt->root, callback);
            break;
        case IN_ORDER:
            in_orderTraversal(avlt->root, callback);
            break;
        case POST_ORDER:
            post_orderTraversal(avlt->root, callback);
            break;
        case BREADTH_FIRST:
            breadth_firstTraversal(avlt->root, callback);
            break;
        case EULER:
            eulerTraversal(avlt->root, callback);
            break;
        default:
            break;
        }
    }
}

void AVLTree_destroy(AVLTree **avlt, UserDataCallback freeData)
{
    if (avlt && *avlt) {

        AVLTreeNode *curr = (*avlt)->root, *to_delete;

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
                    freeData((void *)&to_delete->item);

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

        free(*avlt);
        *avlt = NULL;
    }
}


//library internal functions to traverse binary tree data structures
//no error checking required

#include "FIFOqueue.h"

void pre_orderTraversal(AVLTreeNode *avltNode, UserDataCallback callback)
{
    if (avltNode) {
        callback((void *)&avltNode->item);
        pre_orderTraversal(avltNode->left, callback);
        pre_orderTraversal(avltNode->right, callback);
    }
}

void in_orderTraversal(AVLTreeNode *avltNode, UserDataCallback callback)
{
    if (avltNode) {
        in_orderTraversal(avltNode->left, callback);
        callback((void *)&avltNode->item);
        in_orderTraversal(avltNode->right, callback);
    }
}

void post_orderTraversal(AVLTreeNode *avltNode, UserDataCallback callback)
{
    if (avltNode) {
        post_orderTraversal(avltNode->left, callback);
        post_orderTraversal(avltNode->right, callback);
        callback((void *)&avltNode->item);
    }
}

void breadth_firstTraversal(AVLTreeNode *avltRoot, UserDataCallback callback)
{
    AVLTreeNode *curr;
    FIFOqueue *levelFIFO = FIFO_init();

    FIFO_enqueue(levelFIFO, (void *)&avltRoot->item);

    while (levelFIFO->total_nodes) {
        curr = (AVLTreeNode *)FIFO_dequeue(levelFIFO);
        callback((void *)&curr->item);

        if (curr->right)
            FIFO_enqueue(levelFIFO, curr->right);
        if (curr->left)
            FIFO_enqueue(levelFIFO, curr->left);
    }

    FIFO_destroy(&levelFIFO, NULL);
}

void eulerTraversal(AVLTreeNode *avltNode, UserDataCallback callback)
{
    if (avltNode) {
        callback((void *)&avltNode->item);

        eulerTraversal(avltNode->left, callback);
        callback((void *)&avltNode->item);
        eulerTraversal(avltNode->right, callback);
        callback((void *)&avltNode->item);
    }
}
