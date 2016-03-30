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
      CC::TreeNode* tNode = 0;

      tNode = new LabelledTreeNode(1, "node1");
      tRootNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(2, "node2");
      tRootNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(21, "node21");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(22, "node22");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(221, "node221");
      tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(222, "node222");
      tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(23, "node23");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = new LabelledTreeNode(24, "node24");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

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

      tNode = LabelledTreeNode::create(1, "node1");
      tRootNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(2, "node2");
      tRootNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(21, "node21");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(22, "node22");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(221, "node221");
      tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(222, "node222");
      tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(23, "node23");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(24, "node24");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(3, "node3");
      tRootNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(4, "node4");
      tRootNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(41, "node41");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(42, "node42");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(43, "node43");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(44, "node44");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void generateLabelledTreeNodes3(LabelledTreeNode* tRootNode)
   {
      CC::TreeNode* tNode = 0;

      tNode = LabelledTreeNode::create(1, "node1");
      tRootNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(2, "node2");
      tRootNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(21, "node21");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);


      tNode = LabelledTreeNode::create(211, "node211");
      tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);


      tNode = LabelledTreeNode::create(2111, "node2111");
      tRootNode->mLastChildNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = LabelledTreeNode::create(22, "node22");
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   }

}//namespace