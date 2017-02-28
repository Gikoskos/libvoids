/***********************************************\
*                   AVLTree.h                   *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __EduDS_AVLTREE_H
#define __EduDS_AVLTREE_H


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



EduDS_API AVLTreeNode *AVLTree_insert(AVLTreeNode **avltRoot, key_type key, void *pData);

EduDS_API void *AVLTree_deleteNode(AVLTreeNode **avltRoot, AVLTreeNode *avltToDelete);

EduDS_API void *AVLTree_deleteByKey(AVLTreeNode **avltRoot, key_type key);

EduDS_API AVLTreeNode *AVLTree_find(AVLTreeNode *avltRoot, key_type key);

EduDS_API void AVLTree_traverse(AVLTreeNode *avltRoot, TreeTraversalMethod traversal, CustomDataCallback callback);

EduDS_API void AVLTree_destroy(AVLTreeNode **avltRoot, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_AVLTREE_H
