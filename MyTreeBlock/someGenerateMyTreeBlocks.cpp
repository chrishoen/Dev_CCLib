#include "stdafx.h"

#include "someGenerateMyTreeBlocks.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateMyTreeBlocks1(MyTreeBlock* tRootNode)
{
   MyTreeBlock* tNode = 0;

   tNode = new MyTreeBlock(1);
   tRootNode->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(2);
   tRootNode->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(21);
   tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(22);
   tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(221);
   tRootNode->ptrLastChildNode()->ptrLastChildNode()->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(222);
   tRootNode->ptrLastChildNode()->ptrLastChildNode()->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(23);
   tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(24);
   tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(3);
   tRootNode->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(4);
   tRootNode->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(41);
   tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(42);
   tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(43);
   tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(44);
   tRootNode->ptrLastChildNode()->attachAfterLastChild(tNode);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateMyTreeBlocks2(MyTreeBlock* tRootNode)
{
   MyTreeBlock* tNode = 0;

   tNode = new MyTreeBlock(11);
   tRootNode->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(12);
   tRootNode->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(13);
   tRootNode->attachAfterLastChild(tNode);

   tNode = new MyTreeBlock(14);
   tRootNode->attachAfterLastChild(tNode);

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void generateMyTreeBlocks3(MyTreeBlock* tRootNode)
{
   MyTreeBlock* tNode = 0;

   tNode = new MyTreeBlock(11);
   tRootNode->attachBeforeFirstChild(tNode);

   tNode = new MyTreeBlock(12);
   tRootNode->attachBeforeFirstChild(tNode);

   tNode = new MyTreeBlock(13);
   tRootNode->attachBeforeFirstChild(tNode);

   tNode = new MyTreeBlock(14);
   tRootNode->attachBeforeFirstChild(tNode);

}

}//namespace