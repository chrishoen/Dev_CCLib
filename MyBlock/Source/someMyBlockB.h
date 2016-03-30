#ifndef _SOMEMYBLOCKB_H_
#define _SOMEMYBLOCKB_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <new>
#include "ccBlockHandle.h"
#include "ccBlockPoolList.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class MyBlockB : public CC::HasBlockHandle
{
public:

   MyBlockB();
  ~MyBlockB();

   void method1B();

   int mCode1B;
  
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // This allocates a block from the block pool and uses placement new
   // to call the class constructor. It is analogous to new.

   static MyBlockB* allocate();

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // This deallocates the object back to the block pool. It does not call
   // a destructor for the object.
   void deallocate();

};

//******************************************************************************
}//namespace

#endif

