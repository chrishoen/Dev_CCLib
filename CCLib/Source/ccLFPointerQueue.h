#ifndef _CCLFPOINTERQUEUE_H_
#define _CCLFPOINTERQUEUE_H_
/*==============================================================================

Lock Free Pointer Queue Class Template. 

This implements a pointer queue. It uses the lock free value queue template
and provides some methods that simplify usage.

==============================================================================*/
#include "ccLFValueQueue.h"
//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class Element>
class LFPointerQueue : public CC::LFValueQueue <Element>
{
public:

   //******************************************************************************
   //******************************************************************************
   //******************************************************************************
   // These simplify queue access.

   bool LFPointerQueue::writePtr (Element aValue)
   {
      return tryWrite(aValue);
   }

   Element LFPointerQueue::readPtr ()
   {
      void* tValue;
      if (!tryRead(&tValue)) return 0;
      return tValue;
   }
};
}//namespace
#endif

