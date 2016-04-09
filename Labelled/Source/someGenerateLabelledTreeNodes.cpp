#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "someGenerateLabelledTreeNodes.h"

namespace Some
{

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void generateLabelledTreeNodes1(LabelledTreeNode* tRootNode)
   {
      LabelledTreeNode* tNode = 0;

      tNode = new LabelledTreeNode(1, "node1");
      tRootNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(2, "node2");
      tRootNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(21, "node21");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(22, "node22");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(221, "node221");
      tRootNode->ptrLastChildNode()->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(222, "node222");
      tRootNode->ptrLastChildNode()->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(23, "node23");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(24, "node24");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(3, "node3");
      tRootNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(4, "node4");
      tRootNode->attachAfterLastChild(tNode);
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void generateLabelledTreeNodes2(LabelledTreeNode* tRootNode)
   {
      CC::TreeNode* tNode = 0;

      tNode = new LabelledTreeNode(1, "node1");
      tRootNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(2, "node2");
      tRootNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(21, "node21");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(22, "node22");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(221, "node221");
      tRootNode->ptrLastChildNode()->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(222, "node222");
      tRootNode->ptrLastChildNode()->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(23, "node23");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(24, "node24");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(3, "node3");
      tRootNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(4, "node4");
      tRootNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(41, "node41");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(42, "node42");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(43, "node43");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(44, "node44");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void generateLabelledTreeNodes3(LabelledTreeNode* tRootNode)
   {
      LabelledTreeNode* tNode = 0;

      tNode = new LabelledTreeNode(1, "node1");
      tRootNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(2, "node2");
      tRootNode->attachAfterLastChild(tNode);
      return;
      tNode = new LabelledTreeNode(21, "node21");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(211, "node211");
      tRootNode->ptrLastChildNode()->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(2111, "node2111");
      tRootNode->ptrLastChildNode()->ptrLastChildNode()->ptrLastChildNode()->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(22, "node22");
      tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);
   }

}//namespace