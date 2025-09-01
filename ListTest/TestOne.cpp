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

void TestOne::doInitialize0()
{
   mFreeList.reset();
   mList.reset();
   MyListNode* tNode = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doInitializeFromTail4()
{
   mFreeList.reset();
   mList.reset();
   MyListNode* tNode = 0;

   doPutTail(101);
   doPutTail(102);
   doPutTail(103);
   doPutTail(104);
}

void TestOne::doInitializeFromHead4()
{
   mFreeList.reset();
   mList.reset();
   MyListNode* tNode = 0;

   doPutHead(101);
   doPutHead(102);
   doPutHead(103);
   doPutHead(104);
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

void TestOne::doRun(int aSelect)
{
   switch(aSelect)
   {
      case 11: doRun11(); break;
      case 12: doRun12(); break;
      case 13: doRun13(); break;
      case 14: doRun14(); break;
      case 21: doRun21(); break;
      case 22: doRun22(); break;
      case 23: doRun23(); break;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun11()
{
   printf("TestOne::doRun11 ****************\n");
   doInitializeFromTail4();
   doShow();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun12()
{
   printf("TestOne::doRun12 ****************\n");
   doInitializeFromTail4();
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
   printf("TestOne::doRun13 ****************\n");
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
   printf("TestOne::doRun14 ****************\n");
   doInitialize0();
   doShow();
   doGetHead();
   doGetTail();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun21()
{
   printf("TestOne::doRun21 ****************\n");
   doInitializeFromHead4();
   doShow();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun22()
{
   printf("TestOne::doRun22 ****************\n");
   doInitializeFromHead4();
   doShow();

   MyListNode* tNode = 0;
   doGetTail();
   doGetTail();
   doShow();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void TestOne::doRun23()
{
   printf("TestOne::doRun23 ****************\n");
   doInitialize0();
   doShow();
   MyListNode* tNode = 0;

   for (int i = 0; i < 8; i++)
   {
      doPutHead(101 + i);
   }
   doPutHead(201);
   doGetTail();
   doPutHead(301);
   doShow();
}

