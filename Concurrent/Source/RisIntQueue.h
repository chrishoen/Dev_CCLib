#ifndef _RISINTQUEUE_H_
#define _RISINTQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace RisIntQueue
{
   void initialize (int aAllocate);
   void finalize   ();

   bool tryWrite  (int  aValue);
   bool tryRead   (int* aValue);

   void show();
}
#endif

