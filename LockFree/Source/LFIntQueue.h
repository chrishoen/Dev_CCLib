#ifndef _LFINTQUEUE_H_
#define _LFINTQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFIntQueue
{
   void initialize (int aAllocate);
   void setBackoff(double aQueue1, double aQueue2,double aList1, double aList2);
   void finalize();
   int  listSize();

   bool tryWrite  (int  aValue);
   bool tryRead   (int* aValue);

   void show();

   unsigned long long writeRetry();
   unsigned long long readRetry();
   unsigned long long popRetry();
   unsigned long long pushRetry();
}
#endif

