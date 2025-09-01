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

void TestOne::doPutHead(int aValue)
{
   MyListNode* tNode = 0;
   if ((tNode = mFreeList.doAllocate()) == 0)
   {
      printf("doPutHead FAIL free list %d\n", aValue);
      return;
   }

   tNode->mValue = aValue;
   if (!mList.tryWriteHead(tNode))
   {
      printf("doPutHead FAIL write %d\n", aValue);
      return;
   }
}

void TestOne::doPutTail(int aValue)
{
   MyListNode* tNode = 0;
   if ((tNode = mFreeList.doAllocate()) == 0)
   {
      printf("doPutTail FAIL free list %d\n", aValue);
      return;
   }

   tNode->mValue = aValue;
   if (!mList.tryWriteTail(tNode))
   {
      printf("doPutTail FAIL write %d\n", aValue);
      return;
   }
}

void TestOne::doGetHead()
{
   MyListNode* tNode = 0;
   if (!mList.tryReadHead(&tNode))
   {
      printf("doGetHead FAIL read head\n");
      return;
   }
   printf("doGetHead %d\n", tNode->mValue);
   mFreeList.doFree(tNode);
}

void TestOne::doGetTail()
{
   MyListNode* tNode = 0;
   if (!mList.tryReadTail(&tNode))
   {
      printf("doGetTail FAIL read tail\n");
      return;
   }
   printf("doGetTail %d\n", tNode->mValue);
   mFreeList.doFree(tNode);
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
      case 14: doRun14(); break;
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

   doPutTail(101);
   doPutTail(102);
   doPutTail(103);
   doPutTail(104);
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
   doGetHead();
   doGetHead();
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
      doPutTail(101 + i);
   }
   doPutTail(201);
   doGetHead();
   doPutTail(301);
   doShow();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun14()
{
   printf("TestOne::doRun4 ****************\n");
   doInitialize0();
   doShow();
   doGetHead();
   doGetTail();
}

