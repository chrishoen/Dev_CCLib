#ifndef _CCTREEBLOCKVISITOR_H_
#define _CCTREEBLOCKVISITOR_H_

#include <stdio.h>
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
// This is the recursive anchor class. Instances of it are passed to 
// recursive functions that visit tree nodes. It is used to maintain state
// between the recursive visit calls.

class RecursiveAnchor
{
public:
   // Constructor
   RecursiveAnchor();

   // Members
   // This is incremented for each recursive call
   int   mIndex;
   // This is the recursive level
   int   mLevel;
   // If true the the current visitation is the first in its level
   bool  mFirstInLevel;
};



template <class T>
void visitTest101(
   TreeBlock<T>*    aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor)
{
   printf("visitTest101 %d\n",aSubjectNode->mIdentifier);
}

template <class T>
void visitTest102(
   TreeBlock<T>*    aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   void (*aTestVisitorCall)(void*))
{
   printf("visitTest101 %d\n",aSubjectNode->mIdentifier);
}


//****************************************************************************
//****************************************************************************
//****************************************************************************

//----------------------------------------------------------------------------
// Visit collection in construction order

// This visits all nodes in a tree node collection in construction order. 
// It starts at a root subject node and recursively visits all nodes in the
// collection. It is passed a recursive anchor and a call pointer that is
// called on each node visited

template <class T>
void visitAllNodes111(
   TreeBlock<T>*    aSubjectNode, 
   RecursiveAnchor* aRecursiveAnchor,
   void (*aNodeVisitorCall)(TreeBlock<T>*,RecursiveAnchor*))
{
   // Visit the subject node
   (*aNodeVisitorCall)(aSubjectNode, aRecursiveAnchor);
#if 0
   // Visit all nodes below the subject node
   visitAllNodesBelow1<T>(
      aSubjectNode,
      aRecursiveAnchor,
      aNodeVisitorCall);
#endif
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
}//namespace
#endif