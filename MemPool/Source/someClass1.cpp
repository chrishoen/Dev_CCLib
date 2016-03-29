/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "someClass1.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Class1A::Class1A()
{
   Prn::print(0, "Class1A::Class1A");
   mCode1A=101;
}

Class1A::~Class1A()
{
   Prn::print(0, "Class1A::~Class1A");
}

void Class1A::method1A()
{
   Prn::print(0, "Class1A::method1A %d",mCode1A);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

Class1B::Class1B()
{
   Prn::print(0, "Class1B::Class1B");
   mCode1B=102;
}

Class1B::~Class1B()
{
   Prn::print(0, "Class1B::~Class1B");
}

void Class1B::method1B()
{
   Prn::print(0, "Class1B::method1B %d",mCode1B);
}
}//namespace