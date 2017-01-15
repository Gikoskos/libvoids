#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GiDS.h>

void printIntData(void *param)
{
    int i;
    BSTreeNode *treeNode = (BSTreeNode *)param;

    for (i = 0; i < treeNode->depth; i++)
        putchar('\t');

    printf("node %lu at depth %lu has data %d\n", treeNode->key, treeNode->depth, *(int*)(treeNode->pData));
}

int main(int argc, char *argv[])
{
    BSTreeNode *bstTest = NULL;

    srand(time(NULL));
    //trying to add 10 nodes to a binary search tree
    //with pseudorandomly generated keys and data
    for (int i = 0; i < 10; i++) {
        unsigned long new_key = (unsigned long)rand()%100 + 1;
        int *data = malloc(sizeof data);

        *data = (int)rand();
        printf("Trying to insert new node with key %lu and data %d!\n", new_key, *data);

        if (insertNodeBSTree(&bstTest, new_key, (void*)data)) {
            printf("Node was successfully inserted!\n");
        } else {
            printf("Node insertion failed!\n");
            free(data);
        }
    }

    //testing traversals
    printf("\npre-order traversal:\n");
    traverseBSTree(bstTest, PRE_ORDER, printIntData);

    printf("\nin-order traversal:\n");
    traverseBSTree(bstTest, IN_ORDER, printIntData);

    printf("\npost-order traversal:\n");
    traverseBSTree(bstTest, POST_ORDER, printIntData);

    printf("\nbreadth-first traversal:\n");
    traverseBSTree(bstTest, BREADTH_FIRST, printIntData);

    printf("\neuler traversal:\n");
    traverseBSTree(bstTest, EULER, printIntData);

    for (unsigned long i = 0; i < 50; i++) {
        int *data = (int*) deleteByKeyBSTree(&bstTest, i);

        if (data) {
            printf("\nDeleted node %lu with data %d\n", i, *data);
            free(data);
        }
    }
    deleteBSTree(&bstTest, free);
    return 0;
}
