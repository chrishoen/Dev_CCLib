#ifndef _CCTREEBLOCKDESTROYER_H_
#define _CCTREEBLOCKDESTROYER_H_

#include <stdio.h>
#include "ccTreeBlockVisitor.h"
#include "ccTreeBlock.h"

namespace CC
{

// This destroys a collection of tree nodes, starting at and including a 
// subject root node. It recursively traverses the nodes in destruction
// order, such that child nodes are destroyed before parent nodes. It
// recursively destroys all of the nodes below the subject root node
// and then destroys the subject root node. For each node destroyed, 
// it calls the node destroy function.

template <class T>
void destroyAllTreeBlocks(
   TreeBlock<T>*    aSubjectNode)
{
   // If short term memory then there is no destruction
   if (aSubjectNode->mMemoryType == CC::MemoryType_ShortTerm)
   {
      // Detach the subject node from all nodes to which it is attached
      aSubjectNode->detachFromAll();
      return;
   }

   // Recursive anchor
   RecursiveAnchor tRecursiveAnchor;

   // Visit all nodes below the subject node
   destroyAllTreeBlocksBelow(
      aSubjectNode,
      &tRecursiveAnchor);

   // Destroy the subject node
   aSubjectNode->destroy();
}

// This destroys all child nodes below a subject root node. It is called 
// by the above recursive destroy function. It recursively traverses 
// the nodes in destruction order, such that child nodes are 
// destroyed before parent nodes. For each node destroyed, it calls the
// node destroy function.

template <class T>
void destroyAllTreeBlocksBelow(
   TreeBlock<T>*    aSubjectNode,
   RecursiveAnchor* aRecursiveAnchor)
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

      // If not short term memory then there is destruction
      if (aSubjectNode->mMemoryType != CC::MemoryType_ShortTerm)
      {
         // Recursively call this method for the child node
         destroyAllTreeBlocksBelow(
            tChildNode,
            aRecursiveAnchor);
      }

      // Update the recursive index
      aRecursiveAnchor->mIndex++;

      // Store a pointer to the next child node before deleting it
      TreeBlock<T>* tAfterChildNode = tChildNode->mAfterNode;

      // Detach the child node from all nodes to which it is attached
      tChildNode->detachFromAll();

      // Destroy the child node
      tChildNode->destroy();

      // Proceed to the next child node
      tChildNode = tAfterChildNode;
   }

   // After the loop, decrement the recursive level
   aRecursiveAnchor->mLevel--;
}


//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif