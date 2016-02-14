/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#include "someClass3.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

Class3A::Class3A()
{
   Prn::print(0, "Class3A::Class3A");
   mCode=101;
}

Class3A::~Class3A()
{
   Prn::print(0, "Class3A::~Class3A");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void* Class3A::operator new(size_t sz)
{
   Prn::print(0, "Class3A::new   %d",(int)sz);
   return ::operator new(sz);
}
  
void* Class3A::operator new[](size_t sz)
{
   Prn::print(0, "Class3A::new[] %d",(int)sz);
   return ::operator new(sz);
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Class3A::operator delete(void* ptr)
{
   Prn::print(0, "Class3A::delete");
   ::operator delete(ptr);
}

void Class3A::operator delete[](void* ptr)
{
   Prn::print(0, "Class3A::delete");
   ::operator delete(ptr);
}
}//namespace