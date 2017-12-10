 /********************
 *  BinomialHeap.c
 *
 * This file is part of libvoids which is licensed under the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "MemoryAllocation.h"
#include "BinomialHeap.h"


static BinomialTree *merge_forests(BinomialTree *forest1, BinomialTree *forest2);
static BinomialTree *merge_heaps_max(BinomialHeap *binheap1, BinomialTree *forest2);
static BinomialTree *merge_heaps_min(BinomialHeap *binheap1, BinomialTree *forest2);
static BinomialTree *make_children_forest(BinomialTree *root);
static void destroy_recur_user(BinomialTree *curr, vdsUserDataFunc freeData);
static void destroy_recur_plain(BinomialTree *curr);


BinomialHeap *BinomialHeap_init(vdsUserCompareFunc KeyCmp,
                                vdsHeapProperty property,
                                vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    BinomialHeap *binheap = NULL;

    if (KeyCmp) {

        switch (property) {
        case VDS_MAX_HEAP:
        case VDS_MIN_HEAP:
            binheap = VdsMalloc(sizeof(BinomialHeap));

            if (binheap) {

                binheap->forest = NULL;
                binheap->property = property;
                binheap->KeyCmp = KeyCmp;

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

    return binheap;
}

BinomialTree *BinomialHeap_push(BinomialHeap *binheap,
                                void *pData,
                                void *pKey,
                                vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    BinomialTree *new_tree = NULL;

    if (binheap && pKey) {

        //create the new binomial tree root that will hold the user's data
        new_tree = VdsMalloc(sizeof(BinomialTree));

        //if VdsMalloc succeeded
        if (new_tree) {

            //create a binomial tree of order 0 that holds the new item
            new_tree->child = new_tree->sibling = new_tree->parent = NULL;
            new_tree->item.pData = pData;
            new_tree->item.pKey = pKey;
            new_tree->order = 0;

            //if the forest has no binomial tree nodes (if it's empty)
            if (!binheap->forest) {

                binheap->forest = new_tree;

            //if there are other trees in the forest, we have to create a new temporary
            //binomial heap that holds just this one binomial tree of order 0, and then merge the two
            } else {

                //if we're at this point, then the creation of the temporary heap has succeeded.
                //All that remains, is to merge the new/temporary heap with the user's heap.
                switch (binheap->property) {
                case VDS_MAX_HEAP:
                    binheap->forest = merge_heaps_max(binheap, new_tree);
                    break;
                case VDS_MIN_HEAP:
                    binheap->forest = merge_heaps_min(binheap, new_tree);
                    break;
                default:
                    tmp_err = VDS_INVALID_ARGS;
                    break;
                }
            }

        } else
            tmp_err = VDS_MALLOC_FAIL;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_tree;
}

BinomialTree *merge_forests(BinomialTree *forest1, BinomialTree *forest2)
{
    //handle edge cases
    if (!forest1) {
        return forest2;
    } if (!forest2) {
        return forest1;
    }

    BinomialTree *curr1 = forest1,
                 *curr2 = forest2,
                 *merged_root, *merged_curr;

    if (curr1->order > curr2->order) {
        merged_root = curr2;
        curr2 = curr2->sibling;
    } else {
        merged_root = curr1;
        curr1 = curr1->sibling;
    }

    merged_curr = merged_root;

    while (merged_curr) {

        if (curr1 && curr2) {

            if (curr1->order > curr2->order) {

                merged_curr->sibling = curr2;
                curr2 = curr2->sibling;

            } else {

                merged_curr->sibling = curr1;
                curr1 = curr1->sibling;

            }

        } else {
            if (curr1) {

                merged_curr->sibling = curr1;
                break;

            } else if (curr2) {

                merged_curr->sibling = curr2;
                break;

            }
        }

        merged_curr = merged_curr->sibling;
    }

    return merged_root;
}

BinomialTree *merge_heaps_max(BinomialHeap *binheap1, BinomialTree *forest2)
{
    if (!forest2)
        return binheap1->forest;

    BinomialTree *merged_curr, *merged_root, *merged_prev, *tmp_tree;

    merged_curr = merged_root = merge_forests(binheap1->forest, forest2);
    merged_prev = NULL;

    if (!merged_root)
        return NULL;

    while (merged_curr->sibling) {

        //if merged_curr points to the first of 3 roots in a row, who are of the same order,
        //or if merged_curr and its sibling are of different order, we simply move the
        //pointers one position to the right
        if ( merged_curr->sibling->order != merged_curr->order ||
             (merged_curr->sibling->sibling && (merged_curr->order == merged_curr->sibling->sibling->order)) ) {

            merged_prev = merged_curr;
            merged_curr = merged_curr->sibling;

        //else if merged_curr points to a root that is of the same order as its sibling
        } else {

            //comparison function is the same on both heaps, because the keys are of the same type
            //on heaps that are merged together
            //if the key of the current node we're pointing at, has highest priority than the key of
            //its sibling, the sibling becomes a child of the current node
            if (binheap1->KeyCmp(merged_curr->item.pKey, merged_curr->sibling->item.pKey) > 0) {
                //order of operations is very important here!!
                tmp_tree = merged_curr->sibling;
                merged_curr->sibling = tmp_tree->sibling;

                tmp_tree->sibling = merged_curr->child;
                merged_curr->child = tmp_tree;
                tmp_tree->parent = merged_curr;

                merged_curr->order++;

            } else {

                if (merged_prev)
                    merged_prev->sibling = merged_curr->sibling;
                else
                    //if we're comparing the root of the forest
                    //with its sibling, and the sibling is bigger,
                    //then the sibling becomes the new root that has the
                    //old root as a child
                    merged_root = merged_curr->sibling;

                tmp_tree = merged_curr;
                merged_curr = merged_curr->sibling;

                tmp_tree->sibling = merged_curr->child;
                merged_curr->child = tmp_tree;
                tmp_tree->parent = merged_curr;

                merged_curr->order++;

            }
        }
    }

    return merged_root;
}

BinomialTree *merge_heaps_min(BinomialHeap *binheap1, BinomialTree *forest2)
{
    BinomialTree *merged_curr, *merged_root, *merged_prev, *tmp_tree;

    merged_curr = merged_root = merge_forests(binheap1->forest, forest2);
    merged_prev = NULL;

    if (!merged_root)
        return NULL;

    while (merged_curr->sibling) {

        //if merged_curr points to the first of 3 roots in a row, who are of the same order,
        //or if merged_curr and its sibling are of different order, we simply move the
        //pointers one position to the right
        if ( (merged_curr->sibling->order != merged_curr->order) ||
             (merged_curr->sibling->sibling && (merged_curr->order == merged_curr->sibling->sibling->order)) ) {

            merged_prev = merged_curr;
            merged_curr = merged_curr->sibling;

        //else if merged_curr points to a root that is of the same order as its sibling
        } else {

            //comparison function is the same on both heaps, because the keys are of the same type
            //on heaps that are merged together
            if (binheap1->KeyCmp(merged_curr->item.pKey, merged_curr->sibling->item.pKey) < 0) {
                //order of operations is very important here!!
                tmp_tree = merged_curr->sibling;
                merged_curr->sibling = tmp_tree->sibling;

                tmp_tree->sibling = merged_curr->child;
                merged_curr->child = tmp_tree;
                tmp_tree->parent = merged_curr;

                merged_curr->order++;

            } else {

                if (merged_prev)
                    merged_prev->sibling = merged_curr->sibling;
                else
                    merged_root = merged_curr->sibling;

                tmp_tree = merged_curr;
                merged_curr = merged_curr->sibling;

                tmp_tree->sibling = merged_curr->child;
                merged_curr->child = tmp_tree;
                tmp_tree->parent = merged_curr;

                merged_curr->order++;

            }
        }
    }

    return merged_root;
}

BinomialTree *make_children_forest(BinomialTree *root)
{
    //points to the head of the list at every loop
    BinomialTree *list_head = root->child;

    if (list_head) {

        //points to the current child node of 'root' we are examining at every iteration
        BinomialTree *curr = list_head->sibling;
        //temporary pointer to tree we use to swap the trees
        BinomialTree *tmp;

        list_head->parent = list_head->sibling = NULL;

        while (curr) {

            //we do this first, because curr's siblings change
            tmp = curr;
            curr = curr->sibling;

            //insert each child node of 'root' on the head of the list
            //so that they are sorted by order
            tmp->sibling = list_head;
            list_head = tmp;
            list_head->parent = NULL;
        }

    }

    return list_head;
}

KeyValuePair BinomialHeap_pop(BinomialHeap *binheap,
                              vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    KeyValuePair popped = { 0 };

    if (binheap && binheap->forest) {

        BinomialTree *top_tree, *prev_top = NULL;
        BinomialTree *curr_root = binheap->forest->sibling, *prev_root;


        prev_root = top_tree = binheap->forest;

        switch (binheap->property) {
        case VDS_MAX_HEAP:

            while (curr_root) {

                if (binheap->KeyCmp(top_tree->item.pKey, curr_root->item.pKey) < 0) {
                    prev_top = prev_root;
                    top_tree = curr_root;
                }

                prev_root = curr_root;
                curr_root = curr_root->sibling;
            }

            //don't forget to copy the deleted item
            popped = top_tree->item;

            //remove the top root from the list
            if (prev_top)
                prev_top->sibling = top_tree->sibling;
            else
                binheap->forest = top_tree->sibling;

            binheap->forest = merge_heaps_max(binheap, make_children_forest(top_tree));

            VdsFree(top_tree);
            break;
        case VDS_MIN_HEAP:

            while (curr_root) {

                if (binheap->KeyCmp(top_tree->item.pKey, curr_root->item.pKey) > 0) {
                    prev_top = prev_root;
                    top_tree = curr_root;
                }

                prev_root = curr_root;
                curr_root = curr_root->sibling;
            }

            //don't forget to copy the deleted item
            popped = top_tree->item;

            //remove the top root from the list
            if (prev_top)
                prev_top->sibling = top_tree->sibling;
            else
                binheap->forest = top_tree->sibling;

            binheap->forest = merge_heaps_min(binheap, make_children_forest(top_tree));

            VdsFree(top_tree);
        default:
            tmp_err = VDS_INVALID_ARGS;
            break;
        }

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return popped;
}

KeyValuePair BinomialHeap_getTop(BinomialHeap *binheap,
                                 vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    KeyValuePair top = { 0 };

    if (binheap && binheap->forest) {

        BinomialTree *top_tree = binheap->forest;

        switch (binheap->property) {
        case VDS_MAX_HEAP:

            for (BinomialTree *curr_root = binheap->forest->sibling; curr_root; curr_root = curr_root->sibling)
                if (binheap->KeyCmp(top_tree->item.pKey, curr_root->item.pKey) < 0)
                    top_tree = curr_root;

            top = top_tree->item;
            break;
        case VDS_MIN_HEAP:

            for (BinomialTree *curr_root = binheap->forest->sibling; curr_root; curr_root = curr_root->sibling)
                if (binheap->KeyCmp(top_tree->item.pKey, curr_root->item.pKey) > 0)
                    top_tree = curr_root;

            top = top_tree->item;
            break;
        default:
            tmp_err = VDS_INVALID_ARGS;
            break;
        }

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return top;
}

void *BinomialHeap_replaceKey(BinomialHeap *binheap,
                              BinomialTree *tree,
                              void *pNewKey,
                              vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;
    void *pOldKey = NULL;

    if (binheap && tree && pNewKey) {

        switch (binheap->property) {
        case VDS_MAX_HEAP:

            if (binheap->KeyCmp(pNewKey, tree->item.pKey) > 0) {

                KeyValuePair tmp;
                BinomialTree *curr = tree->parent;

                pOldKey = tree->item.pKey;
                tree->item.pKey = pNewKey;

                while (curr) {

                    if (binheap->KeyCmp(tree->item.pKey, curr->item.pKey) > 0) {
                        tmp = tree->item;
                        tree->item = curr->item;
                        curr->item = tmp;
                    } else
                        break;

                    tree = tree->parent;
                    curr = curr->parent;
                }

            } else
                tmp_err = VDS_INVALID_ARGS;

            break;
        case VDS_MIN_HEAP:

            if (binheap->KeyCmp(pNewKey, tree->item.pKey) < 0) {

                KeyValuePair tmp;
                BinomialTree *curr = tree->parent;

                pOldKey = tree->item.pKey;
                tree->item.pKey = pNewKey;

                while (curr) {

                    if (binheap->KeyCmp(tree->item.pKey, curr->item.pKey) < 0) {
                        tmp = tree->item;
                        tree->item = curr->item;
                        curr->item = tmp;
                    } else
                        break;

                    tree = tree->parent;
                    curr = curr->parent;
                }

            } else
                tmp_err = VDS_INVALID_ARGS;

            break;
        default:
            tmp_err = VDS_INVALID_ARGS;
            break;
        }

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pOldKey;
}

void destroy_recur_user(BinomialTree *curr, vdsUserDataFunc freeData)
{
    if (curr) {
        destroy_recur_user(curr->sibling, freeData);
        destroy_recur_user(curr->child, freeData);
        if (curr->parent) {
            if (curr->parent->child == curr)
                curr->parent->child = NULL;
            else
                curr->parent->sibling = NULL;
        }

        freeData((void *)&curr->item);

        VdsFree(curr);
    }
}

void destroy_recur_plain(BinomialTree *curr)
{
    if (curr) {
        destroy_recur_plain(curr->sibling);
        destroy_recur_plain(curr->child);
        if (curr->parent) {
            if (curr->parent->child == curr)
                curr->parent->child = NULL;
            else
                curr->parent->sibling = NULL;
        }

        VdsFree(curr);
    }
}

void BinomialHeap_destroy(BinomialHeap **binheap,
                          vdsUserDataFunc freeData,
                          vdsErrCode *err)
{
    vdsErrCode tmp_err = VDS_SUCCESS;

    if (binheap && *binheap) {

        if (freeData)
            destroy_recur_user((*binheap)->forest, freeData);
        else
            destroy_recur_plain((*binheap)->forest);

        VdsFree(*binheap);
        *binheap = NULL;

    } else
        tmp_err = VDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
