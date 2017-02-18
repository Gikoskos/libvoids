/***********************************************\
*                   AVLTree.h                   *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __GiDS_AVLTREE_H
#define __GiDS_AVLTREE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _AVLTreeNode {
    unsigned long key;
    void *pData;
    struct _AVLTreeNode *left, *right, *parent;
    int height; //count of edges (not nodes)
} AVLTreeNode;


GiDS_API AVLTreeNode *insertNodeAVLTree(AVLTreeNode **avltRoot, unsigned long key, void *pData);

GiDS_API void *deleteNodeAVLTree(AVLTreeNode **avltRoot, AVLTreeNode *avltToDelete);

GiDS_API void *deleteByKeyAVLTree(AVLTreeNode **avltRoot, unsigned long key);

GiDS_API AVLTreeNode *findNodeAVLTree(AVLTreeNode *avltRoot, unsigned long key);

GiDS_API void traverseAVLTree(AVLTreeNode *avltRoot, TreeTraversalMethod traversal, CustomDataCallback callback);

GiDS_API void deleteAVLTree(AVLTreeNode **avltRoot, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_AVLTREE_H
