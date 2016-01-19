#ifndef _LFOBJECTQUEUE_H_
#define _LFOBJECTQUEUE_H_

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace LFObjectQueue
{
   //---------------------------------------------------------------------------
   // Memory Methods

   // Allocate memory for the block array and initialize the queue logic
   // variables. It is passed the number of blocks to allocate and the size
   // of the blocks.

   void initialize(size_t aAllocateBytes);

   // Deallocate memory

   void finalize();

   //---------------------------------------------------------------------------
   // Queue State Methods

   // This is called to start a write operation. If the queue is not full then
   // it succeeds. It determines the next block to be written to, updates the 
   // queue parameters and it returns a pointer to the block to be written to. 
   // If it fails because the queue is full then it returns a null pointer.
   void* tryStartWrite(size_t aNumBytes);

   // This is called to finish a write operation. It updates the queue state.
   void finishWrite();

   // This is called to start a read operation. If the queue is not empty then
   // it succeeds. It determines the next block to be read from, updates the 
   // queue parameters and it returns a pointer to the block to be read from.
   // If it fails because the queue is empty then it returns a null pointer.
   void* tryStartRead();

   // This is called to finish a read operation. It updates the queue state.
   void finishRead();
}
#endif

