 /********************
 *  Treap.c
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "MemoryAllocation.h"
#include "Treap.h"

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


static void pre_orderTraversal(TreapNode *treapNode, UserDataCallback callback);
static void in_orderTraversal(TreapNode *treapNode, UserDataCallback callback);
static void post_orderTraversal(TreapNode *treapNode, UserDataCallback callback);
static int breadth_firstTraversal(TreapNode *treapNode, UserDataCallback callback);
static void eulerTraversal(TreapNode *treapNode, UserDataCallback callback);

static void fix_max_order(Treap *treap, TreapNode *curr);
static void fix_min_order(Treap *treap, TreapNode *curr);



Treap *Treap_init(UserCompareCallback KeyCmp,
                  HeapPropertyType property,
                  unsigned int seed,
                  EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    Treap *treap = NULL;

    if (KeyCmp) {

        switch (property) {
        case EDS_MAX_HEAP:
        case EDS_MIN_HEAP:
            treap = EdsMalloc(sizeof(Treap));

            if (treap) {

                treap->root = NULL;
                treap->KeyCmp = KeyCmp;
                treap->property = property;

                treap->rand_gen_state = RandomState_init(seed, &tmp_err);

                if (tmp_err != EDS_SUCCESS) {
                    EdsFree(treap);
                    tmp_err = EDS_MALLOC_FAIL;
                }

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

    return treap;
}

TreapNode *Treap_insert(Treap *treap,
                        void *pKey,
                        void *pData,
                        EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    TreapNode *new_node = NULL;

    if (treap && pKey) {

        new_node = EdsMalloc(sizeof(TreapNode));

        if (new_node) {

            //generate a random priority
            new_node->priority = RandomState_genUInt(treap->rand_gen_state, NULL);
            new_node->item.pData = pData;
            new_node->item.pKey = pKey;
            new_node->right = new_node->left = new_node->parent = NULL;

            if (!treap->root) {
                treap->root = new_node;
            } else {
                TreapNode *curr = treap->root, *parent = NULL;
                int cmp_res;

                while (1) {
                    cmp_res = treap->KeyCmp(pKey, curr->item.pKey);

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
                        EdsFree(new_node); //return without doing anything
                        parent = new_node = NULL;
                        tmp_err = EDS_KEY_EXISTS;
                        break;
                    }

                }

                //we fix the property of the tree only if the new node was successfully inserted
                if (new_node) {

                    switch (treap->property) {
                    case EDS_MAX_HEAP:
                        fix_max_order(treap, new_node);
                        break;
                    case EDS_MIN_HEAP:
                        fix_min_order(treap, new_node);
                        break;
                    default:
                        tmp_err = EDS_INVALID_ARGS;
                        break;
                    }

                }

            }
        } else
            tmp_err = EDS_MALLOC_FAIL;
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_node;
}

void fix_max_order(Treap *treap, TreapNode *curr)
{
    TreapNode *parent = curr->parent;

    while (parent) {

        //this loop only makes sense if the parent's priority
        //is less than the priority of the child
        if (parent->priority < curr->priority) {

            if (isLeftNode(curr))
                RotateRight(curr, parent);
            else
                RotateLeft(curr, parent);

            if (parent == treap->root) {
                treap->root = curr;
                //break; not necessary since curr->parent == NULL now
            }

            parent = curr->parent;

        } else
            break;
    }
}

void fix_min_order(Treap *treap, TreapNode *curr)
{
    TreapNode *parent = curr->parent;

    while (parent) {

        if (parent->priority > curr->priority) {

            if (isLeftNode(curr))
                RotateRight(curr, parent);
            else
                RotateLeft(curr, parent);

            if (parent == treap->root) {
                treap->root = curr;
                //break; not necessary since curr->parent == NULL now
            }

            parent = curr->parent;

        } else
            break;
    }
}

KeyValuePair Treap_deleteNode(Treap *treap,
                              TreapNode *treapNode,
                              EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    int reorder = 0;
    KeyValuePair item = { 0 };

    if (treap && treap->root && treapNode) {

        //if the node we want to delete has two children nodes
        //we switch it with its inorder successor from the right subtree
        if (treapNode->right && treapNode->left) {
            //temporary value to store the data that is being swapped
            KeyValuePair swapped_item;
            TreapNode *treapSuccessor = treapNode->right;

            while (treapSuccessor->left)
                treapSuccessor = treapSuccessor->left;

            //swap the data (key and value) of the two nodes
            swapped_item = treapNode->item;
            treapNode->item = treapSuccessor->item;
            treapSuccessor->item = swapped_item;

            treapNode = treapSuccessor;
            reorder = 1; //we only need to reorder the tree if we deleted
            //a node with two children
        }

        //now the node we want to delete has AT MOST one child node

        TreapNode *parent = treapNode->parent;

        //if the node we want to delete ISN'T the root node
        if (parent) {
            //if the node we want to delete is a right node
            if (!isLeftNode(treapNode)) {
                //and we change the right node of the parent so
                //that it points to either the right node of the node we
                //want to delete, or the left node, depending on which one
                //is not NULL (if both are NULL then we point to NULL)
                parent->right = (treapNode->right) ? treapNode->right : treapNode->left;
            } else { //if the key of the parent is smaller, it's a left node
                parent->left = (treapNode->right) ? treapNode->right : treapNode->left;
            }
        //else if the node we want to delete IS the root node
        } else {
            //change the tree root accordingly, so that it points to the new root (or NULL, if it's the only node in the tree)
            treap->root = (treapNode->right) ? treapNode->right : treapNode->left;
        }

        //don't forget to change the parents of the children node too
        //(if they exist)
        if (treapNode->right)
            treapNode->right->parent = parent;
        else if (treapNode->left)
            treapNode->left->parent = parent;

        item = treapNode->item;

        if (reorder) {
            switch (treap->property) {
            case EDS_MAX_HEAP:
                fix_max_order(treap, treapNode->parent);
                break;
            case EDS_MIN_HEAP:
                fix_min_order(treap, treapNode->parent);
                break;
            default:
                tmp_err = EDS_INVALID_ARGS;
                break;
            }
        }

        //delete the node because we don't need it anymore
        //and no other nodes point to it
        EdsFree(treapNode);

    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return item;
}

KeyValuePair Treap_deleteByKey(Treap *treap,
                               void *pKey,
                               EdsErrCode *err)
{
    return Treap_deleteNode(treap, Treap_findNode(treap, pKey, err), err);
}

TreapNode *Treap_findNode(Treap *treap,
                          void *pKey,
                          EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    TreapNode *curr = NULL;

    if (treap && pKey) {
        curr = treap->root;
        int cmp_res;

        while (curr) {
            cmp_res = treap->KeyCmp(pKey, curr->item.pKey);
            
            if (!cmp_res)
                break;

            if (cmp_res > 0)
                curr = curr->right;
            else /*if (cmp_res < 0)*/
                curr = curr->left;
        }
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

