#ifndef _CCMEMORYPTR_H_
#define _CCMEMORYPTR_H_

/*==============================================================================
Memory pointer class.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Memory Pointer class.

class MemoryPtr
{
public:
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // Memory pointer.
   void* mMemoryPtr;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Constructors.

   MemoryPtr();
   MemoryPtr(void* aMemoryPtr);
   void set(void* aMemoryPtr);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Get memory pointer value.

   void* vfetch();
   char* cfetch();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Null pointer value.

   void setNull();
   bool isNull();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Add a number of bytes to the memory pointer.
   // Return the original memory pointer as a void*.
   // This changes the memory pointer.

   void* vfetch_add(int aNumBytes);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Add a number of bytes to the memory pointer.
   // Return the original memory pointer as a char*.
   // This changes the memory pointer.

   char* cfetch_add(int aNumBytes);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Subtract a number of bytes from the memory pointer.
   // Return the original memory pointer as a void*.
   // This changes the memory pointer.

   void* vfetch_sub(int aNumBytes);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Subtract a number of bytes from the memory pointer.
   // Return the original memory pointer as a char*.
   // This changes the memory pointer.

   char* cfetch_sub(int aNumBytes);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Return the memory pointer plus a number of bytes as a void*.
   // This does not change the memory pointer.

   void* vplus(int aNumBytes);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Return the memory pointer plus a number of bytes as a char*.
   // This does not change the memory pointer.

   char* cplus(int aNumBytes);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Return the memory pointer minus a number of bytes as a void*.
   // This does not change the memory pointer.

   void* vminus(int aNumBytes);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Return the memory pointer minus a number of bytes as a char*.
   // This does not change the memory pointer.

   char* cminus(int aNumBytes);

};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
#endif