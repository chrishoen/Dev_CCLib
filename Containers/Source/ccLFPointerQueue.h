#ifndef _CCLFPOINTERQUEUE_H_
#define _CCLFPOINTERQUEUE_H_
/*==============================================================================

This defines a queue of void* pointers. 

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace CC
{
//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsulates a pointer stack. It maintains an array of pointers
// that are dynamically allocated at initialization. Access to the array is 
// done is a stack manner, with pushes and pops.

class LFPointerQueue
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   LFPointerQueue();
  ~LFPointerQueue();

   // Allocate memory for the stack array and initialize the stack index. 
   // aAllocate is the number of pointers to allocate, the size of the array.
   void initialize(int aAllocate);

   // Write a pointer to the queue. Return false if the queue is full.
   bool  writePtr(void* aPointer);

   // Read a pointer from of the queue. Return null if the queue is empty.
   void* readPtr();

   //---------------------------------------------------------------------------
   // Memory Members

   // Array of pointers, dynamically allocated by initialize.
   void** mArray;

   // Size of the array, number of pointers allocated.
   int mAllocate;

   //---------------------------------------------------------------------------
   // Queue Logic Members

   // Queue capacity
   static const int cCapacity = 4;
   
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
   //      0 <= WriteIndex    <= Capacity-1
   //      0 <= ReadAvailable <= Capacity
   //
   //      IF ReadAvailable == 0        THEN the queue is empty
   //      IF ReadAvailable == Capacity THEN the queue is full
   //
   //  The ReadIndex is derived from WriteIndex and ReadAvailable.
   //
   //      ReadIndex = WriteIndex - ReadAvailable;
   //      IF ReadIndex < 0 THEN ReadIndex = ReadIndex + Capacity;
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

   bool tryStartWrite (int* aWriteIndex);
   void finishWrite();

   bool tryStartRead  (int* aReadIndex);
   void finishRead();

};

//******************************************************************************

}//namespace
#endif

