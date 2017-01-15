/***********************************************\
*              BinarySearchTree.h               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __GiDS_BSTREE_H
#define __GiDS_BSTREE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _BSTreeNode {
    unsigned long key, depth;
    void *pData;
    struct _BSTreeNode *left, *right, *parent;
} BSTreeNode;

typedef enum _BSTreeTraversalMethod {
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    BREADTH_FIRST, //level-order
    EULER
} BSTreeTraversalMethod;


GiDS_API BSTreeNode *insertNodeBSTree(BSTreeNode **bstRoot, unsigned long key, void *pData);

GiDS_API void *deleteNodeBSTree(BSTreeNode **bstRoot,  BSTreeNode *bstToDelete);

GiDS_API void *deleteByKeyBSTree(BSTreeNode **bstRoot, unsigned long key);

GiDS_API BSTreeNode *findNodeBSTree(BSTreeNode *bstRoot, unsigned long key);

GiDS_API void traverseBSTree(BSTreeNode *bstRoot, BSTreeTraversalMethod traversal, CustomDataCallback callback);

GiDS_API void deleteBSTree(BSTreeNode **bstRoot, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_BSTREE_H
