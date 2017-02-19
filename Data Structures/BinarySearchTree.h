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
    key_type key;
    void *pData;
    struct _BSTreeNode *left, *right, *parent;
} BSTreeNode;


EduDS_API BSTreeNode *BSTree_insert(BSTreeNode **bstRoot, key_type key, void *pData);
          
EduDS_API void *BSTree_deleteNode(BSTreeNode **bstRoot,  BSTreeNode *bstToDelete);
          
EduDS_API void *BSTree_deleteByKey(BSTreeNode **bstRoot, key_type key);
          
EduDS_API BSTreeNode *BSTree_find(BSTreeNode *bstRoot, key_type key);
          
EduDS_API void BSTree_traverse(BSTreeNode *bstRoot, TreeTraversalMethod traversal, CustomDataCallback callback);
          
EduDS_API void BSTree_destroy(BSTreeNode **bstRoot, CustomDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_BSTREE_H
