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

   tNode = MyTestBlock::create(11);
   tRootNode->attachAfter(tNode);

   tNode = MyTestBlock::create(12);
   tRootNode->mAfterNode->attachAfter(tNode);

   tNode = MyTestBlock::create(13);
   tRootNode->mAfterNode->mAfterNode->attachAfter(tNode);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateMyTestBlocks2(MyTestBlock* tRootNode)
{
}

}//namespace