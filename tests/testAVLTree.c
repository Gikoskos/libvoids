#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <EduDS.h>

void printIntData(void *param)
{
    AVLTreeNode *treeNode = (AVLTreeNode *)param;

    for (int i = 0; i < treeNode->height; i++)
        putchar('\t');
    printf("node %u at height %d has data %d\n", treeNode->key, treeNode->height, *(int*)(treeNode->pData));
}

int *newRandInt(void)
{
    int *p = malloc(sizeof(int));

    *p = (int)rand();
    return p;
}

int main(int argc, char *argv[])
{
    AVLTreeNode *avltTest = NULL;

    srand(time(NULL));
    //trying to add 10 nodes to a binary search tree
    //with pseudorandomly generated keys and data
    for (int i = 0; i < 10; i++) {
        key_type new_key = (key_type)rand()%100 + 1;
        int *data = newRandInt();
        printf("Trying to insert new node with key %u and data %d!\n", new_key, *data);

        if (AVLTree_insert(&avltTest, new_key, (void*)data)) {
            printf("Node was successfully inserted!\n");
        } else {
            printf("Node insertion failed!\n");
            free(data);
        }
    }

    printf("\n----PRINTING AVL TREE BEFORE STARTING TO DELETE ELEMENTS----\n");
    printf("in-order traversal (the node numbers should be in ascending order):\n");
    AVLTree_traverse(avltTest, IN_ORDER, printIntData);
    //testing traversals
    printf("\npre-order traversal:\n");
    AVLTree_traverse(avltTest, PRE_ORDER, printIntData);

    printf("\nin-order traversal:\n");
    AVLTree_traverse(avltTest, IN_ORDER, printIntData);

    printf("\npost-order traversal:\n");
    AVLTree_traverse(avltTest, POST_ORDER, printIntData);

    printf("\nbreadth-first traversal:\n");
    AVLTree_traverse(avltTest, BREADTH_FIRST, printIntData);

    printf("\neuler traversal:\n");
    AVLTree_traverse(avltTest, EULER, printIntData);

    for (key_type i = 0; i < 50; i++) {
        int *data = (int*) AVLTree_deleteByKey(&avltTest, i);

        if (data) {
            printf("\n--------Deleted node %u with data %d--------\n", i, *data);
            free(data);
            printf("in-order traversal (the node numbers should be in ascending order):\n");
            AVLTree_traverse(avltTest, IN_ORDER, printIntData);
        }
    }
    AVLTree_destroy(&avltTest, free);
    return 0;
}
