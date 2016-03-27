
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

void visitMyBlockForPrint (MyBlock* aSubjectNode, CC::RecursiveAnchor* aRecursiveAnchor)
{
   printf("visitMyBlockForPrint %3d %d %d %5d\n",
      aRecursiveAnchor->mIndex,
      aRecursiveAnchor->mFirstInLevel,
      aRecursiveAnchor->mLevel,
      aSubjectNode->mIdentifier);
}

void test101(MyBlock* aSubjectNode)
{
   CC::visitTest101(
      aSubjectNode,
      new CC::RecursiveAnchor());
}

void visitMyBlockForTest (void* aSubjectNode)
{
}

void test102(MyBlock* aSubjectNode)
{
   CC::visitTest102(
      aSubjectNode,
      new CC::RecursiveAnchor(),
      visitMyBlockForTest);
}













void printAllMyBlocks1(MyBlock* aSubjectNode)
{
#if 0
   CC::visitAllNodes111(
      aSubjectNode,
      new CC::RecursiveAnchor(),
      visitMyBlockForPrint);
#endif
}

}//namespace