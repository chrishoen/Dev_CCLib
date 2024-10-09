#pragma once

/*==============================================================================
State variables.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************


namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class implements a general purpose shared storage object. It contains
// status counters and flags.

class State
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members:

   // Queue variables.
   int mQueueSelect;

   // Test variables.
   long long mWriteCount;
   long long mWritePassCount;
   long long mWriteFullCount;

   long long mReadCount;
   long long mReadPassCount;
   long long mReadEmptyCount;
   long long mReadErrorCount;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods:

   // No constructor.
   void reset();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

