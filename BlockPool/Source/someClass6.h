#ifndef _SOMECLASS6_H_
#define _SOMECLASS6_H_

/*==============================================================================
==============================================================================*/

#include <stdio.h>
#include "ccBlockPoolBlock.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************


namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

// This class inherits from BlockPoolBlock to establish a unique memory block
// pool that is used for the memory management of instances of the class.
class Class6A : public CC::BlockPoolBlock<Class6A>
{
public:

   Class6A()
   {
      printf("Class6A::Class6A\n");
   }

   ~Class6A()
   {
      printf("Class6A::~Class6A\n");
   }
   
   void sayHello()
   { 
      printf("hello6A\n");
   }

};

//******************************************************************************
//******************************************************************************
//******************************************************************************

// This class inherits from BlockPoolBlock to establish a unique memory block
// pool that is used for the memory management of instances of the class.
class Class6B : public CC::BlockPoolBlock<Class6B>
{
public:

   Class6B()
   {
      printf("Class6B::Class6B\n");
   }

   ~Class6B()
   {
      printf("Class6B::~Class6B\n");
   }
   
   void sayHello()
   { 
      printf("hello6B\n");
   }

};

//******************************************************************************
}//namespace

#endif

