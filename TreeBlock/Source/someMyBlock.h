#ifndef _SOMEMYBLOCK_H_
#define _SOMEMYLOCK_H_

#include "ccTreeNode.h"
#include "ccDefs.h"
#include "ccBlockPoolBlock.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************

class MyBlock : public CC::TreeNode, public CC::BlockPoolBlock<MyBlock>
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
   static MyBlock* create (int aIdentifier);

   // This method calls the class destructor and then deallocates the object
   // from system memory or from block universe short term or long term
   // memory block pools. It is analogous to delete.

   virtual void destroy();

   // Constructor, it is called by create after allocation of a new block.
   MyBlock();
   MyBlock(int aIdentifier);
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif