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

void printNode(void *p)
{
    LeftistHeapNode *lheapNode = (LeftistHeapNode*)p;

    printf("node %d with npl %u\n", *(int*)lheapNode->pData, lheapNode->npl);
}

void in_orderTraversal(LeftistHeapNode *lheapNode, vdsUserDataFunc callback)
{
    if (lheapNode) {
        in_orderTraversal(lheapNode->left, callback);
        callback((void*)lheapNode);
        in_orderTraversal(lheapNode->right, callback);
    }
}

void pre_orderTraversal(LeftistHeapNode *lheapNode, vdsUserDataFunc callback)
{
    if (lheapNode) {
        callback((void*)lheapNode);
        pre_orderTraversal(lheapNode->left, callback);
        pre_orderTraversal(lheapNode->right, callback);
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
    LeftistHeap *lheap;

    VDS_ERR_FATAL(lheap = LeftistHeap_init(compareInts, VDS_MAX_HEAP, &err), err);

    printf("=== TESTING MAX HEAP ===\n");
    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        VDS_ERR_FATAL(LeftistHeap_push(lheap, &arr[i], &err), err);
        printf("\nInserted %d! PRINTING INORDER\n", arr[i]);
        in_orderTraversal(lheap->root, printNode);

        printf("\nPRINTING PREORDER\n", arr[i]);
        pre_orderTraversal(lheap->root, printNode);
        printf("==================================");
        printf("\n");
    }

    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        int z;
        VDS_ERR_FATAL(z = *(int*)LeftistHeap_pop(lheap, &err), err);
        //printf("popped %d!\n", z);
    }
    printf("\n\n");


    printf("=== TESTING MIN HEAP ===\n");
    lheap->property = VDS_MIN_HEAP;

    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        VDS_ERR_FATAL(LeftistHeap_push(lheap, &arr[i], &err), err);
        printf("Inserted %d!\n", arr[i]);
        in_orderTraversal(lheap->root, printNode);
        printf("\n");
    }

    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        int z;
        VDS_ERR_FATAL(z = *(int*)LeftistHeap_pop(lheap, &err), err);
        printf("%d ", z);
    }
    printf("\n");

    VDS_ERR_FATAL(LeftistHeap_destroy(&lheap, NULL, &err), err);

    return 0;
}
