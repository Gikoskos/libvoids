/***********************************************\
*              BinarySearchTree.h               *
*           George Koskeridis (C) 2016          *
\***********************************************/

#ifndef __EduDS_BSTREE_H
#define __EduDS_BSTREE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _BSTreeNode {
    KeyValuePair item;
    struct _BSTreeNode *left, *right, *parent;
} BSTreeNode;

typedef struct _BSTree {
    BSTreeNode *root;
    UserCompareCallback KeyCmp;
} BSTree;


EduDS_API BSTree *BSTree_init(UserCompareCallback KeyCmp);

EduDS_API BSTreeNode *BSTree_insert(BSTree *bst, void *pData, void *pKey);
          
EduDS_API KeyValuePair BSTree_deleteNode(BSTree *bst, BSTreeNode *bstToDelete);
          
EduDS_API KeyValuePair BSTree_deleteByKey(BSTree *bst, void *pKey);
          
EduDS_API BSTreeNode *BSTree_find(BSTree *bst, void *pKey);
          
EduDS_API void BSTree_traverse(BSTree *bst, TreeTraversalMethod traversal, UserDataCallback callback);
          
EduDS_API void BSTree_destroy(BSTree **bst, UserDataCallback freeData);


#ifdef __cplusplus
}
#endif

#endif //__EduDS_BSTREE_H
