#ifndef _SOMEWRITERREADER_H_
#define _SOMEWRITERREADER_H_

/*==============================================================================
==============================================================================*/

#include <stdio.h>
#include "someMessage.h"
#include "risTimeMarker.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************


namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class WriterReader
{
public:

   //---------------------------------------------------------------------------
   // Methods

   WriterReader();

   void initialize(unsigned aIdent=0);
   void finalize();
   void show();

   void startTrial();
   void finishTrial();

   void writeread  (int aNumWrites);

   //---------------------------------------------------------------------------
   // Members

   unsigned short mIdent;
   unsigned short mCode;

   unsigned long long mWriteCount;
   unsigned long long mWritePassCount;
   unsigned long long mWriteFailCount;
   unsigned long long mWriteCheckSum;

   unsigned long long mReadCount;
   unsigned long long mReadPassCount;
   unsigned long long mReadFailCount;
   unsigned long long mReadCheckSum;

   Ris::TrialTimeMarker mMarkerWrite;
   double               mMeanTimeWrite;
   Ris::TrialTimeMarker mMarkerRead;
   double               mMeanTimeRead;

};

//******************************************************************************
}//namespace

#endif

