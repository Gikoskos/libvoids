 /********************
 *  AVLTree.h
 *
 * This file is part of EduDS data structure library which is licensed under
 * the 2-Clause BSD License
 *
 * Copyright (c) 2015, 2016, 2017 George Koskeridis <georgekoskerid@outlook.com>
 * All rights reserved.
  ***********************************************************************************/


#ifndef EduDS_AVLTREE_H__
#define EduDS_AVLTREE_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


typedef struct _AVLTreeNode {
    KeyValuePair item;
    struct _AVLTreeNode *left, *right, *parent;
    int height; //count of edges (not nodes)
} AVLTreeNode;

typedef struct _AVLTree {
    AVLTreeNode *root;
    UserCompareCallback KeyCmp;
} AVLTree;


EduDS_API AVLTree *AVLTree_init(UserCompareCallback KeyCmp,
                                EdsErrCode *err);

EduDS_API AVLTreeNode *AVLTree_insert(AVLTree *avlt,
                                      void *pKey,
                                      void *pData,
                                      EdsErrCode *err);

EduDS_API KeyValuePair AVLTree_deleteNode(AVLTree *avlt,
                                          AVLTreeNode *avltToDelete,
                                          EdsErrCode *err);

EduDS_API KeyValuePair AVLTree_deleteByKey(AVLTree *avlt,
                                           void *pKey,
                                           EdsErrCode *err);

EduDS_API void *AVLTree_findData(AVLTree *avlt,
                                 void *pKey,
                                 EdsErrCode *err);

EduDS_API AVLTreeNode *AVLTree_findNode(AVLTree *avlt,
                                        void *pKey,
                                        EdsErrCode *err);

EduDS_API void AVLTree_traverse(AVLTree *avlt,
                                TreeTraversalMethod traversal,
                                UserDataCallback callback,
                                EdsErrCode *err);

EduDS_API void AVLTree_destroy(AVLTree **avlt,
                               UserDataCallback freeData,
                               EdsErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //EduDS_AVLTREE_H__
