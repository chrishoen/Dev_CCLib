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

   tNode = new CC::NodeBlock(1);
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(2);
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(21);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(22);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(221);
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(222);
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(23);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(24);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(3);
   tRootNode->attachAfterLastChild(tNode);

   tNode = new CC::NodeBlock(4);
   tRootNode->attachAfterLastChild(tNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateTreeNodes2(CC::NodeBlock* tRootNode)
{
   CC::TreeNode* tNode = 0;

   tNode = CC::NodeBlock::create( 1 );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 2 );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 21 );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 22 );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 221 );
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 222 );
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 23 );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 24 );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 3 );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 4 );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 41 );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 42 );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 43 );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 44 );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateTreeNodes3(CC::NodeBlock* tRootNode)
{
   CC::TreeNode* tNode = 0;

   tNode = CC::NodeBlock::create( 1 );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 2 );
   tRootNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 21 );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);


   tNode = CC::NodeBlock::create( 211 );
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);


   tNode = CC::NodeBlock::create( 2111 );
   tRootNode->mLastChildNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = CC::NodeBlock::create( 22 );
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

}

