# Dev_CCLib
### concurrent container classes, vstudio, cmake windows and linux

This is a library of C++ classes that provides some concurrent containers. Features include:
   1. Block pool classes
   2. Tree node classes
   3. Queues, stacks, and free lists that are based on lock free atomic instuctions
   4. Queues, stacks, and free lists that are based on mutexes 
   5. Related utilities for memory pointer and index arithmetic

This library is written for Windows and Linux in Visual Studio, using the cmake paradigm. The classes are based on Win32 or pthread realtime functions for threads and sockets and such. The library is portable. The details of the provided functionality that are specific to Win32 are contained in a small set of `*_win.cpp` or `*_linux.cpp`files. It is the intention of the library that programs built under Windows can be rebuilt seamlessly under Linux. CMake is used to implement the cross platform functionality.

The solution contains the library project and a set of associated unit test projects.

The current linux version builds on an ASUS TinkerBoard running debian stretch. The only build prerequisite is the gcc build-essentials.
This library depends on RisLib.

## Classes
``` markdown

ccBlockBoxArray.h             -- block pool block box array, a block box contains a block and a header
ccBlockHeader.h               -- block pool block header
ccBlockPool.h                 -- block pool main interface
ccBlockPoolBase.h             -- block pool base class
ccBlockPoolBaseIndexStack.h   -- block pool index stack base class
ccBlockPoolBlock.h            -- block pool memory block
ccBlockPoolCentral.h          -- block pool main class
ccBlockPoolIndex.h            -- block pool index definitions for this library, for tree nodes
ccBlockPoolLFFreeList.h       -- block pool imlementation with a free list that is lock free
ccBlockPoolLMFreeList.h       -- block pool imlementation with a free list that is based on mutexes
ccBlockPoolLMIndexStack.h     -- block pool imlementation of an index stack that is based on mutexes
ccBlockPoolParms.h            -- block pool parameters
ccCallPointer.h               -- class templates that manage function pointers for c++ classes
ccContainers.h                -- some legacy container class templates, queues, stacks ...
ccContainers2.h               -- more of the same
ccDefs.h                      -- some #defines
ccDiagrams.h                  -- some documentation
ccLFIndex.h                   -- lock free index struct used for CAS atomic instructions
ccLFObjectQueue.h             -- single reader multiple writer lock free object queue
ccLFPointerQueue.h            -- single reader multiple writer lock free pointer queue 
ccLFValueQueue.h              -- single reader multiple writer lock free value queue 
ccLMObjectQueue.h             -- single reader multiple writer lock with mutex object queue
ccLMValueQueue.h              -- single reader multiple writer lock with mutex pointer queue
ccMemoryPtr.h                 -- single reader multiple writer lock with mutex value queue
ccRecursiveAnchor.h           -- recursive anchor used by tree node visitors
ccSRSWValueQueue.h            -- single reader single writer thread safe value queue, no mutex, no atomics
ccSynchLock.h                 -- synchronization lock for critical sections
ccTreeNode.h                  -- tree node class
ccTreeNodeDestroyer.h         -- tree node destroyer, recursively destoys a tree
ccTreeNodeVisitor.h           -- tree node visitor, recursively visits a tree, applies a function to tree nodes
ccValueHistory.h              -- circular buffer shift register of value,time pairs
ccValueQueue.h                -- legacy value queue
cc_functions.h                -- some pointer and index management functions
cc_throw.h                    -- wrapper for c++ throw exception
stdafx.h                      -- used for precompiled header files
```

## Solution Projects
``` markdown
CCLib               -- concurrent container library -- this is the library
Classes             -- experiments with classes, new, delete
Concurrent          -- container and block pool timing and concurreny test program
Containers          -- unit test for some containers
Counter             -- experiments with modulo counter classes
Delete              -- experiments with delete operator overloads
Documents           -- some documentation
Files               -- parameters files for Concurrent
History             -- unit test for history container
Labelled            -- unit test for labelled tree nodes
LFCCLib             -- lock free version of CCLib
LFConcurrent        -- lock free version of Concurrent
LLogic              -- experiments with lukasiewicz fuzzy logic variables
LockFree            -- unit test for integer lock free queue and free list
Memory              -- unit test for memory pointer utilites
MyBlock             -- example block pool for classes
MyTreeBlock         -- example block pool for tree nodes
NodeChannel         -- send tree nodes via a communications channel
ProtoBlock          -- prototype for block pools
QueueTest           -- unit test for some queues
SharedMemory        -- unit test for block pools over shared memory
StackTest           -- unit test for stacks
Stash               -- old code
Test                -- scratch test program
```
