#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "GenerateTreeNodes.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateTreeNodes1(CC::LabelledTreeNode* tRootNode)
{
   CC::TreeNode* tNode = 0;

   tNode = new CC::LabelledTreeNode(1, "node1");
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(2, "node2");
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(21, "node21");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(22, "node22");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(221, "node221");
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(222, "node222");
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(23, "node23");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(24, "node24");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(3, "node3");
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::LabelledTreeNode(4, "node4");
   tRootNode->attachAfterLastChild(tNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateTreeNodes2(CC::LabelledTreeNode* tRootNode)
{
   CC::TreeNode* tNode = 0;

   tNode = CC::LabelledTreeNode::create( 1,   "node1" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 2,   "node2" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 21,  "node21" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 22,  "node22" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 221, "node221" );
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 222, "node222" );
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 23,  "node23" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 24,  "node24" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 3,   "node3" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 4,   "node4" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 41,  "node41" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 42,  "node42" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 43,  "node43" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 44,  "node44" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateTreeNodes3(CC::LabelledTreeNode* tRootNode)
{
   CC::TreeNode* tNode = 0;

   tNode = CC::LabelledTreeNode::create( 1,   "node1" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 2,   "node2" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 21,  "node21" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);


   tNode = CC::LabelledTreeNode::create( 211,  "node211" );
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);


   tNode = CC::LabelledTreeNode::create( 2111,  "node2111" );
   tRootNode->mLastChildNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::LabelledTreeNode::create( 22,  "node22" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

}

