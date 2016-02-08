#ifndef _LFINTQUEUE_H_
#define _LFINTQUEUE_H_

#include "LFIntQueueMS.h"
#include "LFIntQueueMSCP.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFIntQueue
{
#ifdef _LFINTQUEUE_CPP_
          int gType = 1;
#else
   extern int gType;
#endif

   inline void setType(int aType)
   {
      gType = aType;
   }

   inline void initialize(int aAllocate)
   {
      switch (gType)
      {
      case 1: return LFIntQueueMS::initialize(aAllocate);
      case 2: return LFIntQueueMSCP::initialize(aAllocate);
      }
   }

   inline void finalize()
   {
      switch (gType)
      {
      case 1: return LFIntQueueMS::finalize();
      case 2: return LFIntQueueMSCP::finalize();
      }
   }

   inline int size()
   {
      switch (gType)
      {
      case 1: return LFIntQueueMS::size();
      case 2: return LFIntQueueMSCP::size();
      }
      return 0;
   }

   inline bool tryWrite (int  aValue)
   {
      switch (gType)
      {
      case 1: return LFIntQueueMS::tryWrite (aValue);
      case 2: return LFIntQueueMSCP::tryWrite (aValue);
      }
      return false;
   }

   inline bool tryRead (int* aValue)
   {
      switch (gType)
      {
      case 1: return LFIntQueueMS::tryRead (aValue);
      case 2: return LFIntQueueMSCP::tryRead (aValue);
      }
      return false;
   }

   inline void show ()
   {
      switch (gType)
      {
      case 1: return LFIntQueueMS::show ();
      case 2: return LFIntQueueMSCP::show ();
      }
   }

   inline unsigned long long writeRetry()
   {
      switch (gType)
      {
      case 1: return LFIntQueueMS::writeRetry ();
      case 2: return LFIntQueueMSCP::writeRetry ();
      }
      return 0;
   }

   inline unsigned long long readRetry()
   {
      switch (gType)
      {
      case 1: return LFIntQueueMS::readRetry ();
      case 2: return LFIntQueueMSCP::readRetry ();
      }
      return 0;
   }

   inline unsigned long long popRetry()
   {
      switch (gType)
      {
      case 1: return LFIntQueueMS::popRetry ();
      case 2: return LFIntQueueMSCP::popRetry ();
      }
      return 0;
   }

   inline unsigned long long pushRetry()
   {
      switch (gType)
      {
      case 1: return LFIntQueueMS::pushRetry ();
      case 2: return LFIntQueueMSCP::pushRetry ();
      }
      return 0;
   }

}
#endif

