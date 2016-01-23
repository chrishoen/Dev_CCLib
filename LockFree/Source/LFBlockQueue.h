#ifndef _LFBLOCKQUEUE_H_
#define _LFBLOCKQUEUE_H_

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
   void  finalize    ();

   bool  startWrite  (int* aNode);
   void  finishWrite (int  aNode);

   bool  startRead   (int* aNode);
   void  finishRead  (int  aNode);

   void* element (int  aNode);

   void show();
}
#endif

