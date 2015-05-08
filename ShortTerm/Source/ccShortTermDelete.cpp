/*==============================================================================
Description:
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

/*
This a global replacement for the delete operator. If this .cpp file is 
included in a build then the following delete operator overrides all deletes
for the entire program. The following delete operation actually replaces all
delete calls made anywhere in the program. This is in accordance with the cpp
language definition. This replacement is implemented at link time.

I want to repeat: If you include this .cpp file in your build then the
following delete operator will replace the default delete operator. It 
will be called by any calls to delete anywhere in your program.

Including this .cpp file in a build is quite frightening.

Here's where I found out about it:

http://en.cppreference.com/w/cpp/memory/new/operator_delete

The versions (1-8) are implicitly declared in each translation unit even if the
<new> header is not included. These functions are replaceable: a user-provided
non-member function with the same signature defined anywhere in the program, 
in any source file, replaces the corresponding implicit version for the entire 
program. Its declaration does not need to be visible. 

The behavior is undefined if more than one replacement is provided in the
program or if a replacement is defined with the inline specifier, the program 
is ill-formed if a replacement is defined in namespace other than global 
namespace, or if it is defined as a static non-member function at global scope

*/
#include <cstdio>
#include <cstdlib>

#include "ccShortTermMemory.h"

//******************************************************************************
// This is a replacement for the delete operator. If the given pointer points
// into the short term memory heap then the object pointed to was allocated
// from the short term memory heap. If this is the case then the delete
// operation does nothing, because there are no deleteions for the short term
// memory heap. If this is not the case then the standard memory free is 
// called. Note that, in either case, the compiler calls the destructor for
// the object pointed to.

void operator delete(void* ptr)
{
   // If the pointer points to an object that was allocated from the
   // short term memory heap.
   if (CC::isInShortTermMemory(ptr))
   {
      // Do nothing, short term memory doesn't do deletes.
   }
   // If the pointer does not point to an object that was allocated from the
   // short term memory heap, which is the normal case.
   else
   {
      // Do the default memory free. This is exactly what would have happened
      // if this file had not overridden the delete operator.
      std::free(ptr);
   }

}

//******************************************************************************
//******************************************************************************
//******************************************************************************

   
