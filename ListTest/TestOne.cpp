/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "TestOne.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

TestOne::TestOne()
{
   reset();
}

void TestOne::reset()
{
   mFreeList.reset();
   mList.reset();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun(int aSelect)
{
   switch(aSelect)
   {
      case 11: doRun11(); break;
      case 12: doRun12(); break;
      case 13: doRun13(); break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doInitialize0()
{
   mFreeList.reset();
   mList.reset();
   MyListNode* tNode = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
void TestOne::doInitialize4()
{
   mFreeList.reset();
   mList.reset();
   MyListNode* tNode = 0;

   if ((tNode = mFreeList.doAllocate()) == 0) return;
   tNode->mValue = 101;
   if (!mList.tryWriteTail(tNode)) return;

   if ((tNode = mFreeList.doAllocate()) == 0) return;
   tNode->mValue = 102;
   if (!mList.tryWriteTail(tNode)) return;

   if ((tNode = mFreeList.doAllocate()) == 0) return;
   tNode->mValue = 103;
   if (!mList.tryWriteTail(tNode)) return;

   if ((tNode = mFreeList.doAllocate()) == 0) return;
   tNode->mValue = 104;
   if (!mList.tryWriteTail(tNode)) return;
}

void TestOne::doShow()
{
   printf("Sizes %d  %d\n", mFreeList.allocated(), mList.size());
   MyListNode* tNode = 0;
   for(int i = 0; i < mList.size(); i++)
   {
      MyListNode* tNode = 0;
      if (!mList.tryPeekHead(i, &tNode)) break;
      printf("%d\n", tNode->mValue);
   }     
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun11()
{
   printf("TestOne::doRun1 ****************\n");
   doInitialize4();
   doShow();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun12()
{
   printf("TestOne::doRun2 ****************\n");
   doInitialize4();
   doShow();

   MyListNode* tNode = 0;
   if (!mList.tryReadHead(&tNode)) return;
   printf("ReadHead %d\n", tNode->mValue);
   if (!mList.tryReadHead(&tNode)) return;
   printf("ReadHead %d\n", tNode->mValue);
   doShow();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun13()
{
   printf("TestOne::doRun3 ****************\n");
   doInitialize0();
   doShow();
   MyListNode* tNode = 0;

   for (int i = 0; i < 8; i++)
   {
      if ((tNode = mFreeList.doAllocate()) == 0) return;
      tNode->mValue = 101 + i;
      if (!mList.tryWriteTail(tNode)) return;
   }

   if ((tNode = mFreeList.doAllocate()) == 0) return;
   tNode->mValue = 201;
   if (!mList.tryWriteTail(tNode))
   {
      printf("tryWriteFail %d\n", tNode->mValue);
      mFreeList.doFree(tNode);
   }

   if (!mList.tryReadHead(&tNode)) return;
   printf("ReadHead %d\n", tNode->mValue);

   if ((tNode = mFreeList.doAllocate()) == 0) return;
   tNode->mValue = 301;
   if (!mList.tryWriteTail(tNode))
   {
      printf("tryWriteFail %d\n", tNode->mValue);
      mFreeList.doFree(tNode);
   }

   doShow();
}

