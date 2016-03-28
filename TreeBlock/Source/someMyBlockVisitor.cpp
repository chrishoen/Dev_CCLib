
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
   printf("\n");
   printf("printAllMyBlocks1**************************** %5d\n",aSubjectNode->mIdentifier);

   CC::RecursiveAnchor tRecursiveAnchor;

   CC::visitAllNodes1(
      aSubjectNode,
      &tRecursiveAnchor,
      visitMyBlockForPrint);
   printf("\n");
}

void printAllMyBlocks2(MyBlock* aSubjectNode)
{
   printf("\n");
   printf("printAllMyBlocks2**************************** %5d\n",aSubjectNode->mIdentifier);

   CC::RecursiveAnchor tRecursiveAnchor;

   CC::visitAllNodes2(
      aSubjectNode,
      &tRecursiveAnchor,
      visitMyBlockForPrint);
   printf("\n");
}



}//namespace