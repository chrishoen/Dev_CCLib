#ifndef _SOMEREADER_H_
#define _SOMEREADER_H_

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

class Reader
{
public:

   //---------------------------------------------------------------------------
   // Methods

   Reader();

   void initialize();
   void finalize();
   void show();

   void read1 (int aNumReads);
   void read2 (int aNumReads);
   void read8 (int aNumReads);
   void read  (int aNumReads);

   void flush1 ();
   void flush2 ();
   void flush8 ();
   void flush  ();

   //---------------------------------------------------------------------------
   // Members

   unsigned long long mCount;
   unsigned long long mPassCount;
   unsigned long long mFailCount;
   unsigned long long mCheckSum;

   Ris::TrialTimeMarker mMarker;
   double               mMeanTime;
};

//******************************************************************************
}//namespace

#endif

