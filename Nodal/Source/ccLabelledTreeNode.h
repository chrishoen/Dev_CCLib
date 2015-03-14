#ifndef _CCLabelledTreeNode_H_
#define _CCLabelledTreeNode_H_

#include "ccTreeNode.h"
#include "ccDefs.h"
#include "ccBlockUniverse.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

class LabelledTreeNode : public TreeNode
{
public:
   typedef TreeNode BaseClass;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Memory management, constructors and destructors

   // Static member block universe. It contains a short term and a long term
   // block pool. These block pools, or system memory, are used to establish
   // memory for all instances of this class that are created within a process.
   // The block universe must be initialized at the beginning of a process, 
   // prior to any block creation.

   static CC::BlockUniverse mBlockUniverse;

   // This static method initializes the block universe. In a process, it must
   // be called prior to any block creations. It initializes the block universe
   // short term and long term block pools.

   static void initializeBlockUniverse(
      int aAllocateShortTermBlocks,
      int aAllocateLongTermBlocks);

   // This static method allocates a block from system memory or from block
   // universe short term or long term memory block pools. After allocation,
   // it calls the class constructor on the allocated block. The memory type
   // parameter specifies either system memory, or short term block pool,
   // or long term block pool. It is analogous to new.

   static LabelledTreeNode* create ();
   static LabelledTreeNode* create (int aMemoryType);
   static LabelledTreeNode* create (int aMemoryType,int aIdentifier,char* aLabel);
   static LabelledTreeNode* create (int aIdentifier,char* aLabel);

   // This method calls the class destructor and then deallocates the object
   // from system memory or from block universe short term or long term
   // memory block pools. It is analogous to delete.

   virtual void destroy();

   // This member variable specifes the memory type for an instance of the
   // class that has been created: system, short term block pool, or long term
   // block pool. It is set by the create method when it is allocated it is
   // used by the destroy method to determine how to deallocate the block.

   int mMemoryType;

   // This static member specifies the default memory type. If a create is
   // called without a memory type parameter then this variable is used.
   // This is a static member variable that is hard coded in the class 
   // cpp file.
   static int mDefaultMemoryType;

   // Constructor, it is called by create after allocation of a new block.
   LabelledTreeNode();
   LabelledTreeNode(int aIdentifier,char* aLabel);

   // Destructor, it is called by destroy before deallocation of a block.
  ~LabelledTreeNode();

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Class members

   // Label
   enum { MaxLabelSize = 20 };
   char mLabel[MaxLabelSize];

   // Full path
   enum { MaxFullPathSize = 200 };
   char mFullPath[MaxFullPathSize];

   // This is called on a subject node after it is attached to an object node
   virtual void onAttached();
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif