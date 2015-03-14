
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ccTreeNodeDestroyer.h"
#include "ccTreeNodeAttach.h"
#include "ccDefs.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

void destroyAllTreeNodes(
   TreeNode*        aSubjectNode)
{
   // If short term memory then there is no destruction
   if (aSubjectNode->mMemoryType == CC::MemoryType_ShortTerm)
   {
      // Detach the subject node from all nodes to which iti is attached
      detach(aSubjectNode);
      return;
   }

   // Recursive anchor
   RecursiveAnchor* tRecursiveAnchor = new RecursiveAnchor();

   // Visit all nodes below the subject node
   destroyAllTreeNodesBelow(
      aSubjectNode,
      tRecursiveAnchor);

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
   TreeNode* tChildNode = aSubjectNode->mFirstChildNode;

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
         destroyAllTreeNodesBelow(
            tChildNode,
            aRecursiveAnchor);
      }

      // Update the recursive index
      aRecursiveAnchor->mIndex++;

      // Store a pointer to the next child node before deleting it
      TreeNode* tAfterChildNode = tChildNode->mAfterNode;

      // Detach the child node from all nodes to which it is attached
      detach(tChildNode);

      // Destroy the child node
      tChildNode->destroy();

      // Proceed to the next child node
      tChildNode = tAfterChildNode;
   }

   // After the loop, decrement the recursive level
   aRecursiveAnchor->mLevel--;
}

}//namespace