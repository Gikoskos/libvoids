#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <EduDS.h>

#define ARRAY_LEN(x) (sizeof(x) / sizeof(*arr))

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

/*BinomialHeap *BinomialHeap_init(UserCompareCallback KeyCmp,
                                HeapPropertyType property,
                                EdsErrCode *err)

BinomialTree *BinomialHeap_insert(BinomialHeap *binheap,
                                  void *pData,
                                  void *pKey,
                                  EdsErrCode *err)
KeyValuePair BinomialHeap_pop(BinomialHeap *binheap,
                              EdsErrCode *err)

KeyValuePair BinomialHeap_getTop(BinomialHeap *binheap,
                                 EdsErrCode *err)

void *BinomialHeap_replaceKey(BinomialHeap *binheap,
                              BinomialTree *tree,
                              void *pNewKey,
                              EdsErrCode *err)

void BinomialHeap_destroy(BinomialHeap **binheap,
                          UserDataCallback freeData,
                          EdsErrCode *err)*/

int main(int argc, char *argv[])
{
    int arr[] = {4 , 51, 6, 222, 43, 40, 4, 11, 1};
    EdsErrCode err;
    BinomialHeap *binheap;

    EduDS_ERR_FATAL(binheap = BinomialHeap_init(compareInts, EDS_MAX_HEAP, &err), err);

    printf("=== TESTING MAX HEAP ===\n");
    printf("\n=== TESTING INSERTIONS ===\n");
    for (size_t i = 0; i < ARRAY_LEN(arr); i++) {
        EduDS_ERR_FATAL(BinomialHeap_push(binheap, NULL, &arr[i], &err), err);
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
    printf("\n\n");


    /*printf("=== TESTING MIN HEAP ===\n");
    binheap->property = EDS_MIN_HEAP;

    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        EduDS_ERR_FATAL(BinaryHeap_push(binheap, &arr[i], &err), err);
        printf("Inserted %d!\n", arr[i]);
        in_orderTraversal(binheap->root, printIntData);
        printf("\n");
    }

    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        int z;
        EduDS_ERR_FATAL(z = *(int*)BinaryHeap_pop(binheap, &err), err);
        printf("%d ", z);
    }
    printf("\n");*/

    EduDS_ERR_FATAL(BinomialHeap_destroy(&binheap, NULL, &err), err);

    return 0;
}
