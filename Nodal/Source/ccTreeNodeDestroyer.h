#ifndef _CCTREENODEDESTROYER_H_
#define _CCTREENODEDESTROYER_H_

#include "ccCallPointer.h"
#include "ccTreeNodeVisitor.h"
#include "ccTreeNode.h"

namespace CC
{

   void destroyAllTreeNodes(
      TreeNode*        aSubjectNode);

   void destroyAllTreeNodesBelow(
      TreeNode*        aSubjectNode,
      RecursiveAnchor* aRecursiveAnchor);


//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif