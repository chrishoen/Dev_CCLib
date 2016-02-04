#ifndef _LFFREELIST_H_
#define _LFFREELIST_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFFreeList
{
   void initialize (int aAllocate);
   void initializeBackoff(int aB1, int aB2);

   void finalize   ();
   int  listSize();
   void show();

   unsigned long long popRetry();
   unsigned long long pushRetry();

   bool listPop(int* aNode);
   bool listPush(int aNode);
}
#endif

