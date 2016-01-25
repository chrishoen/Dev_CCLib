/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <prnPrint.h>

#include "someShare.h"
#include "LFIntQueue.h"
#include "RisIntQueue.h"
#include "someReader.h"

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
   Prn::print(0,"Reader.mPassCount %llu",mPassCount);
   Prn::print(0,"Reader.mFailCount %llu",mFailCount);
   Prn::print(0,"Reader.mCodeSum   %llu",mCodeSum);
   Prn::print(0,"");
}
  
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::read1(int aNumReads)
{
   for (int i = 0; i < aNumReads; i++)
   {
      IntMessage tMsg;
      if (LFIntQueue::tryRead(&tMsg.aint()))
      {
         mPassCount++;
         mCodeSum += tMsg.mCode;
      }
      else
      {
         mFailCount++;
      }
   }
}
   
void Reader::flush1()
{
   while(true)
   {
      IntMessage tMsg;
      if (!LFIntQueue::tryRead(&tMsg.aint())) break;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::read2(int aNumReads)
{
   for (int i = 0; i < aNumReads; i++)
   {
      IntMessage tMsg;
      if (RisIntQueue::tryRead(&tMsg.aint()))
      {
         mPassCount++;
         mCodeSum += tMsg.mCode;
      }
      else
      {
         mFailCount++;
      }
   }
}
   
void Reader::flush2()
{
   while(true)
   {
      IntMessage tMsg;
      if (!RisIntQueue::tryRead(&tMsg.aint())) break;
   }
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::read9(int aNumReads)
{
}
   
void Reader::flush9()
{
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

void Reader::read(int aNumReads)
{
   switch (gShare.mMode)
   {
   case 1: return read1(aNumReads);
   case 2: return read2(aNumReads);
   case 9: return read9(aNumReads);
   }
}
   
void Reader::flush()
{
   switch (gShare.mMode)
   {
   case 1: return flush1();
   case 9: return flush9();
   }
}
   
}//namespace