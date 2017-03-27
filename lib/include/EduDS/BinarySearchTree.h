 /********************
 *  BinarySearchTree.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


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


EduDS_API BSTree *BSTree_init(UserCompareCallback KeyCmp,
                              EdsErrCode *err);

EduDS_API BSTreeNode *BSTree_insert(BSTree *bst,
                                    void *pData,
                                    void *pKey,
                                    EdsErrCode *err);

EduDS_API KeyValuePair BSTree_deleteNode(BSTree *bst,
                                         BSTreeNode *bstToDelete,
                                         EdsErrCode *err);

EduDS_API KeyValuePair BSTree_deleteByKey(BSTree *bst,
                                          void *pKey,
                                          EdsErrCode *err);

EduDS_API BSTreeNode *BSTree_findNode(BSTree *bst,
                                      void *pKey,
                                      EdsErrCode *err);

EduDS_API void *BSTree_findData(BSTree *bst,
                                void *pKey,
                                EdsErrCode *err);

EduDS_API void BSTree_traverse(BSTree *bst,
                               TreeTraversalMethod traversal,
                               UserDataCallback callback,
                               EdsErrCode *err);

EduDS_API void BSTree_destroy(BSTree **bst,
                              UserDataCallback freeData,
                              EdsErrCode *err);


#ifdef __cplusplus
}
#endif

#endif //__EduDS_BSTREE_H
