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

   typedef bool (*LFCasLoopFunction)(unsigned* aExchange);

   bool applyLFCasLoopFunction(
      unsigned*         aValue,
      unsigned*         aExchange,
      unsigned*         aOriginal,
      LFCasLoopFunction aFunction);

//******************************************************************************

}//namespace
#endif

