#ifndef _SOMEWRITER_H_
#define _SOMEWRITER_H_

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

class Writer
{
public:

   //---------------------------------------------------------------------------
   // Methods

   Writer();

   void initialize(unsigned aIdent=0);
   void finalize();
   void show();

   void startTrial();
   void finishTrial();

   void write1 (int aNumWrites);
   void write2 (int aNumWrites);
   void write8 (int aNumWrites);
   void write  (int aNumWrites);

   //---------------------------------------------------------------------------
   // Members

   unsigned short mIdent;
   unsigned short mCode;

   unsigned long long mCount;
   unsigned long long mPassCount;
   unsigned long long mFailCount;
   unsigned long long mCheckSum;

   Ris::TrialTimeMarker mMarkerWrite;
   double               mMeanTimeWrite;

   Ris::TrialTimeMarker mMarkerPop;
   double               mMeanTimePop;
   Ris::TrialTimeMarker mMarkerPush;
   double               mMeanTimePush;
};

//******************************************************************************
}//namespace

#endif

