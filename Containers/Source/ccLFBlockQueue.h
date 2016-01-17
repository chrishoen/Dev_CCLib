#ifndef _CCLFBLOCKQUEUE_H_
#define _CCLFBLOCKQUEUE_H_
/*==============================================================================

Lock Free Fixed Size Block Queue. 

This implements a block queue. The queue is thread safe. It uses an atomic
interlocked compare and exchange to guard against concurrency contentions. 
It is based on a multiple writer, single reader model. A writer starts a write, 
obtaining a write index to the next queue element that is available to be can 
written to. If the queue is full then the write start fails. The writer then
writes to the corresponding queue element. After the write is complete the 
writer somehow signals the reader to read from the queue. The reader wakes up 
and starts a read, obtaining a read index to the next queue element that is 
available to be read from. If the queue is empty, then the read start fails 
(this should not happen because writer should not signal the reader). The 
reader then reads from the corresponding queue element and then calls finish 
read to update the queue state.

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************

class LFBlockQueue
{
public:

   //---------------------------------------------------------------------------
   // Memory Methods

   // Constructor
   LFBlockQueue();
  ~LFBlockQueue();

   // Allocate memory for the block array and initialize the queue logic
   // variables. It is passed the number of blocks to allocate and the size
   // of the blocks.

  void initialize(int aAllocate,int aBlockSize);

   // Return a pointer to a block, based on its block index.
  
   char* element(int aIndex);

   //---------------------------------------------------------------------------
   // Memory Members

   // Pointer to allocated memory
   char* mMemory;

   // Number of blocks allocated
   int mAllocate;

   // Size of each block allocated
   int mBlockSize;

   //---------------------------------------------------------------------------
   // Queue Logic Members

   //---------------------------------------------------------------------------
   // These two variables are each 16 bits and they are packed into a 32 bit 
   // structure because the atomic compare exchange operation used works on
   // 32 bit integers. This limits the queue size to 64K elements. The only 
   // code that can safely change these variables is contained here. Any other
   // code should be read only.
   //
   // WriteIndex is used to circularly index into queue memory for write 
   // operations. ReadAvailable is used to indicate the number of reads that 
   // are available. They have the following ranges:
   //
   //      0 <= WriteIndex    <= Allocate-1
   //      0 <= ReadAvailable <= Allocate
   //
   //      IF ReadAvailable == 0        THEN the queue is empty
   //      IF ReadAvailable == Allocate THEN the queue is full
   //
   //  The ReadIndex is derived from WriteIndex and ReadAvailable.
   //
   //      ReadIndex = WriteIndex - ReadAvailable;
   //      IF ReadIndex < 0 THEN ReadIndex = ReadIndex + Allocate;
   //---------------------------------------------------------------------------

   typedef union
   {
       struct    
       { 
         unsigned short mWriteIndex;  
         unsigned short mReadAvailable;  
       } Parms;
       signed mPacked;
   } LFQueueParms;

   LFQueueParms mParms;

   //---------------------------------------------------------------------------
   // Queue Logic Methods

   // This is called to start a write operation. If the queue is not full then
   // it succeeds. It updates the variable pointed by the input pointer with the 
   // WriteIndex that is to be used to access queue memory for the write, it
   // increments ReadAvailable and returns true. If it fails because the queue is 
   // full then it returns false.
   bool tryStartWrite (int* aWriteIndex);

   // This is a place holder.
   void finishWrite();

   // This is called to start a read operation. If the queue is not empty then it 
   // succeeds, it  updates the variable pointed by the input pointer with the 
   // ReadIndex that is to be used to access queue memory for the read and returns 
   // true. If it fails because the queue is empty then it returns false.
   bool tryStartRead  (int* aReadIndex);

   // This is called to finish a read operation. It decrements ReadAvailable.
   void finishRead();
};

//******************************************************************************

}//namespace
#endif

