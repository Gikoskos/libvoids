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
    AVLTree *avlt = AVLTree_init(compareInts);

    srand(time(NULL));

    //trying to add 10 nodes to a binary search tree
    //with pseudorandomly generated keys and data
    printf("\n----STARTING INSERTIONS----\n");
    for (int i = 0; i < 10; i++) {

        int *new_key = newRandInt(100);
        int *new_data = newRandInt(0);

        printf("Trying to insert new node with key %d and data %d!\n", *new_key, *new_data);

        if (AVLTree_insert(avlt, (void*)new_key, (void*)new_data)) {
            printf("Node was successfully inserted!\n");
        } else {
            printf("Node insertion failed!\n\n");
            free(new_key);
            free(new_data);
        }
    }

    printf("\n----PRINTING AVL TREE BEFORE STARTING TO DELETE ELEMENTS----\n");
    printf("in-order traversal (the node numbers should be in ascending order):\n");
    AVLTree_traverse(avlt, IN_ORDER, printIntData);

    printf("\n----STARTING DELETIONS----\n");
    for (int i = 80; i >= 30; i--) {
        KeyValuePair deleted = AVLTree_deleteByKey(avlt, (void*)&i);

        //if we deleted a valid node
        if (deleted.pKey) {
            printf("\n--------Deleted node %d with data %d--------\n", *(int*)deleted.pKey, *(int*)deleted.pData);
            free(deleted.pKey);
            free(deleted.pData);
            printf("in-order traversal (the node numbers should be in ascending order):\n");
            AVLTree_traverse(avlt, IN_ORDER, printIntData);
        }
    }
    AVLTree_destroy(&avlt, freeKeyValuePair);
    return 0;
}
