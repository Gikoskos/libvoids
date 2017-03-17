#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <EduDS.h>


void printIntData(void *param)
{
    KeyValuePair *item = (KeyValuePair *)param;

    printf("node %d has data %d\n", *(int*)item->pKey, *(int*)item->pData);
    
    /*RedBlackTreeNode *node = (RedBlackTreeNode*)param;
    printf("node 0x%p %s\t= (key = %d\tcolor = %s\tleft child = 0x%p %s\tright child = 0x%p %s\tparent = 0x%p %s)\n",
           node, (node == rbt->root) ? "ROOT" : ((node->right == rbt->nil && node->left == rbt->nil) ? "LEAF" : ""),
           *(int*)node->item.pKey,
           (node->color == BLACK_NODE) ? "BLACK" : "RED",
           node->left, (node->left == rbt->nil) ? "nil" : "", 
           node->right, (node->right == rbt->nil) ? "nil" : "",
           node->parent, (node->parent == rbt->nil) ? "nil" : "");*/
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
    RedBlackTree *rbt;
    rbt = RBTree_init(compareInts, NULL);

    srand(time(NULL));
    printf("\n----STARTING INSERTIONS----\n");
    for (int i = 0; i < 10; i++) {

        int *new_key = newRandInt(100);
        int *new_data = newRandInt(0);

        printf("Trying to insert new node with key %d and data %d!\n", *new_key, *new_data);

        if (RBTree_insert(rbt, (void*)new_key, (void*)new_data, NULL)) {
            printf("Node was successfully inserted!\n");
            printf("in-order traversal (the node numbers should be in ascending order):\n");
            RBTree_traverse(rbt, EDS_IN_ORDER, printIntData, NULL);
            putchar('\n');

        } else {
            printf("Node insertion failed!\n\n");
            free(new_key);
            free(new_data);
        }
    }

    
    printf("\n----PRINTING RB TREE BEFORE STARTING TO DELETE ELEMENTS----\n");
    printf("in-order traversal (the node numbers should be in ascending order):\n");
    RBTree_traverse(rbt, EDS_IN_ORDER, printIntData, NULL);

    printf("\n----STARTING DELETIONS----\n");
    for (int i = 80; i >= 30; i--) {
        KeyValuePair deleted = RBTree_deleteByKey(rbt, (void*)&i, NULL);

        //if we deleted a valid node
        if (deleted.pKey) {
            printf("\n--------Deleted node %d with data %d--------\n", *(int*)deleted.pKey, *(int*)deleted.pData);
            free(deleted.pKey);
            free(deleted.pData);
            printf("in-order traversal (the node numbers should be in ascending order):\n");
            RBTree_traverse(rbt, EDS_IN_ORDER, printIntData, NULL);
        }
    }

    RBTree_destroy(&rbt, freeKeyValuePair, NULL);
    return 0;
}
