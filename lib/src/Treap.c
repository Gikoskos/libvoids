 /********************
 *  Treap.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "HeapAllocation.h"
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


static void pre_orderTraversal(TreapNode *treapNode, vdsUserDataFunc callback);
static void in_orderTraversal(TreapNode *treapNode, vdsUserDataFunc callback);
static void post_orderTraversal(TreapNode *treapNode, vdsUserDataFunc callback);
static int breadth_firstTraversal(TreapNode *treapNode, vdsUserDataFunc callback);
static void eulerTraversal(TreapNode *treapNode, vdsUserDataFunc callback);

static void fix_max_order(Treap *treap, TreapNode *curr);
static void fix_min_order(Treap *treap, TreapNode *curr);
static void max_bubble_down(Treap *treap, TreapNode *treapNode);
static void min_bubble_down(Treap *treap, TreapNode *treapNode);


Treap *Treap_init(vdsUserCompareFunc KeyCmp,
                  vdsHeapProperty property,
                  unsigned int seed,
                  vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    Treap *treap = NULL;

    if (KeyCmp) {

        switch (property) {
        case VDS_MAX_HEAP:
        case VDS_MIN_HEAP:
            treap = VdsMalloc(sizeof(Treap));

            if (treap) {

                treap->root = NULL;
                treap->KeyCmp = KeyCmp;
                treap->property = property;

                treap->rand_gen_state = RandomState_init(seed, &tmp_err);

                if (tmp_err != VDS_SUCCESS) {
                    VdsFree(treap);
                    tmp_err = VDS_MALLOC_FAIL;
                }

            } else
                tmp_err = VDS_MALLOC_FAIL;
            break;
        default:
            tmp_err = VDS_INVALID_ARGS;
            break;
        }

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return treap;
}

TreapNode *Treap_insert(Treap *treap,
                        void *pKey,
                        void *pData,
                        vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    TreapNode *new_node = NULL;

    if (treap && pKey) {

        new_node = VdsMalloc(sizeof(TreapNode));

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
                        VdsFree(new_node); //return without doing anything
                        parent = new_node = NULL;
                        tmp_err = VDS_KEY_EXISTS;
                        break;
                    }

                }

                //we fix the property of the tree only if the new node was successfully inserted
                if (new_node) {

                    switch (treap->property) {
                    case VDS_MAX_HEAP:
                        fix_max_order(treap, new_node);
                        break;
                    case VDS_MIN_HEAP:
                        fix_min_order(treap, new_node);
                        break;
                    default:
                        tmp_err = VDS_INVALID_ARGS;
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

void max_bubble_down(Treap *treap, TreapNode *treapNode)
{
    TreapNode *tmp;

    if (treapNode == treap->root) {
        if (treapNode->left) {
            if (treapNode->right) {
                if (treapNode->left->priority > treapNode->right->priority) {
                    tmp = treapNode->left;

                    RotateRight(tmp, treapNode);
                } else {
                    tmp = treapNode->right;

                    RotateLeft(tmp, treapNode);
                }
            } else {
                tmp = treapNode->left;

                RotateRight(tmp, treapNode);
            }

            treap->root = tmp;
        } else {
            if (treapNode->right) {
                tmp = treapNode->right;

                RotateLeft(tmp, treapNode);

                treap->root = tmp;
            } else {
                return;
            }
        }
    }

    while (1) {

        if (treapNode->left) {
            if (treapNode->right) {
                if (treapNode->left->priority > treapNode->right->priority) {
                    tmp = treapNode->left;

                    RotateRight(tmp, treapNode);

                } else {
                    tmp = treapNode->right;

                    RotateLeft(tmp, treapNode);
                }
            } else {
                tmp = treapNode->left;

                RotateRight(tmp, treapNode);
            }
        } else {
            if (treapNode->right) {
                tmp = treapNode->right;

                RotateLeft(tmp, treapNode);
            } else {
                break;
            }
        }

    }
}

void min_bubble_down(Treap *treap, TreapNode *treapNode)
{
    TreapNode *tmp;

    if (treapNode == treap->root) {
        if (treapNode->left) {
            if (treapNode->right) {
                if (treapNode->left->priority < treapNode->right->priority) {
                    tmp = treapNode->left;

                    RotateRight(tmp, treapNode);
                } else {
                    tmp = treapNode->right;

                    RotateLeft(tmp, treapNode);
                }
            } else {
                tmp = treapNode->left;

                RotateRight(tmp, treapNode);
            }

            treap->root = tmp;
        } else {
            if (treapNode->right) {
                tmp = treapNode->right;

                RotateLeft(tmp, treapNode);

                treap->root = tmp;
            } else {
                return;
            }
        }
    }

    while (1) {

        if (treapNode->left) {
            if (treapNode->right) {
                if (treapNode->left->priority < treapNode->right->priority) {
                    tmp = treapNode->left;

                    RotateRight(tmp, treapNode);

                } else {
                    tmp = treapNode->right;

                    RotateLeft(tmp, treapNode);
                }
            } else {
                tmp = treapNode->left;

                RotateRight(tmp, treapNode);
            }
        } else {
            if (treapNode->right) {
                tmp = treapNode->right;

                RotateLeft(tmp, treapNode);
            } else {
                break;
            }
        }

    }
}

KeyValuePair Treap_deleteNode(Treap *treap,
                              TreapNode *treapNode,
                              vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    KeyValuePair item = { 0 };

    if (treap && treap->root && treapNode) {

        switch (treap->property) {
        case VDS_MAX_HEAP:
            max_bubble_down(treap, treapNode);
            break;
        case VDS_MIN_HEAP:
            min_bubble_down(treap, treapNode);
            break;
        default:
            tmp_err = VDS_INVALID_ARGS;
            break;
        }

        if (treapNode->parent) {
            if (isLeftNode(treapNode)) {
                treapNode->parent->left = NULL;
            } else {
                treapNode->parent->right = NULL;
            }
        } else {
            treap->root = NULL;
        }

        item = treapNode->item;

        VdsFree(treapNode);

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return item;
}

KeyValuePair Treap_deleteByKey(Treap *treap,
                               void *pKey,
                               vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    KeyValuePair item = { 0 };
    TreapNode *to_delete = Treap_findNode(treap, pKey, &tmp_err);

    if (to_delete) {
        item = Treap_deleteNode(treap, to_delete, err);
    }

    SAVE_ERR(err, tmp_err);

    return item;
}

TreapNode *Treap_findNode(Treap *treap,
                          void *pKey,
                          vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
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
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return curr;
}

void *Treap_findData(Treap *treap,
                     void *pKey,
                     vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
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
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return (curr) ? curr->item.pData : NULL;
}

void Treap_traverse(Treap *treap,
                    vdsTreeTraversal traversal,
                    vdsUserDataFunc callback,
                    vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (callback && treap && treap->root) {
        switch (traversal) {
        case VDS_PRE_ORDER:
            pre_orderTraversal(treap->root, callback);
            break;
        case VDS_IN_ORDER:
            in_orderTraversal(treap->root, callback);
            break;
        case VDS_POST_ORDER:
            post_orderTraversal(treap->root, callback);
            break;
        case VDS_BREADTH_FIRST:
            if (!breadth_firstTraversal(treap->root, callback))
                tmp_err = VDS_MALLOC_FAIL;
            break;
        case VDS_EULER:
            eulerTraversal(treap->root, callback);
            break;
        default:
            tmp_err = VDS_INVALID_ARGS;
            break;
        }
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}

void Treap_destroy(Treap **treap,
                   vdsUserDataFunc freeData,
                   vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (treap && *treap) {

        TreapNode *curr = (*treap)->root, *to_delete;

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

        RandomState_destroy(&(*treap)->rand_gen_state, NULL);
        VdsFree(*treap);
        *treap = NULL;
    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}


//library internal functions to traverse binary tree data structures
//no error checking required

#include "FIFOqueue.h"

void pre_orderTraversal(TreapNode *treapNode, vdsUserDataFunc callback)
{
    if (treapNode) {
        callback((void *)&treapNode->item);
        pre_orderTraversal(treapNode->left, callback);
        pre_orderTraversal(treapNode->right, callback);
    }
}

void in_orderTraversal(TreapNode *treapNode, vdsUserDataFunc callback)
{
    if (treapNode) {
        in_orderTraversal(treapNode->left, callback);
        callback((void *)&treapNode->item);
        in_orderTraversal(treapNode->right, callback);
    }
}

void post_orderTraversal(TreapNode *treapNode, vdsUserDataFunc callback)
{
    if (treapNode) {
        post_orderTraversal(treapNode->left, callback);
        post_orderTraversal(treapNode->right, callback);
        callback((void *)&treapNode->item);
    }
}

int breadth_firstTraversal(TreapNode *treapRoot, vdsUserDataFunc callback)
{
    vdsErrCode err;
    TreapNode *curr;
    FIFOqueue *levelFIFO = FIFO_init(&err);

    if (levelFIFO) {
        FIFO_enqueue(levelFIFO, (void *)treapRoot, &err);

        if (err == VDS_SUCCESS) {

            while (levelFIFO->total_nodes) {
                curr = (TreapNode *)FIFO_dequeue(levelFIFO, NULL);

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

void eulerTraversal(TreapNode *treapNode, vdsUserDataFunc callback)
{
    if (treapNode) {
        callback((void *)&treapNode->item);

        eulerTraversal(treapNode->left, callback);
        callback((void *)&treapNode->item);
        eulerTraversal(treapNode->right, callback);
        callback((void *)&treapNode->item);
    }
}
