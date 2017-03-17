#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <EduDS.h>


#define EduDS_ERR_FATAL(func, err) \
    func; \
    if (err != EDS_SUCCESS) { \
        printf("Function call \"%s\" failed with error \"%s\"\n", #func, EdsErrString(err)); \
        return 1; \
    }

void printIntData(void *param)
{
    printf("node %d\n", *(int*)param);
}

void in_orderTraversal(BinaryHeapNode *bheapNode, UserDataCallback callback)
{
    if (bheapNode) {
        in_orderTraversal(bheapNode->left, callback);
        callback(bheapNode->pData);
        in_orderTraversal(bheapNode->right, callback);
    }
}


int compareInts(const void *key1, const void *key2)
{
    return *(int*)key1 - *(int*)key2;
}

int main(int argc, char *argv[])
{
    int arr[] = {4 , 51, 6, 222, 43, 40, 4, 11, 1};
    EdsErrCode err;
    BinaryHeap *bheap;

    EduDS_ERR_FATAL(bheap = BinaryHeap_init(compareInts, EDS_MAX_HEAP, &err), err);

    printf("=== TESTING MAX HEAP ===\n");
    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        EduDS_ERR_FATAL(BinaryHeap_push(bheap, &arr[i], &err), err);
        printf("Inserted %d!\n", arr[i]);
        in_orderTraversal(bheap->root, printIntData);
        printf("\n");
    }

    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        int z;
        EduDS_ERR_FATAL(z = *(int*)BinaryHeap_pop(bheap, &err), err);
        printf("%d ", z);
    }
    printf("\n\n");


    printf("=== TESTING MIN HEAP ===\n");
    bheap->property = EDS_MIN_HEAP;

    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        EduDS_ERR_FATAL(BinaryHeap_push(bheap, &arr[i], &err), err);
        printf("Inserted %d!\n", arr[i]);
        in_orderTraversal(bheap->root, printIntData);
        printf("\n");
    }

    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        int z;
        EduDS_ERR_FATAL(z = *(int*)BinaryHeap_pop(bheap, &err), err);
        printf("%d ", z);
    }
    printf("\n");

    EduDS_ERR_FATAL(BinaryHeap_destroy(&bheap, NULL, &err), err);

    return 0;
}
