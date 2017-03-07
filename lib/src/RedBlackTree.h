/***********************************************\
*                 RedBlackTree.h                *
*           George Koskeridis (C) 2017          *
\***********************************************/

#ifndef __EduDS_REDBLACKTREE_H
#define __EduDS_REDBLACKTREE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"

typedef enum _RedBlackTreeColor {
    RED_NODE, BLACK_NODE
} RedBlackTreeColor;


typedef struct _RedBlackTreeNode {
    KeyValuePair item;
    struct _RedBlackTreeNode *left, *right, *parent;
    RedBlackTreeColor color;
} RedBlackTreeNode;

typedef struct _RedBlackTree {
    RedBlackTreeNode *root, *nil;
    UserCompareCallback KeyCmp;
} RedBlackTree;


EduDS_API RedBlackTree *RBTree_init(UserCompareCallback KeyCmp);

EduDS_API RedBlackTreeNode *RBTree_insert(RedBlackTree *rbt, void *pKey, void *pData);

EduDS_API KeyValuePair RBTree_deleteNode(RedBlackTree *rbt, RedBlackTreeNode *avltToDelete);

EduDS_API KeyValuePair RBTree_deleteByKey(RedBlackTree *rbt, void *pKey);

EduDS_API RedBlackTreeNode *RBTree_find(RedBlackTree *rbt, void *pKey);

EduDS_API void RBTree_traverse(RedBlackTree *rbt, TreeTraversalMethod traversal, UserDataCallback callback);

EduDS_API void RBTree_destroy(RedBlackTree **rbt, UserDataCallback freeData);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_REDBLACKTREE_H
