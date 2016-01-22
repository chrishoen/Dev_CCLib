/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <prnPrint.h>

#include "LFIntQueue.h"
#include "someReader.h"

// Global instance of the block pool

namespace Some
{


//******************************************************************************
//******************************************************************************
//******************************************************************************

Reader::Reader()
{
   initialize();
}

void Reader::initialize()
{
   mPassCount = 0;
   mFailCount = 0;
   mCodeSum   = 0;
}

void Reader::finalize()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::show()
{
   Prn::print(0,"Reader.mPassCount %u",mPassCount);
   Prn::print(0,"Reader.mFailCount %u",mFailCount);
   Prn::print(0,"Reader.mCodeSum   %u",mCodeSum);
   Prn::print(0,"");
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

bool Reader::readOne(int aMode)
{
   IntMessage tMsg;

   if (LFIntQueue::tryRead(&tMsg.aint()))
   {
      mPassCount++;
      mCodeSum += tMsg.mCode;
      return true;
   }
   else
   {
      if (aMode == 1) mFailCount++;
      return false;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::read(int aNumReads)
{
   if (aNumReads > 0)
   {
      for (int i = 0; i < aNumReads; i++)
      {
         readOne(1);
      }
   }
   else
   {
      while(true)
      {
         if (!readOne(2))
         {
            return;
         }
      }
   }
}
   
}//namespace