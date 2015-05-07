#ifndef _CCMESSAGEHEAP_H_
#define _CCMESSAGEHEAP_H_
/*==============================================================================


==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include <stddef.h>

namespace CC
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

class MessageHeap
{
public:
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Constructor

   // This initializes member variables to null values. The message heap does
   // not have memory allocated for it until initialize is called.
   MessageHeap ();

   // This deallocates system memory that was allocated for the message heap.
  ~MessageHeap ();

   //---------------------------------------------------------------------------
   // Initialize
    
   // This allocates system memory for the message heap and initializes member
   // variables. It is passed the number of bytes of system memory to allocate
   // for the message heap.
   void initialize (size_t aAllocate);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Member variables

   // This is a pointer to the begining of the system memory that is allocated
   // for the message heap.
   char* mHeapBeginPtr;

   // This is a pointer to one byte after the end of the message heap. It is 
   // equal to mmHeapBeginPtr + mAllocate.
   char* mHeapEndPtr;

   // This is a pointer that cycles through the message heap memory, when
   // messages are allocated. Its current value points at the next available 
   // section of the heap. When memory is allocated from the heap, the current
   // value is returned and the pointer is incremented apprpriately. If there 
   // is a rollover, then it is set back to point to the beginining of the heap.
   char* mWorkingPtr;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Allocate

   // This allocates a variable sized segment of memory from the message heap.
   // It is used analogously to malloc. For 32 bit systems, it allocates on
   // an eight byte boundary. For 64 bit systems, it allocates on a sixteen
   // byte boundary.
   void* allocate(size_t aSize);

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // This is a header that is placed at the start of every message that is 
   // allocated from the message heap. This header is only used by message
   // heap processing and has nothing to do with actual message headers.
   // Values of this structure are set when a message is allocated and they
   // are tested when a message is checked for consistency.

   typedef struct Header
   {
      // This is a synch word, if it is not correct then the message has been
      // corrupted, the message heap has been overrun.
      unsigned mSyncWord;
      
      // This is a sequence number for the message. It is assigned when the
      // message is allocated.
      unsigned mSequenceNumber;

      // This is a pointer to the previous message in the message heap, the
      // last message that was allocated before this message. The sequence 
      // number of the previous message should be one more than the sequence
      // number of a message that is being checked.
      Header* mPreviousMessageHeader;

   }  Header;

   // This structure must not take up more than sixteen bytes.
   enum { HeaderAllocate = 16 };

   // This is the value for the sync word.
   enum { HeaderSyncWord = 0xAAAABBBB };

   // This is a sequence number that is inserted into the header of any
   // message that is allocated. It is used for consistency checks.
   unsigned mSequenceNumber;

   // This is a pointer to the header of the previous message that was 
   // allocated. It is used to compare its sequence number with that of a
   // a message that is being checked.
   Header* mPreviousMessageHeader;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Check

   // This checks a memory segment for consistency, it should show if a message
   // in the heap has been overrun. It returns true if the memory seqgment was
   // found to be consistent.

   bool check(void* aMessage);
};
//******************************************************************************
}//namespace
#endif

