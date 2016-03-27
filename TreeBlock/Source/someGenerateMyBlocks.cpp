#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "someGenerateMyBlocks.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateMyBlocks1(MyBlock* tRootNode)
{
   MyBlock* tNode = 0;

   tNode = MyBlock::create(1);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(2);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(21);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(22);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(221);
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(222);
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(23);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(24);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(3);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(4);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(41);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(42);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(43);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(44);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateMyBlocks2(MyBlock* tRootNode)
{
   MyBlock* tNode = 0;

   tNode = MyBlock::create(1);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(2);
   tRootNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(21);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);


   tNode = MyBlock::create(211);
   tRootNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);


   tNode = MyBlock::create(2111);
   tRootNode->mLastChildNode->mLastChildNode->mLastChildNode->attachAfterLastChild(tNode);

   tNode = MyBlock::create(22);
   tRootNode->mLastChildNode->attachAfterLastChild(tNode);

}

}//namespace