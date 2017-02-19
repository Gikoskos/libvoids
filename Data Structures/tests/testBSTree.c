#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GiDS.h>

void printIntData(void *param)
{
    BSTreeNode *treeNode = (BSTreeNode *)param;

    printf("node %u has data %d\n", treeNode->key, *(int*)(treeNode->pData));
}

int main(int argc, char *argv[])
{
    BSTreeNode *bstTest = NULL;

    srand(time(NULL));
    //trying to add 10 nodes to a binary search tree
    //with pseudorandomly generated keys and data
    for (int i = 0; i < 10; i++) {
        key_type new_key = (key_type)rand()%100 + 1;
        int *data = malloc(sizeof data);

        *data = (int)rand();
        printf("Trying to insert new node with key %u and data %d!\n", new_key, *data);

        if (BSTree_insert(&bstTest, new_key, (void*)data)) {
            printf("Node was successfully inserted!\n");
        } else {
            printf("Node insertion failed!\n");
            free(data);
        }
    }

    //testing traversals
    /*printf("\npre-order traversal:\n");
    BSTree_traverse(bstTest, PRE_ORDER, printIntData);

    printf("\nin-order traversal:\n");
    BSTree_traverse(bstTest, IN_ORDER, printIntData);

    printf("\npost-order traversal:\n");
    BSTree_traverse(bstTest, POST_ORDER, printIntData);

    printf("\nbreadth-first traversal:\n");
    BSTree_traverse(bstTest, BREADTH_FIRST, printIntData);

    printf("\neuler traversal:\n");
    BSTree_traverse(bstTest, EULER, printIntData);*/

    for (key_type i = 0; i < 50; i++) {
        int *data = (int*) BSTree_deleteByKey(&bstTest, i);

        if (data) {
            printf("\nDeleted node %u with data %d\n", i, *data);
            free(data);
            printf("in-order traversal (the node numbers should be in ascending order):\n");
            BSTree_traverse(bstTest, IN_ORDER, printIntData);
        }
    }
    BSTree_destroy(&bstTest, free);
    return 0;
}
