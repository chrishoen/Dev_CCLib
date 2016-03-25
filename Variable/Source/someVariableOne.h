#ifndef _SOMEVARIABLEONE_H_
#define _SOMEVARIABLEONE_H_

#include "ccTreeNode.h"
#include "ccDefs.h"
#include "ccBlockPoolBlock.h"

namespace Some
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// First order variable

class VariableOne : public CC::TreeNode, public CC::BlockPoolBlock<VariableOne>
{
public:

   //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   // Class members

   int mValue;

   // Class members
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Memory management, constructors and destructors

   // Create with default memory type and specified member variables
   static VariableOne* create (int aIdentifier);

   // This method calls the class destructor and then deallocates the object
   // from system memory or from block universe short term or long term
   // memory block pools. It is analogous to delete.

   virtual void destroy();

   // Constructor, it is called by create after allocation of a new block.
   VariableOne();
   VariableOne(int aIdentifier);
};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace
#endif