
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

void visitMyBlockTest101(MyBlock* aSubjectNode)
{
   CC::visitTest101(
      aSubjectNode);
}

void functionMyBlockForTest102 (void* aSubjectNode)
{
   MyBlock* tSubjectNode = (MyBlock*)aSubjectNode;
   printf("visitMyBlockForTest102 %d\n",tSubjectNode->mIdentifier);
}

void visitMyBlockTest102(MyBlock* aSubjectNode)
{
   CC::visitTest102(
      aSubjectNode,
      functionMyBlockForTest102);
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