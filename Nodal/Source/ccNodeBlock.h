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

   int mCode1;
   int mCode2;
   int mCode3;
   int mCode4;

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