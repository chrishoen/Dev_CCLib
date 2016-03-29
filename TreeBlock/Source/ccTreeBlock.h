#ifndef _CCTREEBLOCK_H_
#define _CCTREEBLOCK_H_

#include <new>
#include <stdio.h>
#include "ccTreeBlockPool.h"

namespace CC
{

//****************************************************************************
//****************************************************************************
//****************************************************************************
// This is a base class for tree nodes.
//   
// It supports recursive data structures that are based on tree nodes and 
// collections of tree nodes. Nodes are attached to other nodes to form 
// collections that have the structure of trees.
//
// Nodes are elements of node collections, node collections contain nodes.
//   
// Nodes maintain pointers to neighboring nodes, similar to linked lists.
// There are methods provided that can be used to attach nodes to other
// nodes.
// 
// Node collections are ordered in two ways. First, any given node can
// havea node before it or a node after it. Second, any node can have a
// parent node that it belongs to above it, or it can have some number of
// child nodes that belong to it below it.
//   
//******************************************************************************
//******************************************************************************
//******************************************************************************

template <class BlockClass>
class TreeBlock
{
public:

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Block Pool Block Members

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Static member which provides a global variable for the memory block 
   // pool.

   static CC::TreeBlockPool<TreeBlock<BlockClass>> mBlockPool;

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // This member variable specifes the memory type for an instance of this
   // class that has been created: system, short term block pool, or long term
   // block pool. It is set by the create method when it is allocated it is
   // used by the destroy method to determine how to deallocate the block.

   int mMemoryType;

   int mBlockIndex;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Block Pool Block Methods

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // This initializes the memory block pool to be short term lifetime,
   // non persistent, circular buffer based. It is passed the number of
   // blocks to allocate from system heap memory.

   static void initializeShortTermBlockPool(int aAllocate)
   {
      mBlockPool.initializeShortTerm(aAllocate, sizeof(BlockClass));
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // This initializes the memory block pool to be long term lifetime,
   // persistent, stack based. It is passed the number of blocks to
   // allocate from system heap memory.

   static void initializeLongTermBlockPool(int aAllocate)
   {
      mBlockPool.initializeLongTerm(aAllocate, sizeof(BlockClass));
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // This allocates a block from the block pool and uses placement new
   // to call the class constructor. It is analogous to new.

   static BlockClass* allocate()
   {
      // Block pointer.
      BlockClass* tPointer = 0;

      // Allocate a block from the block pool.
      tPointer = (BlockClass*)mBlockPool.get();

      // Call the constructor on the allocated block using placement new.
      new(tPointer)BlockClass();

      // Return the pointer to the allocated block.
      return tPointer;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // This deallocates the object back to the block pool. It does not call
   // a destructor for the object.

   void deallocate()
   {
      // Deallocate the block back to the block pool
      mBlockPool.put(this);
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // This method deallocates the object from the block pool.

   void destroy()
   {
      printf("TreeBlock::destroy %d\n",mIdentifier);
      deallocate();
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Tree Node Members

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Node pointers, they point to other neighboring nodes to which a node is
   // attached, If a pointer is null then there is no associated neighbor. The
   // child nodes of a node are managed via a linked list that starts at the 
   // first child node and ends at the last child node. The linked list can be
   // traversed via the before and after pointers of the child nodes.

   // The parent node of this node
   TreeBlock* mParentNode;

   // The node before this node
   TreeBlock* mBeforeNode;

   // The node after this node
   TreeBlock* mAfterNode;

   // The first child node of this node
   TreeBlock* mFirstChildNode;

   // The last child node of this node
   TreeBlock* mLastChildNode;

   // Node identifier
   int mIdentifier;
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Tree Node Methods

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Constructors

   TreeBlock()
   {
      // All pointers to zero
      mParentNode = 0;
      mBeforeNode = 0;
      mAfterNode = 0;
      mFirstChildNode = 0;
      mLastChildNode = 0;

      // Empty state
      mIdentifier=0;
      mMemoryType = 0;
      mAncestorWithAfter = 0;
   }

   TreeBlock(int aIdentifier)
   {
      // All pointers to zero
      mParentNode = 0;
      mBeforeNode = 0;
      mAfterNode = 0;
      mFirstChildNode = 0;
      mLastChildNode = 0;

      // Set state
      mIdentifier = aIdentifier;
      mMemoryType = 0;
      mAncestorWithAfter = 0;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Attach an object node to the first child of this subject node, before it.
   // The object node becomes this subject node's first child.

   void attachBeforeFirstChild (TreeBlock* aObjectNode)
   {
      // If this node doesn't have any children
      // Attach the object node as the only child of this node
      if (this->mFirstChildNode == 0)
      {
         // Set object node's parent as this node
         // Set object node's before as null
         // Set object node's after  as null
         aObjectNode->mParentNode  = this;
         aObjectNode->mBeforeNode  = 0;
         aObjectNode->mAfterNode   = 0;

         // Set the object node as the first and last child of this node
         this->mFirstChildNode     = aObjectNode;
         this->mLastChildNode      = aObjectNode;
      }
      // Else this node does have children
      // Attach the object node after the last child of this node
      else
      {
         // Set object node's parent as this node
         // Set object node's before as null
         // Set object node's after  as the current first child
         aObjectNode->mParentNode  = this;
         aObjectNode->mBeforeNode  = 0;
         aObjectNode->mAfterNode   = this->mFirstChildNode;

         // Set the object node as this node's new first child
         this->mFirstChildNode->mBeforeNode = aObjectNode;
         this->mFirstChildNode              = aObjectNode;
      }
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Attach an object node to the last child of this subject node, after it.
   // The object node becomes this subject node's last child.

   void attachAfterLastChild (TreeBlock* aObjectNode)
   {
      // If this node doesn't have any children
      // Attach the object node as the only child of this node
      if (this->mFirstChildNode == 0)
      {
         // Set object node's parent as this node
         // Set object node's before as null
         // Set object node's after  as null
         aObjectNode->mParentNode  = this;
         aObjectNode->mBeforeNode  = 0;
         aObjectNode->mAfterNode   = 0;

         // Set the object node as the first and last child of this node
         this->mFirstChildNode     = aObjectNode;
         this->mLastChildNode      = aObjectNode;
      }
      // Else this node does have children
      // Attach the object node after the last child of this node
      else
      {
         // Set object node's parent as this node
         // Set object node's before as the current last child
         // Set object node's after  as null
         aObjectNode->mParentNode  = this;
         aObjectNode->mBeforeNode  = this->mLastChildNode;
         aObjectNode->mAfterNode   = 0;

         // Set the object node as this node's new last child
         this->mLastChildNode->mAfterNode = aObjectNode;
         this->mLastChildNode             = aObjectNode;
      }
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Detach the first child node of this parent subject node. Return a
   // pointer to the detached child node.

   TreeBlock* detachFirstChild ()
   {
      // Pointer to the first child node of this subject parent node, this is
      // the node that is to be be detached.
      TreeBlock* tNodeToDetach = this->mFirstChildNode;

      // If there is a node to be detached
      if (tNodeToDetach != 0)
      {
         // If the node to be detached has a node after it
         if (tNodeToDetach->mAfterNode != 0)
         {
            // Because this node is the first child of its parent and therefore has
            // no node before it then set the node after it to also have no node
            // before it.
            tNodeToDetach->mAfterNode->mBeforeNode = 0;

            // Set the new first child node of this subject parent node to be the
            // node after the node that is to be detached.
            this->mFirstChildNode = tNodeToDetach->mAfterNode;
         }
         // If the node to be detached does not have a node after it,
         // then it is the only child node of its parent.
         else
         {
            // Set the subect parent node to have no first child node.
            this->mFirstChildNode = 0;
            // Also, set the subect parent node to have no last child node.
            this->mLastChildNode = 0;
         }

         // Set the detached node to have no node after it. Because it is the 
         // first child node then it already has no node before it.
         tNodeToDetach->mAfterNode = 0;

         // Set the detached node to have no node parent node above it.
         tNodeToDetach->mParentNode = 0;
      }
      // Return the pointer to the detached node.
      return tNodeToDetach;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Detach the last child node of this parent subject node. Return a
   // pointer to the detached child node.

   TreeBlock* detachLastChild ()
   {
      // Pointer to the last child node of this subject parent node, this is
      // the node that is to be be detached.
      TreeBlock* tNodeToDetach = this->mLastChildNode;

      // If there is a node to be detached
      if (tNodeToDetach != 0)
      {
         // If the node to be detached has a node before it
         if (tNodeToDetach->mBeforeNode != 0)
         {
            // Because this node is the last child of its parent and therefore has
            // no node after it then set the node before it to also have no node
            // after it.
            tNodeToDetach->mBeforeNode->mAfterNode = 0;

            // Set the new last child node of this subject parent node to be the
            // node before the node that is to be detached.
            this->mLastChildNode = tNodeToDetach->mBeforeNode;
         }
         // If the node to be detached does not have a node before it,
         // then it is the only child node of its parent.
         else
         {
            // Set the subect parent node to have no last child node.
            this->mLastChildNode = 0;
            // Also, set the subect parent node to have no first child node.
            this->mFirstChildNode = 0;
         }

         // Set the detached node to have no node before it. Because it is the 
         // last child node then it already has no node after it.
         tNodeToDetach->mBeforeNode = 0;

         // Set the detached node to have no node parent node above it.
         tNodeToDetach->mParentNode = 0;
      }
      // Return the pointer to the detached node.
      return tNodeToDetach;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Attach an object node to this subject node, before it

   void attachBefore (TreeBlock* aObjectNode)
   {
      // If this node does not have a node before it
      if (this->mBeforeNode == 0)
      {
         // This node is its root node's first child
         if (this->mParentNode != 0)
         {
            // Set the object node as this node's parent's new last child
            this->mParentNode->mFirstChildNode = aObjectNode;
         }
         // Attach the object node before this node
         aObjectNode->mBeforeNode      = 0;
         aObjectNode->mAfterNode       = this;
         this->mBeforeNode       = aObjectNode;
      }
      // If this node does have a node before it
      else
      {
         // Insert the object node between this node and the node before it
         aObjectNode->mBeforeNode      = this->mBeforeNode;
         aObjectNode->mAfterNode       = this;
         this->mBeforeNode->mAfterNode = aObjectNode;
         this->mBeforeNode             = aObjectNode;
      }
      // The object node inherits this nodes's parent node
      aObjectNode->mParentNode = this->mParentNode;
   }

   // Attach an object node to this subject node, after it
   void attachAfter (TreeBlock* aObjectNode)
   {
      // If this node does not have a node after it
      if (this->mAfterNode == 0)
      {
         // This node is its root node's last child
         if (this->mParentNode != 0)
         {
            // Set the object node as this node's parent's new last child
            this->mParentNode->mLastChildNode = aObjectNode;
         }
         // Attach the object node after this node
         aObjectNode->mBeforeNode      = this;
         aObjectNode->mAfterNode       = 0;
         this->mAfterNode        = aObjectNode;
      }
      // Else this node does have a node after it
      else
      {
         // Insert the object node between this node and the node after it
         aObjectNode->mBeforeNode      = this;
         aObjectNode->mAfterNode       = this->mAfterNode;
         this->mAfterNode->mBeforeNode = aObjectNode;
         this->mAfterNode              = aObjectNode;
      }
      // The object node inherits this node's parent node
      aObjectNode->mParentNode = this->mParentNode;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // Detach this subject node from all of the nodes to which it is attached.
   // This is used when a node is destroyed.

   void detachFromAll()
   {
      // If this subject node does not have a node before it
      if (this->mBeforeNode == 0)
      {
         // If this node has a parent then it's its root node's first child
         if (this->mParentNode != 0)
         {
            // Set the node after this node as the root node's first child
            this->mParentNode->mFirstChildNode = this->mAfterNode;
         }
      }
      // Else this node has a node before it
      else
      {
         // Set the node before it to point to the node after it
         this->mBeforeNode->mAfterNode = this->mAfterNode;
      }

      // If this node does not have a node after it
      if (this->mAfterNode == 0)
      {
         // If this node has a parent then it's its root node's last child
         if (this->mParentNode != 0)
         {
            // Set the node before this node as the root node's last child
            this->mParentNode->mLastChildNode = this->mBeforeNode;
         }
      }
      // Else this node has a node after it
      else
      {
         // Set the node after it to point to the node before it
         this->mAfterNode->mBeforeNode = this->mBeforeNode;
      }

      // This node no longer has a parent or nodes before and after it
      this->mParentNode = 0;
      this->mBeforeNode = 0;
      this->mAfterNode = 0;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   // This is a pointer to the closest ancestor of this node that has a node
   // after it. It is used by transmit and receive queues to deconstruct and
   // reconstruct tree node structures that are transmitted over a 
   // communications channel.
   //
   // This variable should be considered as a sort of temporary variable.
   // It is changed by various actions done by node queues. It should not
   // be used as a node level and it is not set by the attachment methods.
   // It is set by a transmit queue prior to transmission and is used
   // by a receive queue to reconstruct node structures.
   //
   // Use of this variable is mainly via the getNextNode visitor call,
   // which assumes a tree node structure traversal in construction order.

   TreeBlock* mAncestorWithAfter;
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Node pointers
/*

                                   +-----------+
         +------------------------>| parent    |<------------------------+
         |                         +-----------+                         |
         |                               ^                               |
         |                               |                               |
         |                               |                               |
   +-----------+                   +-----------+                   +-----------+
   | before    |<----------------->| subject   |<----------------->| after     |
   +-----------+                   +-----------+                   +-----------+
   before->mParentNode = parent    subject->mParentNode = parent   after->mParentNode = parent
   before->mAfterNode  = subject   subject->mBeforeNode = before   after->mBeforeNode = subject       
                                   subject->mAfterNode  = after

                                   parent->mFirstChildNode = first
                                   parent->mLastChildNode  = last
                                   +-----------+
         +-------------------------| parent    |-------------------------+
         |                         +-----------+                         |
         |                                                               |
         |                                                               |
         v                                                               v
   +-----------+                   +-----------+                   +-----------+
   | first     |<------...-------->| nodes     |<-------...------->| last      |
   +-----------+                   +-----------+                   +-----------+
   first->mParentNode = parent     node->mParentNode = parent      last->mParentNode = parent
*/

/*
TreeBlock is a class that supports recursive data structures.

TreeBlock is the basis for data structures that are based on trees of nodes.
It is similar to linked lists.

The tree data structures are collections of tree node elements. These data
structures are entirely analogous to two constructs: sets and file system
directory structures. 

The TreeBlock class provides pointers to other nodes and it provides
methods that allow attaching other nodes to a given node.

Sets contain elements. The elements can be other sets or they can be what 
are known as ur-elements, elements that are not sets.

File directories contain other file directories or they contain files,
which are not directories.

Here are some rules which apply to sets and file directories:

Sets cannot contain themselves as elements, recursively or otherwise.

File directories cannot contain themselves as directories or files, 
recursively or otherwise.

A set cannot contain two elements which are identical.

A file directory cannot contain two files or directories which are identical.

These rules are not enforced by the TreeBlock attach methods.

*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Attach an object node to a subject node, before it

/*
   CASE1 BEFORE, there is no node before the subject node

   parent->mFirstChildNode = subject
   +-----------+
   | parent    |
   +-----------+
      |     ^
      |     |
      v     |
   +-----------+
   | subject   |
   +-----------+
   subject->mParentNode = parent
   subject->mBeforeNode = 0

   CASE1 AFTER, there is no node before the subject node

   parent->mFirstChildNode = subject
   +-----------+
   | parent    |<-----------------------+
   +-----------+                        |
      |    ^                            |
      |    |                            |
      v    |                            |   
   +-----------+                   +-----------+
   | object    |<----------------->| subject   |       
   +-----------+                   +-----------+
   object->mParentNode = parent   subject->mBeforeNode = object
   object->mBeforeNode = 0         
   object->mAfterNode  = subject   

   CASE2 BEFORE, there is a node before the subject node

   +-----------+                   +-----------+
   | before    |<----------------->| subject   |       
   +-----------+                   +-----------+
   before->mAfterNode = subject     subject->mBeforeNode = before       

   CASE2 AFTER, there is a node before the subject node

   +-----------+                   +-----------+                   +-----------+
   | before    |<----------------->| object    |<----------------->| subject   |
   +-----------+                   +-----------+                   +-----------+
   before->mAfterNode = object    object->mBeforeNode = before     subject->mBeforeNode = object
                                  object->mAfterNode  = subject
                                  object->mParentNode = subject->mParentNode
*/        
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Attach an object node to a subject node, after it

/*
   CASE1 BEFORE, there is no node after the subject node

   parent->mLastChildNode = subject
   +-----------+
   | parent    |
   +-----------+
      |     ^
      |     |
      v     |
   +-----------+
   | subject   |
   +-----------+
   subject->mParentNode = parent
   subject->mAfterNode  = 0

   CASE1 AFTER, there is no node after the subject node

   parent->mLastChildNode = object
   +-----------+
   | parent    |<-----------------------+
   +-----------+                        |
      |    ^                            |
      |    |                            |
      v    |                            |   
   +-----------+                   +-----------+
   | subject   |<----------------->| object    |
   +-----------+                   +-----------+
   subject->mAfterNode = object    object->mBeforeNode = subject 
                                   object->mAfterNode  = 0
                                   object->mParentNode = parent

   CASE2 BEFORE, there is a node after the subject node

   +-----------+                   +-----------+
   | subject   |<----------------->| after     |       
   +-----------+                   +-----------+
   subject->mAfterNode = after      after->mBeforeNode = subject   

   CASE2 AFTER, there is a node after the subject node

   +-----------+                   +-----------+                   +-----------+
   | subject   |<----------------->| object    |<----------------->| after     |
   +-----------+                   +-----------+                   +-----------+
   subject->mAfterNode = object    object->mBeforeNode = subject   after->mBeforeNode = object       
                                   object->mAfterNode  = after
                                   object->mParentNode = subject->mParentNode
*/
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Detach this object node from its parent and before and after nodes

/*
   CASE1 BEFORE, there is no node before the object node

   parent->mFirstChildNode = object
   +-----------+
   | parent    |<-----------------------+
   +-----------+                        |
      |    ^                            |
      |    |                            |
      v    |                            |   
   +-----------+                   +-----------+
   | object    |<----------------->| after     |       
   +-----------+                   +-----------+
   object->mBeforeNode = 0         after->mBeforeNode = object
   object->mAfterNode  = after   

   CASE1 AFTER, there is no node before the object node

   parent->mFirstChildNode = after
   +-----------+
   | parent    |
   +-----------+
      |     ^
      |     |
      v     |
   +-----------+
   | after     |
   +-----------+
   after->mBeforeNode = 0

   CASE2 BEFORE, there is a node before the object node

   +-----------+                   +-----------+                   +-----------+
   | before    |<----------------->| object    |<----------------->| after     |
   +-----------+                   +-----------+                   +-----------+
   before->mAfterNode = object     object->mBeforeNode = before    after->mBeforeNode = object       
                                   object->mAfterNode  = after

   CASE2 AFTER, there is a node before the object node

   +-----------+                   +-----------+
   | before    |<----------------->| after     |       
   +-----------+                   +-----------+
   subject->mAfterNode = after      after->mBeforeNode = before

   CASE3 BEFORE, there is no node after the object node

   parent->mLastChildNode = object
   +-----------+
   | parent    |<-----------------------+
   +-----------+                        |
      |    ^                            |
      |    |                            |
      v    |                            |   
   +-----------+                   +-----------+
   | before    |<----------------->| object    |       
   +-----------+                   +-----------+
   before->mAfterNode = object    object->mBeforeNode = before        
                                   object->mAfterNode  = 0   

   CASE3 AFTER, there is no node after the object node

   parent->mLastChildNode = before
   +-----------+
   | parent    |
   +-----------+
      |     ^
      |     |
      v     |
   +-----------+
   | before    |
   +-----------+
   after->mAfterNode = 0

   CASE4 BEFORE, there is a node after the object node

   +-----------+                   +-----------+                   +-----------+
   | before    |<----------------->| object    |<----------------->| after     |
   +-----------+                   +-----------+                   +-----------+
   before->mAfterNode = object    object->mBeforeNode = before    after->mBeforeNode = object       
                                   object->mAfterNode  = after

   CASE4 AFTER, there is a node before the object node

   +-----------+                   +-----------+
   | before    |<----------------->| after     |       
   +-----------+                   +-----------+
   before->mAfterNode = after      after->mBeforeNode = before       

*/        
#endif