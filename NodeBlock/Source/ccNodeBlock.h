#ifndef _CCNODEBLOCK_H_
#define _CCNODEBLOCK_H_

#include "ccTreeNode.h"
#include "ccDefs.h"
#include "ccBlockPoolBlock.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

class NodeBlock : public TreeNode, public CC::BlockPoolBlock<NodeBlock>
{
public:

   //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   // Class members

   typedef union BlockData
   {
      // Flags
      struct
      {
         unsigned short mBlockType;
         unsigned short mBlockSubType;
         unsigned short mDataSize;
         unsigned short mTreeNodeTxFlags;
         unsigned short mTreeNodeTxAttachLevel;
      };
      // Binary value
      enum {MaxDataSize=200};
      unsigned short mData[MaxDataSize/2];
   } BlockData;

   BlockData mBlockData;


   // Label
   int mData;

   // Class members
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Memory management, constructors and destructors

   // Create with default memory type and specified member variables
   static NodeBlock* create (int aIdentifier);

   // This method calls the class destructor and then deallocates the object
   // from system memory or from block universe short term or long term
   // memory block pools. It is analogous to delete.

   virtual void destroy();

   // Constructor, it is called by create after allocation of a new block.
   NodeBlock();
   NodeBlock(int aIdentifier);
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif