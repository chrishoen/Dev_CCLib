#ifndef _CCLFCASLOOP_H_
#define _CCLFCASLOOP_H_
/*==============================================================================

This provides a function that executes a compare and swap loop.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

   typedef bool (*LFCasLoopFunction)(int* aExchange);

   bool applyLFCasLoopFunction(
      int*   aValue,
      int*   aExchange,
      int*   aOriginal,
      LFCasLoopFunction aFunction);

//******************************************************************************

}//namespace
#endif
