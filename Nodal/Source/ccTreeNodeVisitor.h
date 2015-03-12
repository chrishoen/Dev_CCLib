#ifndef _CCTREENODEVISITOR_H_
#define _CCTREENODEVISITOR_H_

#include "ccCallPointer.h"
#include "ccTreeNode.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

class RecursiveAnchor
{
public:
   // Constructor
   RecursiveAnchor();

   // Members
   int   mIndex;
   int   mLevel;
   bool  mFirstInLevel;
};

//****************************************************************************
//****************************************************************************
//****************************************************************************

typedef CC::CallPointer2<TreeNode*,RecursiveAnchor*> NodeVistorCall;

//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitAllNodes1(
   TreeNode*        aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   NodeVistorCall*  aNodeVisitorCall);

void visitAllNodes2(
   TreeNode*        aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   NodeVistorCall*  aNodeVisitorCall);

void visitAllNodesBelow1(
   TreeNode*        aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   NodeVistorCall*  aNodeVisitorCall);

void visitAllNodesBelow2(
   TreeNode*        aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   NodeVistorCall*  aNodeVisitorCall);

void visitNodeForPrint (TreeNode* aNode, RecursiveAnchor* aRecursiveAnchor);
void printAllTreeNodes1(TreeNode* aRootNode);
void printAllTreeNodes2(TreeNode* aRootNode);

TreeNode* visitNode(
   TreeNode*        aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   NodeVistorCall*  aNodeVisitorCall);

void printAllTreeNodes3(TreeNode* aRootNode);

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif