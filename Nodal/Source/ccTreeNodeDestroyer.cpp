
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ccTreeNodeDestroyer.h"
#include "ccTreeNodeAttach.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

void destroyAllTreeNodes(
   TreeNode*        aSubjectNode)
{
   // Recursive anchor
   RecursiveAnchor* tRecursiveAnchor = new RecursiveAnchor();

   // Visit all nodes below the subject node
   destroyAllTreeNodesBelow(
      aSubjectNode,
      tRecursiveAnchor);

   // Visit the subject node
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

      // Recursively call this method for the child node
      destroyAllTreeNodesBelow(
         tChildNode,
         aRecursiveAnchor);

      // Update the recursive index
      aRecursiveAnchor->mIndex++;

      // Detach the child node after the recursive call
      detach(tChildNode);

      // Destroy the child node after the recursive call
      tChildNode->destroy();

      // Proceed to the next child node
      tChildNode = tChildNode->mAfterNode;
   }

   // After the loop, decrement the recursive level
   aRecursiveAnchor->mLevel--;
}

}//namespace