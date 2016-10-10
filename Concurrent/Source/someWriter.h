#ifndef _SOMEWRITER_H_
#define _SOMEWRITER_H_

/*==============================================================================
==============================================================================*/

#include <stdio.h>
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

   void writeType1 (int aNumWrites);
   void writeType2 (int aNumWrites);
   void writeType3 (int aNumWrites);
   void writeType4 (int aNumWrites);
   void writeType5 (int aNumWrites);
   void writeType6 (int aNumWrites);
   void writeType7 (int aNumWrites);
   void write  (int aNumWrites);

   //---------------------------------------------------------------------------
   // Members

   unsigned short mIdent;

   int mCount;
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

