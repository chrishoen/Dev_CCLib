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
#include "someWriterReader.h"

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

   void update1();
   void update2();
   void update();

   void show1();
   void show8();
   void show();

   int mMode;
   bool mTerminateFlag;

   static const int cMaxNumWriters = 10;
   int            mNumWriters;

   Writer         mWriter[cMaxNumWriters];
   WriterReader   mWriterReader[cMaxNumWriters];
   Reader         mReader;

   int mWriterProcessor[cMaxNumWriters];
   int mReaderProcessor;

   unsigned long long  mWriterCount;
   unsigned long long  mWriterPassCount;
   unsigned long long  mWriterFailCount;
   unsigned long long  mWriterCheckSum;
   double              mWriterMeanTime;
   double              mWriterXMeanTime;

   unsigned long long  mReaderCount;
   unsigned long long  mReaderPassCount;
   unsigned long long  mReaderFailCount;
   unsigned long long  mReaderCheckSum;
   double              mReaderMeanTime;
   double              mReaderXMeanTime;

   double              mWriterMeanTimePop;
   double              mWriterMeanTimePush;
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
