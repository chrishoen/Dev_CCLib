
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "someMyBlockVisitor.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************

void visitMyBlockForPrint (CC::TreeBlock<MyBlock>* aSubjectNode,CC::RecursiveAnchor* aRecursiveAnchor)
{
   printf("visitMyBlockForPrint %3d %d %d %5d\n",
      aRecursiveAnchor->mIndex,
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      aSubjectNode->mIdentifier);
}

void printAllMyBlocks1(MyBlock* aSubjectNode)
{
   CC::visitAllNodes1(
      aSubjectNode,
      new CC::RecursiveAnchor(),
      visitMyBlockForPrint);
}



}//namespace