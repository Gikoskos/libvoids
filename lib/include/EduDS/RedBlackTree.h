 /********************
 *  RedBlackTree.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef EduDS_REDBLACKTREE_H__
#define EduDS_REDBLACKTREE_H__


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


EduDS_API RedBlackTree *RBTree_init(UserCompareCallback KeyCmp,
                                    EdsErrCode *err);

EduDS_API RedBlackTreeNode *RBTree_insert(RedBlackTree *rbt,
                                          void *pKey,
                                          void *pData,
                                          EdsErrCode *err);

EduDS_API KeyValuePair RBTree_deleteNode(RedBlackTree *rbt,
                                         RedBlackTreeNode *rbtToDelete,
                                         EdsErrCode *err);

EduDS_API KeyValuePair RBTree_deleteByKey(RedBlackTree *rbt,
                                          void *pKey,
                                          EdsErrCode *err);

EduDS_API RedBlackTreeNode *RBTree_findNode(RedBlackTree *rbt,
                                            void *pKey,
                                            EdsErrCode *err);

EduDS_API void *RBTree_findData(RedBlackTree *rbt,
                                void *pKey,
                                EdsErrCode *err);

EduDS_API void RBTree_traverse(RedBlackTree *rbt,
                               TreeTraversalMethod traversal,
                               UserDataCallback callback,
                               EdsErrCode *err);

EduDS_API void RBTree_destroy(RedBlackTree **rbt,
                              UserDataCallback freeData,
                              EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //EduDS_REDBLACKTREE_H__
