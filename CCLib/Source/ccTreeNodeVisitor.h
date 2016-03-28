#ifndef _CCTREENODEVISITOR_H_
#define _CCTREENODEVISITOR_H_

#include "ccCallPointer.h"
#include "ccTreeNode.h"
#include "ccRecursiveAnchor.h"

/*==============================================================================

This provides a set of functions that can be used to visit tree nodes in a
recursive manner. Tree nodes collections can be visited in two orders:
construction order (the order in which the tree node collection was
constructed) and destruction order (the order that can be used to destroy
a tree node collection, such that child nodes are destroyed before parent
nodes).

==============================================================================*/
namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Call pointer for functions that visit tree nodes

typedef CC::CallPointer2<TreeNode*,RecursiveAnchor*> NodeVisitorCall;

//****************************************************************************
//****************************************************************************
//****************************************************************************

//----------------------------------------------------------------------------
// Visit collection in construction order

// This visits all nodes in a tree node collection in construction order. 
// It starts at a root subject node and recursively visits all nodes in the
// collection. It is passed a recursive anchor and a call pointer that is
// called on each node visited

void visitAllNodes1(
   TreeNode*         aSubjectNode,
   RecursiveAnchor*  aRecursiveAnchor,
   NodeVisitorCall*  aNodeVisitorCall);

// This visits all nodes below a given subject root node. It is called 
// by the above visitAllNodes1.

void visitAllNodesBelow1(
   TreeNode*         aSubjectNode,
   RecursiveAnchor*  aRecursiveAnchor,
   NodeVisitorCall*  aNodeVisitorCall);

//----------------------------------------------------------------------------
// Visit collection in destruction order

// This visits all nodes in a tree node collection in destruction order. 
// It starts at a root subject node and recursively visits all nodes in the
// collection. It is passed a recursive anchor and a call pointer that is
// called on each node visited

void visitAllNodes2(
   TreeNode*         aSubjectNode,
   RecursiveAnchor*  aRecursiveAnchor,
   NodeVisitorCall*  aNodeVisitorCall);

// This visits all nodes below a given subject root node. It is called 
// by the above visitAllNodes2.

void visitAllNodesBelow2(
   TreeNode*         aSubjectNode, 
   RecursiveAnchor*  aRecursiveAnchor,
   NodeVisitorCall*  aNodeVisitorCall);

//----------------------------------------------------------------------------
// Print a collection

// This is a function that is prints a visited tree node
void visitNodeForPrint (TreeNode* aNode, RecursiveAnchor* aRecursiveAnchor);

// This prints all tree nodes in  a collection in construction order
void printAllTreeNodes1(TreeNode* aRootNode);

// This prints all tree nodes in  a collection in destruction order
void printAllTreeNodes2(TreeNode* aRootNode);

//----------------------------------------------------------------------------
// Iteratively visit a colletion

// This can be called in a loop that visits all tree nodes in a collection.
// It is passed a subject node to visit, a recursive anchor, and a call
// pointer to a fuction to be applied when the node is visited.

TreeNode* visitNode(
   TreeNode*         aSubjectNode,
   RecursiveAnchor*  aRecursiveAnchor,
   NodeVisitorCall*  aNodeVisitorCall);

// This prints all nodes in a collection in a loop that uses visitNode.

void printAllTreeNodes3(TreeNode* aRootNode);

//----------------------------------------------------------------------------
// Iteratively visit a colletion

// This can be called in a loop that visits all tree nodes in a collection.
// It returns the next node that is to be visited.

TreeNode* getNextNode(
   TreeNode*         aSubjectNode);

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif