/*==============================================================================
Description:

I'm naming this file as dangerous so that you will be aware of the dangers
of including it in a build. 

It globally replaces the delete operator.

The replacement delete operator looks at a given pointer. If it points to an 
object that was not allocated from the short term memory heap then it points
to an object that was allocated from the syetem heap. In this case its memory
is freed as normal. If it does point to an object that was allocated on the 
short term heap then nothing happens, because the short term memory heap
doesn't do deletions.

This is provided as as a safety measure against legacy code that might call
delete on objects that, instead of being created with new, were allocated from
the short term memory heap. These objects don't live on the system heap and 
cannot be deleted from it.

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

If you include this .cpp file in your build then the following delete operator
will replace the default delete operator. It will be called by any calls to 
delete anywhere in your program.

Including this .cpp file in a build is quite frightening.

Here's where I found out about it:

http://en.cppreference.com/w/cpp/memory/new/operator_delete

And this is what it says:

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
//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <cstdio>
#include <cstdlib>

#include "ccShortTermMemory.h"

//******************************************************************************
// This is a replacement for the delete operator. It is global in scope.
//
// If the given pointer is within the bounds of the short term memory heap then
// the object pointed to was allocated from the short term memory heap. 
//
// If this is not the case, which is normal, then the object pointed to was
// allocated from the system heap. Therefore the standard memory free is
// called, which is exactly what would have happened if this file had not 
// overridden the delete operator.
//
// If it is the case, then the pointer points to an object that was allocated
// from the short term memory heap. If so, nothing is done, because the short 
// term memory heap does not do deletions.

void operator delete(void* ptr)
{
   // If the pointer does not point to an object that was allocated from the
   // short term memory heap, which would be the normal case.
   if (!CC::isInShortTermMemory(ptr))
   {
      // Do the default memory free. This is exactly what would have happened
      // if this file had not overridden the delete operator.
      std::free(ptr);
   }
   // Else the pointer does point to an object that was allocated from the
   // short term memory heap.
   else
   {
      // Do nothing, short term memory doesn't do deletes.
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

   
