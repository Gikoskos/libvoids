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
    KeyValuePair item;
    struct _AVLTreeNode *left, *right, *parent;
    int height; //count of edges (not nodes)
} AVLTreeNode;

typedef struct _AVLTree {
    AVLTreeNode *root;
    UserCompareCallback KeyCmp;
} AVLTree;


EduDS_API AVLTree *AVLTree_init(UserCompareCallback KeyCmp,
                                EduDSErrCode *err);

EduDS_API AVLTreeNode *AVLTree_insert(AVLTree *avlt,
                                      void *pKey,
                                      void *pData,
                                      EduDSErrCode *err);

EduDS_API KeyValuePair AVLTree_deleteNode(AVLTree *avlt,
                                          AVLTreeNode *avltToDelete,
                                          EduDSErrCode *err);

EduDS_API KeyValuePair AVLTree_deleteByKey(AVLTree *avlt,
                                           void *pKey,
                                           EduDSErrCode *err);

EduDS_API AVLTreeNode *AVLTree_find(AVLTree *avlt,
                                    void *pKey,
                                    EduDSErrCode *err);

EduDS_API void AVLTree_traverse(AVLTree *avlt,
                                TreeTraversalMethod traversal,
                                UserDataCallback callback,
                                EduDSErrCode *err);

EduDS_API void AVLTree_destroy(AVLTree **avlt,
                               UserDataCallback freeData,
                               EduDSErrCode *err);

#ifdef __cplusplus
}
#endif

#endif //__EduDS_AVLTREE_H
