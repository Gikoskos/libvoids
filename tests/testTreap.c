#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <voids.h>


#define VDS_ERR_FATAL(func, err) \
    func; \
    if (err != VDS_SUCCESS) { \
        printf("Function call \"%s\" failed with error \"%s\"\n",  #func, VdsErrString(err)); \
        return 1; \
    }

void printIntData(void *param)
{
    KeyValuePair x = *(KeyValuePair*)param;
    /*TreapNode *n = (TreapNode*)param;

    printf("node %d has priority %u\n", *(int*)n->item.pKey, n->priority);*/
    printf("node has key %d\n", *(int*)x.pKey);
}

int compareInts(const void *key1, const void *key2)
{
    return *(int*)key1 - *(int*)key2;
}

int main(int argc, char *argv[])
{
    int arr[] = {4 , 51, 6, 222, 43, 40, 4, 11, 1};
    vdsErrCode err;
    Treap *treap;

    VDS_ERR_FATAL(treap = Treap_init(compareInts, VDS_MAX_HEAP, 0, &err), err);

    printf("=== TESTING MAX HEAP ===\n");
    printf("=== INSERTIONS ===\n");
    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        Treap_insert(treap, &arr[i], NULL, &err);
        printf("Inserted %d!\n", arr[i]);
        Treap_traverse(treap, VDS_IN_ORDER, printIntData, NULL);
        printf("\n");
    }

    printf("\n=== DELETIONS ===\n");
    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        KeyValuePair z;
        z = Treap_deleteByKey(treap, (void*)&arr[i], &err);
        if (z.pKey) {
            printf("removed %d from the treap\n", *(int*)z.pKey);
            printf("In-order traversal of the treap!\n");
            Treap_traverse(treap, VDS_IN_ORDER, printIntData, NULL);
            putchar('\n');
        }
    }
    printf("\n\n");


    printf("=== TESTING MIN HEAP ===\n");
    treap->property = VDS_MIN_HEAP;

    printf("=== INSERTIONS ===\n");
    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        Treap_insert(treap, &arr[i], NULL, &err);
        printf("Inserted %d!\n", arr[i]);
        Treap_traverse(treap, VDS_IN_ORDER, printIntData, NULL);
        printf("\n");
    }

    printf("\n=== DELETIONS ===\n");
    for (size_t i = 0; i < sizeof arr / sizeof *arr; i++) {
        KeyValuePair z;
        z = Treap_deleteByKey(treap, (void*)&arr[i], &err);
        if (z.pKey) {
            printf("removed %d from the treap\n", *(int*)z.pKey);
            printf("In-order traversal of the treap!\n");
            Treap_traverse(treap, VDS_IN_ORDER, printIntData, NULL);
            putchar('\n');
        }
    }
    printf("\n");

    VDS_ERR_FATAL(Treap_destroy(&treap, NULL, &err), err);

    return 0;
}
