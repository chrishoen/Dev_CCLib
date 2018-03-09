#ifndef _SMSCONTAINER_H_
#define _SMSCONTAINER_H_
/*==============================================================================

// Overview

This file is the the header and template definition file for a set of
class templates that define array container classes. The array
container classes are based on statically allocated arrays of
elements.  The elements are either scalars or other
containers. Containers that are currently defined are lists, queues,
stacks, and other containers that are based on them.

Lists are arrays of elements that provide Put and Get operations to
sequentially move elements into the array and then sequentially move
elements out of the array. Lists are used to transfer data between a
producer and a consumer. The producer resets the list, performs a
sequence of Put operations on the list, and passes access to the
consumer. The consumer then performs a sequence of Get operations on
the list. Producers and consumers do not perform concurrent Puts and
Gets on a list.

Lists provide state variables that indicate whether or not Put
operations are enabled (the list is not full) and state variables that
indicate whether or not Get operations are enabled (the list is not
empty). Lists also provide state variables that are used as Put and
Get array indices. Lists contain a dual finite state machine that
implements Put and Get logic on the state variables.

Queues are arrays of elements that implement FIFOs. They provide Put
and Get operations to concurrently move elements into and out of the
array. Puts are done at the back of the queue and gets are done from
the front of the queue.

Queues provide state variables that indicate whether or not Put
operations are enabled (the queue is not full) and state variables
that indicate whether or not Get operations are enabled (the queue is
not empty). Queues also provide state variables that are used as front
and back array indices.

Queues are implemented in such a way that a queue can be used
concurrently between two threads, one of which only does queue Puts
and one of which only does queue Gets. The implementation is such that
mutual exclusion semaphores are not needed. If there are more than two
threads then semaphores are needed.

Stacks are arrays of elements that implement LIFOs. They provide Put
and Get operations to concurrently move elements into and out of the
array.

// Class Summary

BaseContainer
This is a base class for all container classes. It provides a
set of attribute member variables that are common to all containers.
The attributes maintain container status.

Array<Element,Allocate>
This class template implements an array of type Element and of size
Allocate. Container classes use the array as storage.  The array is
allocated statically at object instantiation and does not use the new
operator or any type of dynamic memory allocation.

List<Element,Allocate>
This class template implements a list of type Element and of size
Allocate. It provides members that support list Put and Get
operations, which are common to all list classes.

Queue<Element,Allocate>
This class template implements a queue of type Element and of size
Allocate. It provides members that support list Put and Get
operations, which are common to all queue classes. It contains an
array of flags, one for each element, that indicate whether or not an
Array position is occupied. Queues use these flags so that two
concurrent threads, one that puts to the queue, and one that gets from
the queue, can access the queue without using mutual exclusion
semaphores.

Trace <Element,Allocate>
This class template implements a shift register of type Element and
of size Allocate. It is used to store the last Allocate values of an
object. It traces the history of an object with a sliding window of
it's last Allocate values. It is implemented as a queue that, if it is
full after a put opertion then a Get operation on the front value is
performed automatically.


Stack<Element,Allocate>
This class template implements a stack of type Element and of size
Allocate. It provides members that support list Put and Get
operations, which are common to all stack classes.

Update<Element>
This class template implements a double buffer of type Element that
provides the most recent update of an object. The double buffer is
implemented in such a way that it can be used to transfer data from
one thread to another, in only one direction, such that it provides
the most recent update of a status object from a producer to a
consumer.  The producer puts it's most recent status to the object and
the consumer asynchronously gets the status. The producer can put it's
status at the same time that the consumer gets it, with a lock
mechanism providing mutual exclusion protection. It can be used to
transfer data from one thread to another without using mutual
exclusion semaphores. Mutual exclusion is implemented by disabling
interrupts for short periods of time. It provides members that
implement double buffer Put and Get operations.

Double<Element>
This class template implements a double buffer of type Element that
provides the an element to put to and an element to get, which is the
last element that was put to.

Allocator<Allocate> 
This class template implements a resource allocator and it it used to
allocate and deallocate the members of a finite resource set with size
Allocate.  It is implemented as a stack of resource tokens (ints) that
is reset to full (Put 0,1,2,3..Allocate-1), there being one element
for each available resource. To allocate a resource Get a token from
the stack and to deallocate a resource Put the token back on the
stack.

MemHeap<Element,Allocate>
This class template implements a heap of type Element and of size
Allocate. It is used for dynamic memory allocation of objects of type
Element that is fast and does not fragment. It allocates a static
array of type Element and of size Allocate and provides a resource
allocator to allocate and deallocate array elements. Type Element is a
class that inherits from BaseContainer and it overloads the new and
delete operators.

// Examples

// data to   a list from stdin

This example shows data input to a list from stdin.
Bytes come in from stdin until the list is full.

The loop continues to put bytes to the list until it
is no longer put enabled.

ByteList<256> ByteListRx;

void GetByteListInput(ByteListRx& BytesRx)
{
 BytesRx.reset();
 while(BytesRx.isPutEnabled()) BytesRx.Put(getch());
}

// data to   a list from stdin

This example shows data input to a list from stdin.
Bytes come in from stdin until the list is full or
escape is entered.

The loop continues to put bytes to the list until it
is no longer put enabled.

ByteList<256> ByteListRx;

void GetByteListInput(ByteListRx& BytesRx)
{
 unsigned char Byte;
 BytesRx.reset();
 while(BytesRx.isPutEnabled()){
    Byte = getch();
    if(Byte!=27) BytesRx.Put(Byte);
    else         BytesRx.stopPut();}
}

// data from a list to   stdout

This example shows data output from a list to stdout.
Bytes are extracted from the list and output to 
stdout until the list is empty.

The loop continues to get bytes from the list until it
is no longer get enabled. The loop gets a byte from the 
list and sends it to stdout.

ByteList<256> ByteListRx;

void GetByteListOutput(ByteListRx& BytesRx)
{
 BytesRx.StartGet();
 while(BytesRx.isGetAvailable()) putch(BytesRx.Get());
}

// data from a list to a list

This example shows data transferred from one list
to another. Data is transferred until either the
source is empty or the destination is full.

ByteList<256> ByteListTx;
ByteList<256> ByteListRx;

void Transfer(ByteListRx& Source,ByteListRx& Destin)
{
 Source.StartGet();
 Destin.reset(); 
 while(Source.isGetAvailable() && Destin.isPutEnabled())
    Destin.Put(Source.Get());
}

// data from a file to a list

This example shows data transferred from a file
input directly into a byte list.

typedef ByteList<1024> SFileList;
SFileList FileList;

void TransferFileToList(SFileList& List)
{
 List.reset();
 List.mPutIndex = getfile(List.Array);
}

==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Sms
{

namespace Containers
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// class BaseContainer

// This is a base class for all container classes. It provides a
// set of attribute member variables that are common to all containers. The
// attributes maintain container status.

class BaseContainer
{
public:

//******************************************************************************
// These reset all member variables.

   BaseContainer()
   {
      reset();
   }   

   void reset()
   {
      mValidFlag         = false;
   
      mFirstFlag         = false;
      mLastFlag          = false;

      mPutInProgressFlag = false;
      mGetInProgressFlag = false;

      mCountXx           = 0;
      mAckParm           = 0;

      mReqFlag           = false;
      mAcceptReqFlag     = false;
      mAckFlag           = false;
      mAcceptAckFlag     = false;
   }

//******************************************************************************
// This provides a validity flag. If the flag is true then the object
// contains valid data.

   int   isValid    () {return(mValidFlag);}
   void  setValid   () {mValidFlag = 1;}
   void  setInValid () {mValidFlag = 0;}
   bool  mValidFlag;

//******************************************************************************
// This provides a container first flag. It is used when transferring
// segmented data streams between containers of different types. If the
// flag is true then the container contains the first byte in a data
// stream segment.
// 
// This flag is used when copying one source container into a sequence of
// destination containers. If this is the first container in the sequence
// of destination containers then it contains the first byte from the
// source container and the first flag is set.
// 
// The mFirstFlag is used in conjuction with the mLastFlag.

   bool  isFirst  () {return(mFirstFlag);}
   void  setFirst () {mFirstFlag=true;}
   bool  mFirstFlag;

//******************************************************************************
// This provides a container last flag. It is used when transferring
// segmented data streams between containers of different types. If the
// flag is true then the container contains the last byte in a data
// stream segment.
// 
// This flag is used when copying one source container into a sequence of
// destination containers. If this is the last container in the sequence
// of destination containers then it contains the last byte from the
// source container and the last flag is set.
// 
// The mLastFlag is used in conjuction with the mLastFlag.

   bool  isLast    () {return(mLastFlag);}
   void  setLast   () {mLastFlag=true;}
   void  resetLast () {mLastFlag=false;}
   bool  mLastFlag;

//******************************************************************************
// This provides a container lock flag that indicates if a container
// put is in progress. If the flag is true then the container is
// currently being put to and it should not be gotten from.

   int   isPutInProgress     () {return(mPutInProgressFlag);}
   void  setPutInProgress    () {mPutInProgressFlag=1;}
   void  resetPutInProgress  () {mPutInProgressFlag=0;}
   int   mPutInProgressFlag;

//******************************************************************************
// This provides a container lock flag that indicates if a container
// get is in progress. If the flag is true then the container is
// currently being gottne from and it should not be put to.

   bool  isGetInProgress     () {return(mGetInProgressFlag);}
   void  setGetInProgress    () {mGetInProgressFlag=true;}
   void  resetGetInProgress  () {mGetInProgressFlag=false;}
   bool  mGetInProgressFlag;

//******************************************************************************
// This provides a two way handshake between a client and a server.
// The client requests a service, the server accepts the request, the
// server performs the service, the server acknowledges the request, and
// the client accepts the acknowledgement.

//******************************************************************************
// This is the request for service from the client to the server. The
// client sets the request flag to request the service. The server
// accepts the request by setting the accept flag and resetting the
// request flag.

   void resetReq ()
   {
      mReqFlag       = false;
      mAcceptReqFlag = false;
   }
   
   void setReq() 
   {
      mReqFlag       = true;
      mAcceptReqFlag = false;
      mAckFlag       = false;
   }

   bool isReq()
   {
      return(mReqFlag);
   }
   
   bool acceptReq()
   {
      if(mReqFlag)
      {
         mReqFlag=false;
         mAcceptReqFlag=true;
         return(true);
      }
      else
      {
         return(false);
      }
   }
   
   bool isAcceptReq()
   {
      return(mAcceptReqFlag);
   }

   bool  mReqFlag;
   bool  mAcceptReqFlag;

//******************************************************************************
// This is the acknowledgement of service by the server to the client.
// The server sets the acknowledge flag to acknowledge the service. The
// clent accepts the acknowledge by setting the accept flag and resetting
// the acknowledge flag.

   void resetAck ()
   {
      mAckFlag       = false;
      mAcceptAckFlag = false;
   }
   
   void setAck() 
   {
      mAckFlag       = true;
      mAcceptAckFlag = false;
      mAckFlag       = false;
   }
   
   bool isAck()
   {
      return(mAckFlag);
   }
   
   bool acceptAck()
   {
      if(mAckFlag)
      {
         mAckFlag=0;
         mAcceptAckFlag=1;
         return(true);
      }
      else
      {
         return(false);
      }
   }
   
   bool isAcceptAck()
   {
      return(mAcceptAckFlag);
   }

   bool mAckFlag;
   bool mAcceptAckFlag;

//******************************************************************************
// These are various container parameters. These are a count of the
// number of times a container has been transferred, and an acknowledge
// parameter, which is an indication of the number of iterations that
// remain before an acknowledge is expected.

   int mCountXx;
   int mAckParm;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// class template Array <Element,Allocate>

// This class template implements an array of type Element and of size
// Allocate. Container classes use the array as storage.  The array is
// allocated statically at object instantiation and does not use the new
// operator or any type of dynamic memory allocation.
// 
// Array classes have member variables mBeginIndex and mEndIndex that are
// lower and upper bounds on array elements that can contain valid
// data. Data indices can access array data in the closed interval
// [mBeginIndex,mEndIndex] where
// 
//   0 =< mBeginIndex =< DataIndex =< mEndIndex =< Allocate-1
// 
// This feature is provided to implement packets that have header storage
// allocated at the beginning of the array and have variable length
// maximum transmission unit size which can be less than Allocate.


template <class Element,int Allocate>
class Array : public BaseContainer
{
public:

   Array()
   {
      reset();
   }
   
   void reset()
   {
      mBeginIndex = 0;
      mEndIndex   = Allocate-1;
      BaseContainer::reset();
   }
   
   void setBeginIndex(int index)
   {
      mBeginIndex = index;
   }

   int mBeginIndex;

   void setEndIndex(int index)
   {
      mEndIndex = index;
   }

   int mEndIndex;

   int capacity()
   {
      return( mEndIndex - mBeginIndex + 1);
   }

   Element mArray[Allocate];
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// class template List <Element,Allocate>

// This class template implements a list of type Element and of size
// Allocate. It provides members that implement list Put and Get
// operations, which are common to all container list classes.  Put and
// Get operations use Element references. It provides members that give
// direct access to the list Put and Get Elements so that Puts and Gets
// can be performed with minimum copying.

template <class Element,int Allocate>
class List : public Array<Element,Allocate>
{
public:

   List()
   {
      reset();
   }
   
   void reset ()
   {
      Array<Element,Allocate>::reset();
        
      mPutIndex = mBeginIndex;
      mPutFlag  = true;
      mGetIndex = mBeginIndex;
      mGetFlag  = false; 
   }
   
   bool isEmpty()
   {
      return(mPutIndex==mBeginIndex);
   }
   
   bool isFull()
   {
      return(mPutIndex>mEndIndex);
   }

//******************************************************************************
// This returns true if Put operations are enabled for the list. Put
// and Get operations cannot be enabled at the same time.

   bool isPutEnabled()
   {
      return(mPutFlag);
   }

//******************************************************************************
// This is executed before starting array Put operations. Put
// operations are enabled, mPutIndex is set to the beginning of data in
// the array, and Get operations for the array are disabled to guard
// against concurrent Puts and Gets. This does not need to be called if
// reset is called, these assignments are contained in reset, which
// automaitally starts the list for Put operations.

   void startPut()
   {
      mPutFlag  = true;
      mPutIndex = mBeginIndex;
      mGetFlag  = false;
   }

//******************************************************************************
// This is executed to disable array Put operations. Lists are filled
// with sequences of consecutive Put operations. If the Put sequence
// terminates before reaching the end of the array data interval then
// this is called to disable further Puts. If the Put sequence does reach
// the end of the interval then Puts are automatically disabled and this
// does not need to be called.

   void stopPut()
   {
      mPutFlag = false;
   }

//******************************************************************************
// This is executed after every Put operation to advance the Put
// state. If Put operations are enabled then it increments mPutIndex to
// point to the next array position to be Put to. If mPutIndex has reached
// the end of the array data interval then further Put operations are
// disabled.

   void nextPut()
   {
      if(mPutFlag)
      {
         if(++mPutIndex>mEndIndex)
         {
            mPutFlag=false;
         }
      }
   }

//******************************************************************************
// This is the Put operation enable flag. If it is true then Puts are
// enabled for the list. If it is false then Puts are ignored.

   bool mPutFlag;

//******************************************************************************
// This is the Put operation array index. If Puts are enabled then it
// contains the array position of the next Put to be performed.
// 
// This index can vary over
//    
//    mBeginIndex =< mPutIndex =< mEndIndex+1
// 
// Valid Puts can be performed on the interval
// 
//    mBeginIndex =< mPutIndex =< mEndIndex
// 
// If mPutIndex = mEndIndex+1 then the previous Put reached the end of the
// array data interval and Puts are disabled.

   int mPutIndex;

//******************************************************************************
// If Put operations are enabled for the list then this Puts an
// element to the array list at the current Put position and advances the
// Put state.

   void put(const Element& value)
   {
      if(mPutFlag)
      {
         mArray[mPutIndex] = value;
         nextPut();
      }
   }

//******************************************************************************
// This returns a reference that points to the current array position
// to Put to. It is provided to give direct access to the Put element to
// minimize copies. If an element is Put directly to the list array by
// using this reference then nextPut should be called after the direct
// Put operation.

   Element& backElement()
   {
      return(mArray[mPutIndex]);
   }

//******************************************************************************
// This refects the current size of the list. It is the number of
// elements that have been Put, mPutIndex - mBeginIndex.

   int size()
   {
      return(mPutIndex - mBeginIndex);
   }

//******************************************************************************
// This returns true if Get operations are enabled for the list. Put
// and Get operations cannot be enabled at the same time.

   bool isGetAvailable()
   {
      return(mGetFlag);
   }

//******************************************************************************
// This is executed before starting array Get operations. Get
// operations are enabled, mGetIndex is set to the beginning of data in
// the array, and Put operations for the array are disabled to guard
// against concurrent Puts and Gets.

   void startGet()
   {
      mGetFlag  = true;
      mGetIndex = mBeginIndex;
      mPutFlag  = false;
      if(mPutIndex==mBeginIndex)
      {
         mGetFlag=false;
      }
   }

//******************************************************************************
// This is executed to disable array Get operations. Lists are emptied
// with sequences of consecutive Get operations that range from the
// beginning of the array data interval to the array index where the last
// Put operation took place. If the Get sequence terminates before
// reaching the end of the array Put sequence then this is called to
// disable further Gets. If the Get sequence does reach the end of the
// array Put sequence then Gets are automatically disabled and this does
// not need to be called.

   void stopGet()
   {
      mGetFlag = false;
   }

//******************************************************************************
// This is executed after every Get operation to advance the Get
// state. If Get operations are enabled then it increments mGetIndex to
// point to the next array position to be Gotten from. If mGetIndex has
// reached mPutIndex then all data elements that were previously Put have
// been Gotten and further Get operations are disabled.

   void nextGet()
   {
      if(mGetFlag)
      {
         if(++mGetIndex>=mPutIndex)
         {
            mGetFlag = false; 
         }
      }
   }

//******************************************************************************
// This is the Get operation enable flag. If it is true then Gets are
// enabled for the list. If it is false then Gets are ignored.

   bool mGetFlag;

//******************************************************************************
// This is the Get operation array index. If Gets are enabled then it
// contains the array position of the next Get to be performed.
// 
// This index can vary over
//    
//    mBeginIndex =< mGetIndex =< mPutIndex =< mEndIndex+1
// 
// Valid Gets can be performed on the interval
// 
//    mBeginIndex =< mGetIndex < mPutIndex
// 
// If mGetIndex = mPutIndex then all array data elements that were
// previously Put have been Gotten and further Gets are disabled.

   int mGetIndex;

//******************************************************************************
// If Get operations are enabled for the list then this Gets an
// element from the array list at the current Get position and advances
// the Get state and returns the gotten element. If Get operations are
// not enabled then this returns an the last element. This should not be
// called unless Get operations are enabled.

   Element& get()
   {
      if(mGetFlag)
      {
         int tempIndex = mGetIndex;
         nextGet();
         return(mArray[tempIndex]);
      }
      else
      {
         return(mArray[mEndIndex]);
      }
   }

//******************************************************************************
// This returns a reference that points to the current array position
// to Get from. It is provided to give direct access to the Get element
// to minimize copies. If an element is gotten directly from the list
// array by using this reference then nextGet should be called after the
// direct Get operation.

   Element& frontElement()
   {
     return(mArray[mGetIndex]);
   }

//******************************************************************************
// This returns the element at the array begin index.

   Element& begin()
   {
      return(mArray[mBeginIndex]);
   }

//******************************************************************************
// This returns the element at the array end index.

   Element& end()
   {
     return(mArray[mEndIndex]);
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// class template Queue <Element,Allocate>

// This class template implements a queue of type Element and of size
// Allocate. It provides members that implement queue Put and Get
// operations, which are common to all container queue classes. Put and
// Get operations use Element references. It provides members that give
// direct access to the queue Put and Get Elements so that Puts and Gets
// can be performed with minimum copying.

template <class Element,int Allocate>
class Queue : public Array<Element,1+Allocate>
{
public:

//******************************************************************************
// These reset all member variables.

   Queue()
   {
      reset();
   }

   void reset ()
   {
      Array<Element,Allocate+1>::reset();
      for(int i=0;i<Allocate+1;i++) mOccupyFlag[i] = 0;
    
      mPutIndex   = mBeginIndex;
      mGetIndex   = mBeginIndex;
      mNullIndex  = mEndIndex;
      mOccupyFlag[mEndIndex] = 1;
   }

//******************************************************************************
// This returns true if the queue is put enabled. If Put operations
// are enabled and if the element at the back index is not occupied then
// the queue is not full and is enabled for a put operation at the back
// index.

   int isPutEnabled()
   {
      return(!mOccupyFlag[mPutIndex]);
   }
   
   bool isNotFull()
   {
      return(mOccupyFlag[mPutIndex]==0);
   }
   
   bool isFull()
   {
      return(mOccupyFlag[mPutIndex]!=0);
   }

//******************************************************************************
// This is executed after a put operation to advance the queue back
// state. If Put operations are not enabled then it returns. It sets the
// queue array element that was Put to occupied. It increments the queue
// array back index around the queue array end index to point to the next
// array element that is to be Put.

   void nextPut()
   {
      mOccupyFlag[mPutIndex] = 1;
      if(++mPutIndex>mEndIndex)
      {
         mPutIndex=mBeginIndex;
      }
   }

//******************************************************************************
// This is the array index of the back of the queue, where Put
// operations take place.
// 
//    mBeginIndex =< mPutIndex =< mEndIndex

   int   mPutIndex;

//******************************************************************************
// If Put operations are enabled for the list then this Puts an
// element to the array list at the current back position and advances
// the queue back state.

   bool put(const Element & value)
   {
     if(isPutEnabled())
     {
        mArray[mPutIndex] = value;
        nextPut();
        return true;
     }
     return false;
   }

//******************************************************************************
// This returns a reference that points to the current queue back
// array position. It is provided to give direct access to the Put
// element to minimize copies. If an element is Put directly to the queue
// array by using this reference then nextPut should be called after the
// direct Put operation.

   Element& backElement()
   {
      return(mArray[mPutIndex]);
   }

//******************************************************************************
// This returns true if the queue is get enabled. If the element at
// the front index is occupied then the queue is not empty and is enabled
// for a get operation at the front index.

   bool isGetAvailable()
   {
      return(mOccupyFlag[mGetIndex]!=0);
   }
   
   bool isNotEmpty()
   {
      return(mOccupyFlag[mGetIndex]!=0);
   }
   
   bool isEmpty()
   {
      return(mOccupyFlag[mGetIndex]==0);
   }

//******************************************************************************
// This is executed after a get operation to advance the queue front
// state. It sets the element at the queue null index to not occupied
// (which makes it available for Put operations), sets the null index to
// the current front index (to protect the queue front from being Put to
// until after the next Get), and increments the queue array front index
// around the queue array end index to point to the next array element to
// get from.

   void nextGet()
   {
      mOccupyFlag[mNullIndex] = 0;
      mNullIndex = mGetIndex;
      if(++mGetIndex>mEndIndex)
      {
         mGetIndex=mBeginIndex;
      }
   }

//******************************************************************************
// This is the array index of the front of the queue, where Get
// operations take place.
// 
//    mBeginIndex =< mGetIndex =< mEndIndex

   int mGetIndex;

//******************************************************************************
// This is the array index of the array element that is before the
// front of the queue. This element is a null place holder. Its purpose
// is to guarentee that the last element at the front that was Gotten
// cannot be Put to until the end of the next Get operation.
// 
//     mNullIndex = (mGetIndex - 1) % (mEndIndex - mBeginIndex + 1)

   int mNullIndex;

//******************************************************************************
// If Get operations are enabled for the queue then this Gets an
// element from the array list at the current front position and advances
// the front state and returns the gotten element. If Get operations are
// not enabled then this returns an element that has been reset. This
// should not be called unless Get operations are enabled. This stores
// the element returned in tempGetElement, which requires an extra copy.

   Element& get()
   {
      int tempIndex = mGetIndex;
      if(isGetAvailable())
      {
         nextGet();
      }
      return(mArray[tempIndex]);
   }

//******************************************************************************
// This returns a reference that points to the current queue front
// array position. It is provided to give direct access to the Get
// element to minimize copies. If an element is Gotten directly from the
// queue array by using this reference then nextGet should be called
// after the direct Get operation.

   Element& frontElement()
   {
      return(mArray[mGetIndex]);
   }

//******************************************************************************
// This is an array of occupation flags, there is one flag for each
// element in the queue array. If an array element is occupied then it
// contains a valid data element. If the array element at the queue back
// is not occupied then a new element can be Put to the queue back. If it
// is occupied then the queue is full. If the array element at the queue
// front is occupied then it and element can be Gotten from the queue
// front. If it is not occupied then the queue is empty. The last thing
// to be done after a Put operation is to set the back position to
// occupied and the last thing to be done after a Get operation is to set
// the front element to not occupied. Queues contain a null element
// located at the null index. Its purpose is to guarentee that an element
// that has been gotten cannot be put to until the end of the next get
// operation (as in the case of two concurrent threads). This means that
// the queue only uses Alloacte-1 elements.

   unsigned char mOccupyFlag[1+Allocate];

//******************************************************************************
// This is the current size of the queue. It is the diffenece between
// the mPutIndex and the mGetIndex.

   int size()
   {
      return((Allocate+1+mPutIndex-mGetIndex)%(Allocate+1));
   }

};
//******************************************************************************
//******************************************************************************
//******************************************************************************
// class template Trace <Element,Allocate>

//******************************************************************************
// This class template implements a shift register of type Element and
// of size Allocate. It is used to store the last Allocate values of an
// object. It traces the history of an object with a sliding window of
// it's last Allocate values. It is implemented as a queue that, if it is
// full after a put opertion then a Get operation on the front value is
// performed automatically.

template <class Element,int Allocate>
class Trace : public Queue<Element,1+Allocate>
{
public:

//******************************************************************************
// This advances the queue put state. If the queue is full then it
// advances the queue get state to shift the queue.

   void nextPut()
   {
      Queue<Element,Allocate+1>::nextPut();
      if(!isPutEnabled())
      {
         nextGet();
      }
    }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// class template Stack <Element,Allocate>

//******************************************************************************
// This class template implements a stack of type Element and of size
// Allocate. The stack does not mutex protection.

template <class Element,int Allocate>
class Stack : public Array<Element,Allocate>
{
public:

   Stack()
   {
      reset();
   }
   
   void reset ()
   {
      Array<Element,Allocate>::reset();
      mIndex = mBeginIndex;
   }


//******************************************************************************
// This returns true if Put operations are enabled for the stack.

   bool isPutEnabled()
   {
      return(mIndex<=mEndIndex);
   }

//******************************************************************************
// This is executed after every Put operation to advance the Put
// state. It increments Index to point to the next array position to be
// Put to. If mPutIndex has reached the end of the array data interval
// then further Put operations are disabled.

   void nextPut()
   {
      mIndex++;
   }

//******************************************************************************
// If Put operations are enabled for the stack then this Puts an
// element to the stack array at the current Index and advances the Put
// state.

   void put(const Element& value)
   {
      if(mIndex<=mEndIndex)
      {
         mArray[mIndex++] = value;
      }
   }

//******************************************************************************
// This returns a reference that points to the current array position
// to Put to. It is provided to give direct access to the Put element to
// minimize copies. If an element is Put directly to the stack array by
// using this reference then nextPut should be called after the direct
// Put operation.
 
   Element& backElement()
   {
      return(mArray[mIndex]);
   }

//******************************************************************************
// This returns true if Get operations are enabled for the stack. Put
// and Get operations cannot be enabled at the same time.

   bool isGetAvailable()
   {
      return(mIndex>mBeginIndex);
   }

//******************************************************************************
// This is executed after every Get operation to advance the Get
// state. It increments mGetIndex to point to the next array position to
// be Gotten from. If mGetIndex has reached mPutIndex then all data
// elements that were previously Put have been Gooten and further Get
// operations are disabled.

   void nextGet()
   {
      if(Index>mBeginIndex)
      {
         mIndex--;
      }
   }

//******************************************************************************
// If Get operations are enabled for the stack then this Gets an
// element from the array stack at the current Get position and advances
// the Get state and returns the gotten element. If Get operations are
// not enabled then this returns an the last element. This should not be
// called unless Get operations are enabled.

   Element& get()
   {
      if(mIndex>mBeginIndex)
      {
         mIndex--;
         return(mArray[mIndex]);
      }
      else
      {
         return(mArray[mBeginIndex]);
      }
   }

//******************************************************************************
// This returns a reference that points to the current array position
// to Get from. It is provided to give direct access to the Get element
// to minimize copies. If an element is gotten directly from the stack
// array by using this reference then nextGet should be called after the
// direct Get operation.

   Element& frontElement()
   {
      return(mArray[mIndex-1]);
   }

  // This is the stack pointer. 

  int mIndex;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// class template Update <Element>

//******************************************************************************
// This class template implements a double buffer of type Element that
// provides the most recent update of an object. The double buffer is
// implemented in such a way that it can be used to transfer data from
// one thread to another, in only one direction, such that it provides
// the most recent update of a status object from a producer to a
// consumer.  The producer puts it's most recent status to the object and
// the consumer asynchronously gets the status. The producer can put it's
// status at the same time that the consumer gets it, with a lock
// mechanism providing mutual exclusion protection. It can be used to
// transfer data from one thread to another without using mutual
// exclusion semaphores. Mutual exclusion is implemented by disabling
// interrupts for short periods of time. It provides members that
// implement double buffer Put and Get operations.

template <class Element>
class Update : public Array<Element,2>
{
public:

   Update()
   {
      reset();
   }
   
   void reset ()
   {
      Array<Element,2>::reset();
       
      mPutIndex = 0;
      mPutFlag  = false;
      mGetIndex = 0;
      mGetFlag  = false; 
   }

//******************************************************************************
// This is executed before starting double buffer Put operations. It
// sets mPutFlag to indicate that a Put operation is currently in
// progress. If a Get operation is not currently in progress then it
// switches the Put Index.  If a Get operation is currently in progress
// then it sets the Put Index to the array index not being Gotten from.
// Interrupts are disabled during execution of this function.

   void startPut()
   {
      mPutFlag = true;
      if(!mGetFlag)
      {
         if(mPutIndex==0)
         {
            mPutIndex=1;
         }
         else
         {
            mPutIndex=0;
         }
      }
      else
      {
         if(mGetIndex==0)
         {
            mPutIndex=1;
         }
         else
         {
            mPutIndex=0;
         }
      }
   }

//******************************************************************************
// This is executed after a Put operation is complete. It sets the
// mPutFlag false to indicate that a Put operation is not currently in
// progress. Interrupts are disabled during execution of this function.

   void stopPut()
   {
      mPutFlag = false;
   }

//******************************************************************************
// If this flag is true then a put operation is currently in progress.

   bool mPutFlag;

//******************************************************************************
// This is the Put operation array index. If a Put operation is
// currently in progress then this is the array index that is being Put
// to. If a Put operation is not currently in progress then this is the
// array index of the last Put operation.

   int mPutIndex;

//******************************************************************************
// This returns a reference that points to the current array position
// to Put to. It is provided to give direct access to the Put element to
// minimize copies.
 
   Element& backElement()
   {
      return(mArray[mPutIndex]);
   }

//******************************************************************************
// This is executed before starting double buffer Get operations. It
// sets mGetFlag to indicate that a Get operation is currently in
// progress. If a Put operation is not currently in progress then it sets
// the mGetIndex to the last mPutIndex.  If a Put operation is currently in
// progress then it sets the mGetIndex to the array index not being Put
// to. Interrupts are disabled during execution of this function.

   void startGet()
   {
      mGetFlag = true;
      if(!mPutFlag)
      {
         mGetIndex=mPutIndex;
      }
      else
      {
         if(mPutIndex==0)
         {
            mGetIndex=1;
         }
         else
         {
            mGetIndex=0;
         }
      }
   }

//******************************************************************************
// This is executed after a Get operation is complete. It sets the
// mGetFlag false to indicate that a Get operation is not currently in
// progress. Interrupts are disabled during execution of this function.

   void stopGet()
   {
      mGetFlag  = false;
   }

//******************************************************************************
// If this flag is true then a get operation is currently in progress.

   bool mGetFlag;

//******************************************************************************
// This is the Get operation array index. If a Get operation is
// currently in progress then this is the array index that is being Get
// to. If a Get operation is not currently in progress then this is the
// array index of the last Get operation.

   int mGetIndex;

//******************************************************************************
// This returns a reference that points to the current array position
// to Get from. It is provided to give direct access to the Get element
// to minimize copies.

   Element& frontElement()
   {
      return(mArray[mGetIndex]);
   }

};
//******************************************************************************
//******************************************************************************
//******************************************************************************
// class template Double <Element>

//******************************************************************************
// This class template implements a double buffer of type Element that
// provides the an element to put to and an element to get, which is the
// last element that was put to.

template <class Element>
class Double : public Array<Element,2>
{
public:

   Double()
   {
      reset();
   }
   
   void reset ()
   {
      Array<Element,2>::reset();
        
      mPutIndex = 0;
      mGetIndex = 1;
   }

//******************************************************************************
// These return references to the current double buffer elements to
// put to and get from.

   Element& backElement(){return(mArray[mPutIndex]);}  
   Element& frontElement(){return(mArray[mGetIndex]);}

   int mPutIndex;
   int mGetIndex;

//******************************************************************************
// This swaps the put and get elements.

   void nextPut()
   {
      int temp  = mPutIndex;
      mPutIndex = mGetIndex;
      mGetIndex = temp;
   }
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// class template Allocator <Allocate>

//******************************************************************************
// This class template implements a resource allocator and it it used
// to allocate and deallocate the members of a finite resource set of
// size Allocate. It is implemented as a stack of resource tokens (ints)
// that is reset to full (Put 0,1,2,3..Allocate-1), there being one
// token for each available resource. To determine if a resource is
// available, test isGetAvailable(), to allocate a resource Token = Get() from the
// stack and to deallocate a resource Put(Token) the token back on the
// stack.

template <int Allocate>
class Allocator : public Array<int,Allocate>
{
public:

   Allocator()
   {
      reset();
   }
   
   void reset ()
   {
      Array<int,Allocate>::reset();
      mIndex   = 0;
      for(int token=Allocate-1;token>=0;--token) put(token);  
      mNumPuts = 0;
      mNumGets = 0;
   }

//******************************************************************************
// This returns true if Put operations are enabled for the stack.

   bool isPutEnabled()
   {
      return(mIndex<=mEndIndex);
   }

//******************************************************************************
// If Put operations are enabled for the stack then this Puts an
// integer to the stack array at the current Index and advances the Put
// state.

   void put(int value)
   {
      if(mIndex<=mEndIndex)
      {
         mArray[mIndex++] = value;
         mNumPuts++;
      }
   }

//******************************************************************************
// This returns true if Get operations are enabled for the stack.

   bool isGetAvailable()
   {
      return(Index>mBeginIndex);
   }

//******************************************************************************
// If Get operations are enabled for the stack then this Gets an
// integer from the stack array at the current Get position and advances
// the Get state and returns the gotten integer. If Get operations are
// not enabled then this returns a -1. This should not be called unless
// Get operations are enabled.

   int get()
   {
      int temp = -1;
      if(mIndex>mBeginIndex)
      {
         temp = mArray[--mIndex];
         mNumGets++;
      }
      return(temp);
   }

//******************************************************************************
// This is the stack pointer.

  int mIndex;

//******************************************************************************
// These are the numbers of puts and gets that have occurred.

  int mNumPuts;
  int mNumGets;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// class template MemHeap <Element,Allocate>

//******************************************************************************
// This class template implements a heap of type Element and of size
// Allocate. It is used for dynamic memory allocation of objects of type
// Element that is fast and does not fragment. It allocates a static
// array of type Element and of size Allocate and provides a resource
// allocator to allocate and deallocate array elements. Type Element is a
// class that inherits from BaseContainer and it overloads the new and
// delete operators.

template <class Element,int Allocate>
class MemHeap : public Array<Element,Allocate>
{
public:

   MemHeap()
   {
     reset();
   }
   
   void reset ()
   {
     Array<Element,Allocate>::reset();
     for(int i=0;i<Allocate;i++)
     {
        mArray[i].reset();
     }
     mAllocator.reset();
   }

//******************************************************************************
// This is a resource allocator and it it used to allocate and
// deallocate the heap array elements.

  Allocator<Allocate> mAllocator;

};

} //namespace
} //namespace

#endif

