#ifndef _SOMEMYBLOCKC_H_
#define _SOMEMYBLOCKC_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <new>
#include "ccBlockHandle.h"
#include "ccBlockPoolCentral.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class MyBlockC : public CC::HasBlockHandle
{
public:

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Memory management, constructors and destructors

   // Allocate a block from the block pool and call its constructor.
   static MyBlockC* create ();
   static MyBlockC* create (int aIdentifier);

   // This method deallocates the object from the block pool from which it was
   // created. It does not call a class destructor.
   void destroy();

   // Constructor, it is called by create after allocation of a new block.
   MyBlockC();
   MyBlockC(int aIdentifier);

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Members

   int  mIdentifier;
   int  mCode1;
   int  mCode2;
   int  mCode3;
   int  mCode4;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Methods

   void method1();
};

//******************************************************************************
}//namespace

#endif

