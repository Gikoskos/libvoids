 /********************
 *  ArrayHeap.c
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#include "MemoryAllocation.h"
#include "ArrayHeap.h"


static void fix_push_max(ArrayHeap *heap);
static void fix_push_min(ArrayHeap *heap);
static void fix_pop_max(ArrayHeap *heap);
static void fix_pop_min(ArrayHeap *heap);


ArrayHeap *ArrayHeap_init(UserCompareCallback DataCmp,
                          HeapPropertyType property,
                          size_t size,
                          EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    ArrayHeap *arrheap = NULL;

    if (DataCmp && size > 0) {

        switch (property) {
        case EDS_MAX_HEAP:
        case EDS_MIN_HEAP:
            arrheap = EdsMalloc(sizeof(ArrayHeap));

            if (arrheap) {

                arrheap->array = EdsMalloc(sizeof(void*) * size);

                if (arrheap->array) {

                    arrheap->property = property;
                    arrheap->DataCmp = DataCmp;
                    arrheap->size = size;
                    arrheap->idx = 0;

                } else
                    tmp_err = EDS_MALLOC_FAIL;

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

    return arrheap;
}

void *ArrayHeap_push(ArrayHeap *arrheap,
                     void *pData,
                     EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    void *pRet = NULL;

    if (arrheap && pData && (arrheap->idx < arrheap->size)) {

        arrheap->array[arrheap->idx] = pRet = pData;

        switch (arrheap->property) {
        case EDS_MAX_HEAP:
            fix_push_max(arrheap);
            break;
        case EDS_MIN_HEAP:
            fix_push_min(arrheap);
            break;
        default:
            tmp_err = EDS_INVALID_ARGS;
            break;
        }

        arrheap->idx++;

    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pRet;
}

void fix_push_max(ArrayHeap *heap)
{
    size_t curr = heap->idx, parent;
    int cmp_res;
    void *pTmp;

    while (curr) {
        parent = ( !(curr % 2) ) ? ( curr/2 - 1 ) : ( curr/2 );

        cmp_res = heap->DataCmp(heap->array[curr], heap->array[parent]);

        if (cmp_res > 0) {
            pTmp = heap->array[curr];
            heap->array[curr] = heap->array[parent];
            heap->array[parent] = pTmp;
        } else
            break;

        curr = parent;
    }
}

void fix_push_min(ArrayHeap *heap)
{
    size_t curr = heap->idx, parent;
    int cmp_res;
    void *pTmp;

    while (curr) {
        parent = ( !(curr%2) ) ? ( curr/2 - 1 ) : ( curr/2 );

        cmp_res = heap->DataCmp(heap->array[curr], heap->array[parent]);

        if (cmp_res < 0) {
            pTmp = heap->array[curr];
            heap->array[curr] = heap->array[parent];
            heap->array[parent] = pTmp;
        } else
            break;

        curr = parent;
    }
}

void *ArrayHeap_pop(ArrayHeap *arrheap,
                    EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;
    void *pDeleted = NULL;

    if (arrheap && arrheap->idx) {

        arrheap->idx--;

        //save the data of the deleted node
        pDeleted = arrheap->array[0];
        arrheap->array[0] = arrheap->array[arrheap->idx];

        //if that was the last node on the heap array
        //we don't need to fix the node priority
        if (arrheap->idx) {

            switch (arrheap->property) {
            case EDS_MAX_HEAP:
                fix_pop_max(arrheap);
                break;
            case EDS_MIN_HEAP:
                fix_pop_min(arrheap);
                break;
            default:
                tmp_err = EDS_INVALID_ARGS;
                break;
            }

        }

    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);

    return pDeleted;
}

void fix_pop_max(ArrayHeap *heap)
{
    size_t curr = 0, child1, child2, max_child;
    int cmp_res;
    void *pTmp;

    while (curr < heap->idx) {
        child2 = 2 * curr + 2;
        child1 = 2 * curr + 1;

        //if the right child exists, then both children exist
        //since the heap can be visualized as a complete binary tree
        if (child2 < heap->idx) {
            //first compare the two children to get the biggest
            cmp_res = heap->DataCmp(heap->array[child1], heap->array[child2]);

            max_child = (cmp_res > 0) ? child1 : child2;

            //compare the biggest child with the parent
            cmp_res = heap->DataCmp(heap->array[max_child], heap->array[curr]);
            if (cmp_res > 0) {
                pTmp = heap->array[max_child];
                heap->array[max_child] = heap->array[curr];
                heap->array[curr] = pTmp;
                curr = max_child;
                continue;
            }
        //else there's only one child, the left, so we compare with that
        } else if (child1 < heap->idx) {
            cmp_res = heap->DataCmp(heap->array[child1], heap->array[curr]);

            //if the parent is smaller than the child, then we swap them
            //to maintain the maximum heap order
            if (cmp_res > 0) {
                pTmp = heap->array[child1];
                heap->array[child1] = heap->array[curr];
                heap->array[curr] = pTmp;
                curr = child1;
                continue;
            }
        }

        break;
    }
}

void fix_pop_min(ArrayHeap *heap)
{
    size_t curr = 0, child1, child2, min_child;
    int cmp_res;
    void *pTmp;

    while (curr < heap->idx) {
        child2 = 2 * curr + 2;
        child1 = 2 * curr + 1;

        //if the right child exists, then both children exist
        //since the heap can be visualized as a complete binary tree
        if (child2 < heap->idx) {
            //first compare the two children to get the smallest
            cmp_res = heap->DataCmp(heap->array[child1], heap->array[child2]);

            min_child = (cmp_res < 0) ? child1 : child2;

            //compare the smallest child with the parent
            cmp_res = heap->DataCmp(heap->array[min_child], heap->array[curr]);
            if (cmp_res < 0) {
                //if the parent is bigger than the child, then we swap them
                //to maintain the minimum heap order
                pTmp = heap->array[min_child];
                heap->array[min_child] = heap->array[curr];
                heap->array[curr] = pTmp;
                curr = min_child;
                continue;
            }
        //else there's only one child, the left, so we compare with that
        } else if (child1 < heap->idx) {
            cmp_res = heap->DataCmp(heap->array[child1], heap->array[curr]);

            if (cmp_res < 0) {
                pTmp = heap->array[child1];
                heap->array[child1] = heap->array[curr];
                heap->array[curr] = pTmp;
                curr = child1;
                continue;
            }
        }

        break;
    }
}

void ArrayHeap_destroy(ArrayHeap **arrheap,
                       UserDataCallback freeData,
                       EdsErrCode *err)
{
    EdsErrCode tmp_err = EDS_SUCCESS;

    if (arrheap && *arrheap) {

        if (freeData) {
            for (size_t i = 0; i < (*arrheap)->idx; i++)
                freeData((*arrheap)->array[i]);
        }

        EdsFree((*arrheap)->array);
        EdsFree(*arrheap);
        *arrheap = NULL;
    } else
        tmp_err = EDS_INVALID_ARGS;

    SAVE_ERR(err, tmp_err);
}
