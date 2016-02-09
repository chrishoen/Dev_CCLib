/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "prnPrint.h"

#define  _SOMECLASS1_CPP_
#include "someClass1.h"

namespace Some
{

Class1A::Class1A() :
   mMyCallPointer(this,&Class1A::myCall1)
{
   // CallPointers
   mMyCallPointer.bind  (this,&Class1A::myCall1);
}

//******************************************************************************

void Class1A::myCall1(int aX)
{
   Prn::print(0,"Class1::myCall1 %d",aX);
}

void Class1A::myCall2(int aX)
{
   Prn::print(0,"Class1::myCall2 %d",aX);
}

}//namespace