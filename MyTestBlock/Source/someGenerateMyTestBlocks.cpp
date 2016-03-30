#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "someGenerateMyTestBlocks.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateMyTestBlocks1(MyTestBlock* tRootNode)
{
   MyTestBlock* tNode = 0;

   tNode = MyTestBlock::create(1);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(2);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(21);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(22);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(221);
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(222);
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(23);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(24);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(3);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(4);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(41);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(42);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(43);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(44);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateMyTestBlocks2(MyTestBlock* tRootNode)
{
   MyTestBlock* tNode = 0;

   tNode = MyTestBlock::create(1);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(2);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(21);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);


   tNode = MyTestBlock::create(211);
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);


   tNode = MyTestBlock::create(2111);
   tRootNode->mLastChildNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTestBlock::create(22);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);
}

}//namespace