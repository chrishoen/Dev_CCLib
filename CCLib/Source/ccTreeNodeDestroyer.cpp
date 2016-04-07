
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ccBlockPoolCentral.h"
#include "ccTreeNodeDestroyer.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

void destroyAllTreeNodes(
   TreeNode* aSubjectNode)
{
   // If short term memory then there is no destruction
   if (!isBlockPoolMemoryLongTerm(aSubjectNode->mBlockHandle))
   {
      // Detach the subject node from all nodes to which it is attached
      aSubjectNode->detachFromAll();
      return;
   }

   // Recursive anchor
   RecursiveAnchor tRecursiveAnchor;

   // Visit all nodes below the subject node
   destroyAllTreeNodesBelow(
      aSubjectNode,
      &tRecursiveAnchor);

   // Destroy the subject node
   aSubjectNode->destroy();

}

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Visit all nodes below

void destroyAllTreeNodesBelow(
   TreeNode*        aSubjectNode,
   RecursiveAnchor* aRecursiveAnchor)
{
   //-------------------------------------------------------------------------
   // Loop for each child node of the subject node

   // Recursive local variable for first in level flag, 
   bool tFirstInLevel=true;

   // Before the loop, increment the recursive level
   aRecursiveAnchor->mLevel++;

   // Start the loop at the first child node
   TreeNode* tChildNodeP = aSubjectNode->ptrFirstChildNode();

   // Loop through the child nodes
   while (tChildNodeP != 0)
   {
      // Update the recursive first in level flag
      aRecursiveAnchor->mFirstInLevel = tFirstInLevel;
      tFirstInLevel = false;

      // If not short term memory then there is destruction
      if (isBlockPoolMemoryLongTerm(aSubjectNode->mBlockHandle))
      {
         // Recursively call this method for the child node
         destroyAllTreeNodesBelow(
            tChildNodeP,
            aRecursiveAnchor);
      }

      // Update the recursive index
      aRecursiveAnchor->mIndex++;

      // Store a pointer to the next child node before deleting it
      TreeNode* tAfterChildNodeP = tChildNodeP->ptrAfterNode();

      // Detach the child node from all nodes to which it is attached
      tChildNodeP->detachFromAll();

      // Destroy the child node
      tChildNodeP->destroy();

      // Proceed to the next child node
      tChildNodeP = tAfterChildNodeP;
   }

   // After the loop, decrement the recursive level
   aRecursiveAnchor->mLevel--;
}

}//namespace