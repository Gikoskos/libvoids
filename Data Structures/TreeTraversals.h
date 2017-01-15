/***********************************************\
*                TreeTraversals.h               *
*           George Koskeridis (C) 2016          *
\***********************************************/
//LIBRARY INTERNAL HEADER. DO NOT INCLUDE THIS ANYWHERE ELSE.

#ifndef __GiDS_TREETRAVERSALS_H
#define __GiDS_TREETRAVERSALS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"


GiDS_LOCAL void pre_orderTraversal(BSTreeNode *bstRoot, CustomDataCallback callback);

GiDS_LOCAL void in_orderTraversal(BSTreeNode *bstRoot, CustomDataCallback callback);

GiDS_LOCAL void post_orderTraversal(BSTreeNode *bstRoot, CustomDataCallback callback);

GiDS_LOCAL void breadth_firstTraversal(BSTreeNode *bstRoot, CustomDataCallback callback);

GiDS_LOCAL void eulerTraversal(BSTreeNode *bstRoot, CustomDataCallback callback);

#ifdef __cplusplus
}
#endif

#endif //__GiDS_TREETRAVERSALS_H