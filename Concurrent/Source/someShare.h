#ifndef _SOMESHARE_H_
#define _SOMESHARE_H_

/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "risTimeMarker.h"
#include "someWriter.h"
#include "someReader.h"

namespace Some
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class Share
{
public:
   Share();

   void initialize();
   void update();
   void show();

   int mMode;

   static const int cMaxNumWriters = 10;
   Writer   mWriter[cMaxNumWriters];
   int      mNumWriters;

   Reader mReader;

   unsigned long long  mWriterCount;
   unsigned long long  mWriterPassCount;
   unsigned long long  mWriterFailCount;
   unsigned long long  mWriterCodeSum;
   double              mWriterMeanTime;

   unsigned long long  mReaderCount;
   unsigned long long  mReaderPassCount;
   unsigned long long  mReaderFailCount;
   unsigned long long  mReaderCodeSum;
   double              mReaderMeanTime;

};

//******************************************************************************
// Global instance

#ifdef _SOMESHARE_CPP_
          Share gShare;
#else
   extern Share gShare;
#endif

//******************************************************************************
}//namespace

#endif
