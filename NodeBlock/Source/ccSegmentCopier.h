#ifndef _SEGMENTCOPIER_H_
#define _SEGMENTCOPIER_H_
/*==============================================================================

This defines a stack of void* pointers. It can be used by specialized heaps
and pools as an allocator.

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

template <class Element>
class SegmentCopier
{
public:
   //---------------------------------------------------------------------------
   // Methods

   // Constructor
   SegmentCopier()
   {
      mSegment      = 0;
      mNumOfElementsInSegment  = 0;
      mNumOfElementsInFragment = 0;
      mSegmentIndex = 0;
   }

   void initialize(
      Element* aSegment,
      int      aNumOfElementsInSegment,
      int      aNumOfElementsInFragment)
   {
      mSegment      = aSegment;
      mNumOfElementsInSegment  = amNumOfElementsInSegment;
      mNumOfElementsInFragment = aNumOfElementsInFragment;
      mSegmentIndex = 0;
   }

   void copyFragmentToSegment(Element* aFragment)
   {
      for (i = 0; i < mNumOfElementsInFragment;i++)
      { 
         if (mSegmentIndex < mNumOfElementsInSegment - 1)
         {
            mSegment[mSegmentIndex++] = aFragment[i];
         }
      }
   }

   //---------------------------------------------------------------------------
   // Members

   Element* mSegment;
   int      mNumOfElementsInSegment;
   int      mNumOfElementsInFragment;
   int      mSegmentIndex;
};

//******************************************************************************

}//namespace
#endif

