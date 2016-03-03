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
#include "someTester.h"
#include "ccLFPointerQueue.h"
#include "ccLFBlockQueue.h"
#include "ccLFBlockFreeList.h"

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
   void update3();
   void update();

   void show12();
   void show3();
   void show();

   int mMode;
   int mType;
   int mTest;
   bool mTerminateFlag;

   static const int cMaxNumWriters = 10;
   int            mNumWriters;

   Writer         mWriter[cMaxNumWriters];
   WriterReader   mWriterReader[cMaxNumWriters];
   Reader         mReader;
   Tester         mTester;

   int mWriterProcessor[cMaxNumWriters];
   int mReaderProcessor;

   unsigned long long  mWriterCount;
   unsigned long long  mWriterPassCount;
   unsigned long long  mWriterFailCount;
   unsigned long long  mWriterCheckSum;
   double              mWriterMeanTime;

   unsigned long long  mReaderCount;
   unsigned long long  mReaderPassCount;
   unsigned long long  mReaderFailCount;
   unsigned long long  mReaderCheckSum;
   double              mReaderMeanTime;

   double              mWriterMeanTimePop;
   double              mWriterMeanTimePush;

   unsigned long long  mTesterCount;
   double              mTesterMeanTime1;
   double              mTesterMeanTime2;

   CC::LFPointerQueue  mPointerQueue;
   CC::LFBlockQueue    mBlockFreeList;
   CC::LFBlockQueue    mBlockQueue;

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
