#include "KMessageLFQueue.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Regionals

enum             {eCapacity = 4};
static const LONG cCapacity = 4;
static const LONG cCapacityMask = 0x03;

static LONG mBuffer[eCapacity];
   
static LONG mNumOfElements = eCapacity;
static LONG mElementSize = 4;

static PCHAR mElementStore = 0;

static LONG mReadAvailable  = 0;
static LONGLONG mWriteCount = 0;
static LONGLONG mReadCount  = 0;

static BOOLEAN mEnableFlag  = FALSE;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate buffer size needed for queue create

LONG KMsg_LFQueue_calc_buffer_size()
{
   return cCapacity*4;
}

VOID KMsg_LFQueue_create (PVOID aBuffer)
{
   mNumOfElements = cCapacity;
   mElementSize = 4;
   mElementStore = (char*)aBuffer;

   mReadAvailable = 0;
   mWriteCount = 0;
   mReadCount  = 0;
   mEnableFlag = FALSE;
}

BOOLEAN  KMsg_LFQueue_isEmpty() {return mReadAvailable <= 0;}
BOOLEAN  KMsg_LFQueue_isFull () {return mReadAvailable >= cCapacity;}

//******************************************************************************
//******************************************************************************
//******************************************************************************

VOID KMsg_LFQueue_reset()
{
   mEnableFlag = FALSE;
   mReadAvailable = 0;
   mWriteCount = 0;
   mReadCount  = 0;
}

VOID KMsg_LFQueue_enable()
{
   mEnableFlag = TRUE;
}

VOID KMsg_LFQueue_disable()
{
   mEnableFlag = FALSE;
}

//******************************************************************************
// This returns a pointer to an element. It is used in place of
// mElementStore[aIndex]

PVOID KMsg_LFQueue_element (LONG aIndex)
{
   return mElementStore + mElementSize*aIndex;
}
   
//******************************************************************************
//******************************************************************************
//******************************************************************************

BOOLEAN KMsg_LFQueue_startWrite(LONG* aWriteIndex)
{
   // Guard for queue disabled
   if (!mEnableFlag) return FALSE;

   // Guard for full, number of available reads is at capacity
   if (mReadAvailable >= cCapacity) return FALSE;

   // Increment the number of reads that are available
   LONG tOriginal = InterlockedExchangeAdd(&mReadAvailable,1);

   // Guard for full again
   if (tOriginal >= cCapacity)
   {
      // Undo the increment and exit
      InterlockedExchangeAdd(&mReadAvailable,-1);
      return FALSE;
   }

   // Increment the write count and get the write index from it
   LONGLONG tWriteCount = InterlockedExchangeAdd64(&mWriteCount,1);
   LONG     tWriteIndex = tWriteCount % cCapacity;

   // Store result
   *aWriteIndex = tWriteIndex;
   return TRUE;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

VOID KMsg_LFQueue_finishWrite()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

BOOLEAN KMsg_LFQueue_startRead(LONG* aReadIndex)
{
   // Guard for queue disabled
   if (!mEnableFlag) return FALSE;

   // Guard for empty, number of available reads is at zero
   if (mReadAvailable <= 0) return FALSE;

   // Increment the read count and get the read index from it
   // This doesn't need LONGerlocks because there is only one reader.
   LONGLONG tReadCount = mReadCount++;
   LONG     tReadIndex = tReadCount % cCapacity;

   // Store result
   *aReadIndex = tReadIndex;
   return TRUE;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

VOID KMsg_LFQueue_finishRead()
{
   // Decrement the number of reads that are available
   InterlockedDecrement(&mReadAvailable);
}
