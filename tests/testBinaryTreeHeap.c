#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <voids.h>


#define VDS_ERR_FATAL(func, err) \
do { \
    func; \
    if (err != VDS_SUCCESS) { \
        printf("Function call \"%s\" failed with error \"%s\"\n", #func, VdsErrString(err)); \
        return 1; \
    } \
} while (0)

void printIntData(void *param)
{
    printf("node %d\n", *(int*)param);
}

void in_orderTraversal(BTHeapNode *bheapNode, vdsUserDataFunc callback)
{
    if (bheapNode) {
        in_orderTraversal(bheapNode->left, callback);
        callback(bheapNode->pData);
        in_orderTraversal(bheapNode->right, callback);
    }
}

void pre_orderTraversal(BTHeapNode *bheapNode, vdsUserDataFunc callback)
{
    if (bheapNode) {
        callback(bheapNode->pData);
        pre_orderTraversal(bheapNode->left, callback);
        pre_orderTraversal(bheapNode->right, callback);
    }
}


int compareInts(const void *key1, const void *key2)
{
    return *(int*)key1 - *(int*)key2;
}

int main(int argc, char *argv[])
{
    int arr[] = {4 , 51, 6, 222, 43, 40, 4, 11, 1, 55, 10, 3, 666, 89, 99, 7, 12};
    vdsErrCode err;
    BTHeap *bheap;

    VDS_ERR_FATAL(bheap = BTHeap_init(compareInts, VDS_MAX_HEAP, &err), err);

    printf("=== TESTING MAX HEAP ===\n");
    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        VDS_ERR_FATAL(BTHeap_push(bheap, &arr[i], &err), err);
        printf("\nInserted %d! PRINTING INORDER\n", arr[i]);
        in_orderTraversal(bheap->root, printIntData);

        printf("\nPRINTING PREORDER\n", arr[i]);
        pre_orderTraversal(bheap->root, printIntData);
        printf("==================================");
        printf("\n");
    }

    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        int z;
        VDS_ERR_FATAL(z = *(int*)BTHeap_pop(bheap, &err), err);
        //printf("popped %d!\n", z);
    }
    printf("\n\n");


    printf("=== TESTING MIN HEAP ===\n");
    bheap->property = VDS_MIN_HEAP;

    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        VDS_ERR_FATAL(BTHeap_push(bheap, &arr[i], &err), err);
        printf("Inserted %d!\n", arr[i]);
        in_orderTraversal(bheap->root, printIntData);
        printf("\n");
    }

    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        int z;
        VDS_ERR_FATAL(z = *(int*)BTHeap_pop(bheap, &err), err);
        printf("%d ", z);
    }
    printf("\n");

    VDS_ERR_FATAL(BTHeap_destroy(&bheap, NULL, &err), err);

    return 0;
}
