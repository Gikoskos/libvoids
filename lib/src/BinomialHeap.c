 /********************
 *  BinomialHeap.c
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include <stdlib.h>
#include "BinomialHeap.h"



BinomialHeap *BinomialHeap_init(UserCompareCallback KeyCmp,
                                HeapPropertyType property,
                                EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    BinomialHeap *binheap = NULL;

    if (KeyCmp) {

        switch (property) {
        case EDS_MAX_HEAP:
        case EDS_MIN_HEAP:
            binheap = malloc(sizeof(BinomialHeap));

            if (binheap) {

                binheap->forest = NULL;
                binheap->property = property;
                binheap->KeyCmp = KeyCmp;

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

    return binheap;
}

BinomialTree *BinomialHeap_insert(BinomialHeap *binheap,
                                  void *pData,
                                  void *pKey,
                                  EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    BinomialTree *new_tree = NULL;

    if (binheap && pKey) {

        //if the forest has no binomial tree nodes (if it's empty)
        if (!binheap->forest) {

            //create the new binomial tree root that will hold the user's data
            new_tree = malloc(sizeof(BinomialTree));

            //if malloc succeeded
            if (new_tree) {

                //create a binomial tree of order 0
                new_tree->child = new_tree->sibling = new_tree->parent = NULL;
                new_tree->item.pData = pData;
                new_tree->item.pKey = pKey;
                new_tree->order = 0;

                binheap->forest = new_tree;
            } else
                tmp_err = EDS_MALLOC_FAIL;

        //if there are other trees in the forest, we have to create a new temporary
        //binomial heap that holds just this one binomial tree of order 0, and then merge the two
        } else {

            BinomialHeap *tmp_heap = BinomialHeap_init(binheap->KeyCmp, binheap->property, &tmp_err),
                         *aux_heap = BinomialHeap_init(binheap->KeyCmp, binheap->property, &tmp_err);

            if (tmp_heap && aux_heap) {

                new_tree = BinomialHeap_insert(tmp_heap, pData, pKey, &tmp_err);

                if (new_tree) {
                    //if we're at this point, then the creation of the temporary heap has succeeded.
                    //All that remains, is to merge the new/temporary heap with the user's heap.
                    switch (property) {
                    case EDS_MAX_HEAP:
                        
                        merge_heaps_max(binheap, tmp_heap);
                    case EDS_MIN_HEAP:
                        merge_heaps_min(binheap, tmp_heap);
                        break;
                    default:
                        free(new_tree);
                        free(tmp_heap->forest);
                        free(tmp_heap);
                        tmp_err = EDS_INVALID_ARGS;
                        break;
                    }
                } else {
                    free(tmp_heap);
                    //we don't have to set tmp_err to EDS_MALLOC_FAIL at this point
                    //since we pass it as a parameter to the call to BinomialHeap_insert()
                }
            }
        }

    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return new_tree;
}

void merge_heaps_max(BinomialHeap *binheap1, BinomialHeap *binheap2)
{
    BinomialTree *curr1 = binheap1->forest,
                 *curr2 = binheap2->forest,
                 *merged;
    int cmp_res;

    merged = (
    while (curr1 && curr2) {

        if (curr1->order == curr2->order) {

            //comparison function is the same on both heaps, because the keys are of the same type
            //on heaps that are merged together
            cmp_res = binheap1->KeyCmp(curr1->item.pKey, curr2->item.pKey);

            if (cmp_res > 0) {
                curr2->sibling = curr1->child;
                curr1->child = curr2;
                curr2->parent = curr1;
            } else {
                
            }
        }
    }
}

void merge_heaps_min(BinomialHeap *merged, BinomialHeap *to_merge)
{
    BinomialTree *curr_1 = treelist_1->head,
                 *curr_2 = treelist_2->head;

    while (curr_1 && curr_2) {
        if (curr_1->tree->order == curr_2->tree->order) {
            
        }
    }
}

KeyValuePair BinomialHeap_pop(BinomialHeap *binheap,
                              EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
}

KeyValuePair BinomialHeap_getTop(BinomialHeap *binheap,
                                 EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
}

KeyValuePair BinomialHeap_replaceKey(BinomialHeap *binheap,
                                     BinomialTree *tree,
                                     void *pKey,
                                     EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
}

void BinomialHeap_destroy(BinomialHeap **binheap,
                          UserDataCallback freeData,
                          EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
}
