
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "someMyBlockScratch.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************
//****************************************************************************

void functionMyBlockForScratch102 (void* aSubjectNode)
{
   MyBlock* tSubjectNode = (MyBlock*)aSubjectNode;
   printf("scratchMyBlockForTest102 %d\n",tSubjectNode->mIdentifier);
}

void functionMyBlockForScratch103 (CC::TreeBlock<MyBlock>* aSubjectNode)
{
   printf("scratchMyBlockForTest103 %d\n",aSubjectNode->mIdentifier);
}

//****************************************************************************

void scratchMyBlockTest101(MyBlock* aSubjectNode)
{
   CC::scratchTest101(
      aSubjectNode);
}

void scratchMyBlockTest102(MyBlock* aSubjectNode)
{
   CC::scratchTest102(
      aSubjectNode,
      functionMyBlockForScratch102);
}

void scratchMyBlockTest103(MyBlock* aSubjectNode)
{
   CC::scratchTest103(
      aSubjectNode,
      functionMyBlockForScratch103);
}

}//namespace