#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "someGenerateBlocks.h"

namespace Some
{

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void generateBlocks1(NodeBlock* tRootNode)
   {
      CC::TreeNode* tNode = 0;

      tNode = new NodeBlock(1);
      tRootNode->attachAfterLastChild(tNode);

      tNode = new NodeBlock(2);
      tRootNode->attachAfterLastChild(tNode);

      tNode = new NodeBlock(21);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = new NodeBlock(22);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = new NodeBlock(221);
      tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = new NodeBlock(222);
      tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = new NodeBlock(23);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = new NodeBlock(24);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = new NodeBlock(3);
      tRootNode->attachAfterLastChild(tNode);

      tNode = new NodeBlock(4);
      tRootNode->attachAfterLastChild(tNode);
   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void generateBlocks2(NodeBlock* tRootNode)
   {
      CC::TreeNode* tNode = 0;

      tNode = NodeBlock::create(1);
      tRootNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(2);
      tRootNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(21);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(22);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(221);
      tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(222);
      tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(23);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(24);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(3);
      tRootNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(4);
      tRootNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(41);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(42);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(43);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(44);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   }

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************

   void generateBlocks3(NodeBlock* tRootNode)
   {
      CC::TreeNode* tNode = 0;

      tNode = NodeBlock::create(1);
      tRootNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(2);
      tRootNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(21);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);


      tNode = NodeBlock::create(211);
      tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);


      tNode = NodeBlock::create(2111);
      tRootNode->mLastChildNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

      tNode = NodeBlock::create(22);
      tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   }

}//namespace