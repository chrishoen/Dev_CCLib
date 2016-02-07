#ifndef _LFINTQUEUETC_H_
#define _LFINTQUEUETC_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFIntQueueTC
{
   void initialize (int aAllocate);
   void finalize();
   int  size();

   bool tryWrite  (int  aValue);
   bool tryRead   (int* aValue);

   void show();

   unsigned long long writeRetry();
   unsigned long long readRetry();
   unsigned long long popRetry();
   unsigned long long pushRetry();
}
#endif

