#ifndef _LFINTQUEUE_H_
#define _LFINTQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFBlockQueue
{
   typedef struct
   {
      int  mCode1;
      int  mCode2;
      int  mCode3;
      int  mCode4;
   } BlockT;

   void  initialize  (int  aAllocate);

   bool  startWrite  (int* aIndex);
   void  finishWrite (int  aIndex);

   bool  startRead   (int* aIndex);
   void  finishRead  (int  aIndex);

   void* element (int  aIndex);

   void show();
}
#endif

