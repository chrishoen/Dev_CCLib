#ifndef _LFINTQUEUEMSCPMS_H_
#define _LFINTQUEUEMSCPMS_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFIntQueueMSCP
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

