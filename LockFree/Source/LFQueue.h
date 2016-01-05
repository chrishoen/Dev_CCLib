#ifndef _LFQUEUE_H_
#define _LFQUEUE_H_

#include <windows.h>


//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFQueue
{
   void initialize();
   void finalize();

   LONG available();

   bool write (int  aValue);
   bool read  (int* aValue);

   bool increment (LONG* aCount);
   bool decrement (LONG* aCount);
}
#endif

