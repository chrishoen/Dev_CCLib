#ifndef _LFQUEUE_H_
#define _LFQUEUE_H_

#include <windows.h>


//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFQueue
{
   void initialize();

   bool tryStartWrite (int* aWriteIndex);
   bool tryStartRead  (int* aReadIndex);

   void write (int aWriteIndex, int  aValue);
   void read  (int aReadIndex,  int* aValue);
}
#endif