void *Treap_findData(Treap *treap,
                       void *pKey,
                       EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    TreapNode *curr = NULL;

    if (treap && pKey) {
        curr = treap->root;
        int cmp_res;

        while (curr) {
            cmp_res = treap->KeyCmp(pKey, curr->item.pKey);
            
            if (!cmp_res)
                break;

            if (cmp_res > 0)
                curr = curr->right;
            else /*if (cmp_res < 0)*/
                curr = curr->left;
        }
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return (curr) ? curr->item.pData : NULL;
}

void Treap_traverse(Treap *treap,
                    TreeTraversalMethod traversal,
                    UserDataCallback callback,
                    EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;

    if (callback && treap && treap->root) {
        switch (traversal) {
        case EDS_PRE_ORDER:
            pre_orderTraversal(treap->root, callback);
            break;
        case EDS_IN_ORDER:
            in_orderTraversal(treap->root, callback);
            break;
        case EDS_POST_ORDER:
            post_orderTraversal(treap->root, callback);
            break;
        case EDS_BREADTH_FIRST:
            if (!breadth_firstTraversal(treap->root, callback))
                tmp_err = EDS_MALLOC_FAIL;
            break;
        case EDS_EULER:
            eulerTraversal(treap->root, callback);
            break;
        default:
            tmp_err = EDS_INVALID_ARGS;
            break;
        }
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void Treap_destroy(Treap **treap,
                   UserDataCallback EdsFreeData,
                   EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;

    if (treap && *treap) {

        TreapNode *curr = (*treap)->root, *to_delete;

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

                if (EdsFreeData)
                    EdsFreeData((void *)&to_delete->item);

                if (curr) {

                    if (curr->right == to_delete) {
                        EdsFree(curr->right);
                        curr->right = NULL;
                    } else {
                        EdsFree(curr->left);
                        curr->left = NULL;
                    }

                } else { //if curr is NULL, it means that to_delete holds the root node
                    EdsFree(to_delete);
                }
            }
        }

        RandomState_destroy(&(*treap)->rand_gen_state, NULL);
        EdsFree(*treap);
        *treap = NULL;
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}


//library internal functions to traverse binary tree data structures
//no error checking required

#include "FIFOqueue.h"

void pre_orderTraversal(TreapNode *treapNode, UserDataCallback callback)
{
    if (treapNode) {
        callback((void *)&treapNode->item);
        pre_orderTraversal(treapNode->left, callback);
        pre_orderTraversal(treapNode->right, callback);
    }
}

void in_orderTraversal(TreapNode *treapNode, UserDataCallback callback)
{
    if (treapNode) {
        in_orderTraversal(treapNode->left, callback);
        callback((void *)&treapNode->item);
        in_orderTraversal(treapNode->right, callback);
    }
}

void post_orderTraversal(TreapNode *treapNode, UserDataCallback callback)
{
    if (treapNode) {
        post_orderTraversal(treapNode->left, callback);
        post_orderTraversal(treapNode->right, callback);
        callback((void *)&treapNode->item);
    }
}

int breadth_firstTraversal(TreapNode *treapRoot, UserDataCallback callback)
{
    EdsErrCode err;
    TreapNode *curr;
    FIFOqueue *levelFIFO = FIFO_init(&err);

    if (levelFIFO) {
        FIFO_enqueue(levelFIFO, (void *)treapRoot, &err);

        if (err == EDS_SUCCESS) {

            while (levelFIFO->total_nodes) {
                curr = (TreapNode *)FIFO_dequeue(levelFIFO, NULL);

                callback((void *)&curr->item);

                if (curr->right) {
                    FIFO_enqueue(levelFIFO, curr->right, &err);

                    if (err != EDS_SUCCESS)
                        break;
                }

                if (curr->left) {
                    FIFO_enqueue(levelFIFO, curr->left, &err);

                    if (err != EDS_SUCCESS)
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

void eulerTraversal(TreapNode *treapNode, UserDataCallback callback)
{
    if (treapNode) {
        callback((void *)&treapNode->item);

        eulerTraversal(treapNode->left, callback);
        callback((void *)&treapNode->item);
        eulerTraversal(treapNode->right, callback);
        callback((void *)&treapNode->item);
    }
}
