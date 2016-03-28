#ifndef _CCTREEBLOCKVISITOR_H_
#define _CCTREEBLOCKVISITOR_H_

#include <stdio.h>
#include "ccRecursiveAnchor.h"
#include "ccTreeBlock.h"

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
// Visit collection in construction order

// This visits all nodes in a tree node collection in construction order. 
// It starts at a root subject node and recursively visits all nodes in the
// collection. It is passed a recursive anchor and a call pointer that is
// called on each node visited

template <class T>
void visitAllNodes1(
   TreeBlock<T>*    aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   void (*aNodeVisitorCall)(TreeBlock<T>*,RecursiveAnchor*))
{
   // Visit the subject node
   (*aNodeVisitorCall)(aSubjectNode, aRecursiveAnchor);

   // Visit all nodes below the subject node
   visitAllNodesBelow1<T>(
      aSubjectNode,
      aRecursiveAnchor,
      aNodeVisitorCall);
}

// This visits all nodes below a given subject root node. It is called 
// by the above visitAllNodes1.

template <class T>
void visitAllNodesBelow1(
   TreeBlock<T>*    aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   void (*aNodeVisitorCall)(TreeBlock<T>*,RecursiveAnchor*))
{
   //-------------------------------------------------------------------------
   // Loop for each child node of the subject node

   // Recursive local variable for first in level flag, 
   bool tFirstInLevel=true;

   // Before the loop, increment the recursive level
   aRecursiveAnchor->mLevel++;

   // Start the loop at the first child node
   TreeBlock<T>* tChildNode = aSubjectNode->mFirstChildNode;

   // Loop through the child nodes
   while (tChildNode != 0)
   {
      // Update the recursive first in level flag
      aRecursiveAnchor->mFirstInLevel = tFirstInLevel;
      tFirstInLevel = false;

      // Update the recursive index
      aRecursiveAnchor->mIndex++;

      // Visit the child node before the recursive call
      (*aNodeVisitorCall)(tChildNode, aRecursiveAnchor);

      // Recursively call this method for the child node
      visitAllNodesBelow1(
         tChildNode,
         aRecursiveAnchor,
         aNodeVisitorCall);

      // Proceed to the next child node
      tChildNode = tChildNode->mAfterNode;
   }

   // After the loop, decrement the recursive level
   aRecursiveAnchor->mLevel--;
}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Visit collection in destruction order

// This visits all nodes in a tree node collection in destruction order. 
// It starts at a root subject node and recursively visits all nodes in the
// collection. It is passed a recursive anchor and a call pointer that is
// called on each node visited

template <class T>
void visitAllNodes2(
   TreeBlock<T>*    aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   void (*aNodeVisitorCall)(TreeBlock<T>*,RecursiveAnchor*))
{
   // Visit all nodes below the subject node
   visitAllNodesBelow2(
      aSubjectNode,
      aRecursiveAnchor,
      aNodeVisitorCall);

   // Visit the subject node
   (*aNodeVisitorCall)(aSubjectNode, aRecursiveAnchor);
}

// This visits all nodes below a given subject root node. It is called 
// by the above visitAllNodes2.

template <class T>
void visitAllNodesBelow2(
   TreeBlock<T>*    aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   void (*aNodeVisitorCall)(TreeBlock<T>*,RecursiveAnchor*))
{
   //-------------------------------------------------------------------------
   // Loop for each child node of the subject node

   // Recursive local variable for first in level flag, 
   bool tFirstInLevel=true;

   // Before the loop, increment the recursive level
   aRecursiveAnchor->mLevel++;

   // Start the loop at the first child node
   TreeBlock<T>* tChildNode = aSubjectNode->mFirstChildNode;

   // Loop through the child nodes
   while (tChildNode != 0)
   {
      // Update the recursive first in level flag
      aRecursiveAnchor->mFirstInLevel = tFirstInLevel;
      tFirstInLevel = false;

      // Recursively call this method for the child node
      visitAllNodesBelow2(
         tChildNode,
         aRecursiveAnchor,
         aNodeVisitorCall);

      // Update the recursive index
      aRecursiveAnchor->mIndex++;

      // Visit the child node after the recursive call
      (*aNodeVisitorCall)(tChildNode, aRecursiveAnchor);

      // Proceed to the next child node
      tChildNode = tChildNode->mAfterNode;
   }

   // After the loop, decrement the recursive level
   aRecursiveAnchor->mLevel--;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Iteratively visit a colletion. This can be called in a loop that visits all
// tree nodes in a collection. It is passed a subject node to visit, a
// recursive anchor, and a call pointer to a fuction to be applied when the
// node is visited.

template <class T>
TreeBlock<T>* visitNode(
   TreeBlock<T>*    aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   void (*aNodeVisitorCall)(TreeBlock<T>*,RecursiveAnchor*))
{
   //--------------------------------------------------------------------------
   // Visit the subject node

   (*aNodeVisitorCall)(aSubjectNode, aRecursiveAnchor);

   //--------------------------------------------------------------------------
   // Set the subject node ancestor with after node

   // If the subject node has no parent
   if (aSubjectNode->mParentNode == 0)
   {
      // Then it has no ancestor with after node
      aSubjectNode->mAncestorWithAfter = 0;
   }
   // Else if the parent of the subject node has a node after it
   else if (aSubjectNode->mParentNode->mAfterNode !=0)
   {
      // Then the subject node ancestor with after node is its parent
      aSubjectNode->mAncestorWithAfter = aSubjectNode->mParentNode;
   }
   // Else the subject node has no parent with an after node
   else
   {
      // Copy the subject node's parent ancestor after node to it.
      // That will be the closest ancestor that has a node after it.
      // This is used recursively by calls to getNextNode.
      aSubjectNode->mAncestorWithAfter = aSubjectNode->mParentNode->mAncestorWithAfter;
   }

   //--------------------------------------------------------------------------
   // Update the recursive index

   aRecursiveAnchor->mIndex++;

   //--------------------------------------------------------------------------
   // Pointer to the next node

   TreeBlock<T>* tNextNode = 0;

   //--------------------------------------------------------------------------
   // Determine the next node

   // If the subject node has child nodes
   if (aSubjectNode->mFirstChildNode)
   {
      // The next node will be the first child node of the subject node
      tNextNode = aSubjectNode->mFirstChildNode;
      // The next node level will increase
      aRecursiveAnchor->mLevel++;
      // The next node will be the first in its level
      aRecursiveAnchor->mFirstInLevel = true;
   }
   // Else if the subject node has a node after it
   else if (aSubjectNode->mAfterNode)
   {
      // The next node will be the node after it
      tNextNode = aSubjectNode->mAfterNode;
      // The next node will not be the first in its level
      aRecursiveAnchor->mFirstInLevel = false;
   }
   // Else the subject node has no child nodes and no nodes after it
   else
   {
      // If the subject node has an ancestor after node
      if (aSubjectNode->mAncestorWithAfter)
      {
         // Set the next node to the ancestor after node
         tNextNode = aSubjectNode->mAncestorWithAfter->mAfterNode;
      }
   }
   // Return the next node
   return tNextNode;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
#endif
