#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <voids.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof(*arr))

#define VDS_ERR_FATAL(func, err) \
    func; \
    if (err != VDS_SUCCESS) { \
        printf("Function call \"%s\" failed with error \"%s\"\n", #func, VdsErrString(err)); \
        return 1; \
    }

void printIntData(void *param)
{
    printf("node %d\n", *(int*)param);
}

void printBinomialHeap(BinomialHeap *bheap)
{
    BinomialTree *curr_root = bheap->forest, *curr_tree, *curr_node, *tmp;

    while (curr_root) {

        curr_tree = curr_root->child;
        printf("Printing children of tree with (key = %d, order = %u)\n", *(int*)curr_root->item.pKey, curr_root->order);

        while (curr_tree) {

            curr_node = curr_tree;

            while (curr_node) {

                printf("(key = %d) -> ", *(int*)curr_node->item.pKey);
                curr_node = curr_node->sibling;
            }

            printf("Null\n");
            curr_tree = curr_tree->child;
        }

        curr_root = curr_root->sibling;
    }

}

int compareInts(const void *key1, const void *key2)
{
    return *(int*)key1 - *(int*)key2;
}

int main(int argc, char *argv[])
{
#define REPLACED_KEY  7

    int arr[] = {4 , 51, 6, 222, 43, 40, 4, 11, 1};
    vdsErrCode err;
    BinomialHeap *binheap;
    BinomialTree *tree_node; //i'm storing a node here to test replaceKey

    VDS_ERR_FATAL(binheap = BinomialHeap_init(compareInts, VDS_MAX_HEAP, &err), err);

    printf("=== TESTING MAX HEAP ===\n");
    printf("\n=== TESTING INSERTIONS ===\n");
    for (size_t i = 0; i < ARRAY_LEN(arr); i++) {
        if (i == REPLACED_KEY) {
            VDS_ERR_FATAL(tree_node = BinomialHeap_push(binheap, NULL, &arr[i], &err), err);
        } else {
            VDS_ERR_FATAL(BinomialHeap_push(binheap, NULL, &arr[i], &err), err);
        }
        printf("Inserted %d!\n", arr[i]);
        printBinomialHeap(binheap);
        printf("\n");
    }

    printf("\n=== TESTING DECREASE KEY ===\n");
    int new_key = 555;
    VDS_ERR_FATAL(BinomialHeap_replaceKey(binheap, tree_node, (void*)&new_key, &err), err);

    printf("Replaced %d with %d!\n", arr[REPLACED_KEY], new_key);
    printBinomialHeap(binheap);
    printf("\n");

    /*printf("\n=== TESTING DELETIONS ===\n");
    for (size_t i = 0; i < ARRAY_LEN(arr); i++) {
        KeyValuePair tmp;
        tmp = BinomialHeap_pop(binheap, &err);

        if (tmp.pKey) {
            printf("\nPopped %d!\n", *(int*)tmp.pKey);
            printBinomialHeap(binheap);
        }
    }
    printf("\n\n");


    printf("=== TESTING MIN HEAP ===\n");
    binheap->property = VDS_MIN_HEAP;

    printf("\n=== TESTING INSERTIONS ===\n");
    for (size_t i = 0; i < ARRAY_LEN(arr); i++) {
        VDS_ERR_FATAL(BinomialHeap_push(binheap, NULL, &arr[i], &err), err);
        printf("Inserted %d!\n", arr[i]);
        printBinomialHeap(binheap);
        printf("\n");
    }

    printf("\n=== TESTING DELETIONS ===\n");
    for (size_t i = 0; i < ARRAY_LEN(arr); i++) {
        KeyValuePair tmp;
        tmp = BinomialHeap_pop(binheap, &err);

        if (tmp.pKey) {
            printf("\nPopped %d!\n", *(int*)tmp.pKey);
            printBinomialHeap(binheap);
        }
    }
    printf("\n\n");*/

    VDS_ERR_FATAL(BinomialHeap_destroy(&binheap, NULL, &err), err);

    return 0;
}
