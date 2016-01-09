#ifndef _LFPOINTERQUEUE_H_
#define _LFPOINTERQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFPointerQueue
{
   void  initialize();

   bool  tryStartWrite (int* aWriteIndex);
   void  finishWrite();

   bool  tryStartRead  (int* aReadIndex);
   void  finishRead();

   void  write (int aWriteIndex, void*  aValue);
   void  read  (int aReadIndex,  void** aValue);

   bool  writePtr (void*  aValue);
   void* readPtr  ();
}
#endif

