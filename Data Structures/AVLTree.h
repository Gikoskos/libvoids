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
    key_type key;
    void *pData;
    struct _AVLTreeNode *left, *right, *parent;
    int height; //count of edges (not nodes)
} AVLTreeNode;



GiDS_API AVLTreeNode *AVLTree_insert(AVLTreeNode **avltRoot, key_type key, void *pData);

GiDS_API void *AVLTree_deleteNode(AVLTreeNode **avltRoot, AVLTreeNode *avltToDelete);

GiDS_API void *AVLTree_deleteByKey(AVLTreeNode **avltRoot, key_type key);

GiDS_API AVLTreeNode *AVLTree_find(AVLTreeNode *avltRoot, key_type key);

GiDS_API void AVLTree_traverse(AVLTreeNode *avltRoot, TreeTraversalMethod traversal, CustomDataCallback callback);

GiDS_API void AVLTree_destroy(AVLTreeNode **avltRoot, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_AVLTREE_H
