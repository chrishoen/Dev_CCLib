#ifndef _LFINTQUEUEMS_H_
#define _LFINTQUEUEMS_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFIntQueueMS
{
   void initialize (int aAllocate);
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

