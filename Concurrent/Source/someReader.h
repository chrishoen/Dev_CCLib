#ifndef _SOMEREADER_H_
#define _SOMEREADER_H_

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

class Reader
{
public:

   //---------------------------------------------------------------------------
   // Methods

   Reader();

   void initialize();
   void finalize();
   void show();

   void startTrial();
   void finishTrial();

   void readType1 (int aNumReads);
   void readType2 (int aNumReads);
   void readType3 (int aNumReads);
   void read      (int aNumReads);

   void flushType1 ();
   void flushType2 ();
   void flushType3 ();
   void flush  ();

   //---------------------------------------------------------------------------
   // Members

   unsigned long long mCount;
   unsigned long long mPassCount;
   unsigned long long mFailCount;
   unsigned long long mCheckSum;

   Ris::TrialTimeMarker mMarkerRead;
   double               mMeanTimeRead;
};

//******************************************************************************
}//namespace

#endif

