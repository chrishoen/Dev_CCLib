#ifndef _CCSHORTTERMMEMORY_H_
#define _CCSHORTTERMMEMORY_H_
/*==============================================================================

ByteContent and ByteBuffer classes.

ByteBuffer is a smart pointer that addresses a fixed section of memory.

ByteContent is a base class for something that can be copied to/from a
ByteBuffer.

These classes are intended to support the construction of message classes.
The idea here is that each message is encapsulated by a class that inherits
from ByteContent and supplies a member function that allows it to be copied
to/from a ByteBuffer, which can be transported via some communications
medium. All copies are done in network order. 

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************


namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This class encapsualtes byte buffers. It represents memory sections. It
// provides member functions to do some simple memory management for a buffer.
// It provides primitive data type put and get operations that allow primitives
// to be copied to/from a byte buffer in network order. It also provides "copy"
// member functions that either put to a buffer or get from a buffer, based on
// a copy direction flag.
//
// This class maintains a buffer base pointer, which contains the base address
// of the buffer, a buffer working pointer, which contains an addresss within
// the buffer where the next put or get operation will be performed. It also
// maintains a buffer length, which contains the number of bytes that have
// been put into the buffer.

class ShortTermMemory
{
public:
   //-------------------------------------------------------------
   // structors.

   // no memory allocated or assigned
   //
   // this constructor          does not do a memory alloc operation.
   // its associated destructor does not do a memory free  operation.
   ShortTermMemory ();

   // assigns pre-allocated memory
   //
   // this constructor          does not do a memory alloc operation.
   // its associated destructor does not do a memory free  operation.
   ShortTermMemory (char* address,int size);

   // allocates memory of given size  
   // 
   // this constructor          does do a memory alloc operation.
   // its associated destructor does do a memory free  operation.
   // If fill zero is true then all bytes are set to zero.
   ShortTermMemory (int size,bool fillZero=false);

   //-------------------------------------------------------------
   // simple memory management.
   // if allocated then destructor frees it

   void  memAlloc (int size);
   void  memFree  ();

   //-------------------------------------------------------------
   // buffer maximum size
   int getMaxLength();

   //-------------------------------------------------------------
   // buffer base address.

   void  setBaseAddress (char* address,int size);
   char* getBaseAddress ();

   //-------------------------------------------------------------
   // buffer length. This is the number of bytes that have
   // actually been put into the buffer, the actual data length.

   void setLength(int value);
   int  getLength();

   //-------------------------------------------------------------
   // pointer operations.
   // reset sets the working pointer to the base address and
   // sets the length to zero.
   // rewind sets the working pointer to the base address
   // forward advances the working pointer and the length, if the
   // copy direction is for a put operation.
   // advance advances the working pointer and the length

   void  reset();
   void  rewind();
   void  forward     (int byteSize=1);
   void  advance     (int byteSize=1);
   void  fillZero    (int byteSize=1);

   //-------------------------------------------------------------
   // Show

   void  show();

   //-------------------------------------------------------------
   // buffer position.

   // these set the buffer working pointer.
   bool  setPosition (char* address);
   bool  setPosition (int index);

   // these get the buffer working pointer.
   char* getPosition ();
   char* getPositionC();
   void* getPositionV();

protected:

   //-------------------------------------------------------------
   // pointer members.
   // The base pointer contains the address of the beginning of the
   // buffer. The working pointer contains the address in the buffer
   // to which the next put or get operation will operate. The
   // working length contains the number of bytes that have been put
   // into the buffer. The max length is maxlength of the buffer,
   // it is the size allocated for the buffer

   char* mBasePtr;
   char* mWorkingPtr;
   int   mWorkingLength;
   int   mMaxLength;

   //-------------------------------------------------------------
   // Memory allocation code,
   // determines if the destructor does a memFree.

   int mMemAllocCode;
};
//******************************************************************************
}//namespace
#endif

