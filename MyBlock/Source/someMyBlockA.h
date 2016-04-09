#ifndef _SOMEMYBLOCKA_H_
#define _SOMEMYBLOCKA_H_

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

class MyBlockA : public CC::HasBlockHandle
{
public:

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Memory management, constructors and destructors

   // Allocate or deallocate a block from the block pool.
   static void* operator new      (size_t sz);
   static void  operator delete   (void* ptr);

   // Constructors.
   MyBlockA();
   MyBlockA(int aIdentifier);
   // Destructor.
  ~MyBlockA();

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

