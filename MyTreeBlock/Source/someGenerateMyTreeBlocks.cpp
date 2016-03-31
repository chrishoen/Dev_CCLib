#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "someGenerateMyTreeBlocks.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateMyTreeBlocks1(MyTreeBlock* tRootNode)
{
   MyTreeBlock* tNode = 0;

   tNode = MyTreeBlock::create(1);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(2);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(21);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(22);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(221);
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(222);
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(23);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(24);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(3);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(4);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(41);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(42);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(43);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(44);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateMyTreeBlocks2(MyTreeBlock* tRootNode)
{
   MyTreeBlock* tNode = 0;

   tNode = MyTreeBlock::create(11);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(12);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(13);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyTreeBlock::create(14);
   tRootNode->attachAfterLastChild(tNode);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateMyTreeBlocks3(MyTreeBlock* tRootNode)
{
   MyTreeBlock* tNode = 0;

   tNode = MyTreeBlock::create(11);
   tRootNode->attachBeforeFirstChild(tNode);

   tNode = MyTreeBlock::create(12);
   tRootNode->attachBeforeFirstChild(tNode);

   tNode = MyTreeBlock::create(13);
   tRootNode->attachBeforeFirstChild(tNode);

   tNode = MyTreeBlock::create(14);
   tRootNode->attachBeforeFirstChild(tNode);

}

}//namespace