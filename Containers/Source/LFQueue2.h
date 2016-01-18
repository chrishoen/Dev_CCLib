#ifndef _LFQUEUE2_H_
#define _LFQUEUE2_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFQueue2
{
   void initialize();

   bool tryStartWrite (int* aWriteIndex);
   void finishWrite();

   bool tryStartRead  (int* aReadIndex);
   void finishRead();

   void write (int aWriteIndex, int  aValue);
   void read  (int aReadIndex,  int* aValue);
}
#endif

