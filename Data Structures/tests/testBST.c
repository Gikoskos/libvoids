#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GiDS.h>

void printIntData(void *pData)
{
    int x = *(int *)pData;
    printf("%d ", x);
}

int main(int argc, char *argv[])
{
    BSTreeNode *bstTest = NULL;

    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        unsigned long new_key = (unsigned long)rand()%100 + 1;
        int *data = malloc(sizeof data);

        *data = (int)rand();
        insertNodeBSTree(&bstTest, new_key, (void*)data);
    }

    return 0;
}
