#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <EduDS.h>

void printIntData(void *param)
{
    KeyValuePair *item = (KeyValuePair *)param;

    printf("node %d has data %d\n", *(int*)item->pKey, *(int*)item->pData);
}

int *newRandInt(int range)
{
    int *p = malloc(sizeof(int));

    if (range) {
        *p = rand()%range + 1;        
    } else {
        *p = rand();
    }

    return p;
}

int compareInts(const void *key1, const void *key2)
{
    return *(int*)key1 - *(int*)key2;
}

void freeKeyValuePair(void *param)
{
    KeyValuePair *item = (KeyValuePair *)param;

    free(item->pKey);
    free(item->pData);
}

int main(int argc, char *argv[])
{
    BSTree *bst = BSTree_init(compareInts);

    srand(time(NULL));

    //trying to add 10 nodes to a binary search tree
    //with pseudorandomly generated keys and data
    printf("\n----STARTING INSERTIONS----\n");
    for (int i = 0; i < 10; i++) {

        int *new_key = newRandInt(100);
        int *new_data = newRandInt(0);

        printf("Trying to insert new node with key %d and data %d!\n", *new_key, *new_data);

        if (BSTree_insert(bst, (void*)new_data, (void*)new_key)) {
            printf("Node was successfully inserted!\n");
            printf("in-order traversal (the node numbers should be in ascending order):\n");
            BSTree_traverse(bst, IN_ORDER, printIntData);
        } else {
            printf("Node insertion failed!\n\n");
            free(new_key);
            free(new_data);
        }
    }

    printf("\n----PRINTING BS TREE BEFORE STARTING TO DELETE ELEMENTS----\n");
    //testing traversals
    printf("in-order traversal (the node numbers should be in ascending order):\n");
    BSTree_traverse(bst, IN_ORDER, printIntData);

    printf("\npre-order traversal:\n");
    BSTree_traverse(bst, PRE_ORDER, printIntData);

    printf("\npost-order traversal:\n");
    BSTree_traverse(bst, POST_ORDER, printIntData);

    printf("\nbreadth-first traversal:\n");
    BSTree_traverse(bst, BREADTH_FIRST, printIntData);

    printf("\neuler traversal:\n");
    BSTree_traverse(bst, EULER, printIntData);

    printf("\n----STARTING DELETIONS----\n");
    for (int i = 80; i >= 30; i--) {
        KeyValuePair deleted = BSTree_deleteByKey(bst, (void*)&i);

        //if we deleted a valid node
        if (deleted.pKey) {
            printf("\n--------Deleted node %d with data %d--------\n", *(int*)deleted.pKey, *(int*)deleted.pData);
            free(deleted.pKey);
            free(deleted.pData);
            printf("in-order traversal (the node numbers should be in ascending order):\n");
            BSTree_traverse(bst, IN_ORDER, printIntData);
        }
    }

    BSTree_destroy(&bst, freeKeyValuePair);

    return 0;
}
