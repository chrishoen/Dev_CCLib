#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "ccNodeBlock.h"
#include "GenerateTreeNodes.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateTreeNodes1(CC::NodeBlock* tRootNode)
{
   CC::TreeNode* tNode = 0;

   tNode = new CC::NodeBlock(1, "node1");
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(2, "node2");
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(21, "node21");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(22, "node22");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(221, "node221");
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(222, "node222");
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(23, "node23");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(24, "node24");
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(3, "node3");
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(4, "node4");
   tRootNode->attachAfterLastChildAsLastInStructure(tNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateTreeNodes2(CC::NodeBlock* tRootNode)
{
   CC::TreeNode* tNode = 0;

   tNode = CC::NodeBlock::create( 1,   "node1" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 2,   "node2" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 21,  "node21" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 22,  "node22" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 221, "node221" );
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 222, "node222" );
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 23,  "node23" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 24,  "node24" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 3,   "node3" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 4,   "node4" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 41,  "node41" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 42,  "node42" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 43,  "node43" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 44,  "node44" );
   tRootNode->mLastChildNode->attachAfterLastChildAsLastInStructure(tNode);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateTreeNodes3(CC::NodeBlock* tRootNode)
{
   CC::TreeNode* tNode = 0;

   tNode = CC::NodeBlock::create( 1,   "node1" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 2,   "node2" );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 21,  "node21" );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);


   tNode = CC::NodeBlock::create( 211,  "node211" );
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);


   tNode = CC::NodeBlock::create( 2111,  "node2111" );
   tRootNode->mLastChildNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 22,  "node22" );
   tRootNode->mLastChildNode->attachAfterLastChildAsLastInStructure(tNode);

}

