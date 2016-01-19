#ifndef _LFQUEUE_H_
#define _LFQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFQueue
{
   void initialize (unsigned aAllocate);

   bool tryStartWrite (int* aWriteIndex);
   void finishWrite();

   bool tryStartRead  (int* aReadIndex);
   void finishRead();

   void write (int aWriteIndex, int  aValue);
   void read  (int aReadIndex,  int* aValue);
}
#endif

