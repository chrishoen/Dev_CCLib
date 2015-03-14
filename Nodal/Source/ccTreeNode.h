#ifndef _CCTREENODE_H_
#define _CCTREENODE_H_

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
// Node colletions are ordered in two ways. First, any given node can have
// a node before it or a node after it. Second, any node can have a parent
// node that it belongs to above it, or it can have some number of child
// nodes that belong to it below it.

// Here is the class definition, there is more documentation after it.
//   
//****************************************************************************
//****************************************************************************
//****************************************************************************

class TreeNode
{
public:
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Constructors

   TreeNode();
   TreeNode(int aIdentifier);

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Node pointers, they point to other neighboring nodes to which a node is
   // attached, If a pointer is null then there is no associated neighbor. The
   // child nodes of a node are managed via a linked list that starts at the 
   // first child node and ends at the last child node. The linked list can be
   // traversed via the before and after pointers of the child nodes.

   // The parent node of this node
   TreeNode* mParentNode;

   // The node before this node
   TreeNode* mBeforeNode;

   // The node after this node
   TreeNode* mAfterNode;

   // The first child node of this node
   TreeNode* mFirstChildNode;

   // The last child node of this node
   TreeNode* mLastChildNode;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Node state

   int mIdentifier;
   int mOrder;

   // This is called on a subject node after it is attached to an object node
   virtual void onAttached() {}

   // This method calls the class destructor and then deallocates the object
   // from system memory or from block universe short term or long term
   // memory block pools. It is analogous to delete.

   virtual void destroy(){}

   // This member variable specifes the memory type for an instance of the
   // class that has been created: system, short term block pool, or long term
   // block pool. It is set by the create method when it is allocated it is
   // used by the destroy method to determine how to deallocate the block.

   int mMemoryType;

};

//****************************************************************************
//****************************************************************************
//****************************************************************************
}//namespace


/*
TreeNode is a class that supports recursive data structures.

TreeNode is the basis for data structures that are based on trees of nodes.
It is similar to linked lists.

The tree data structures are collections of tree node elements. These data
structures are entirely analogous to two constructs: sets and file system
directory structures. 

The TreeNode class provides pointers to other nodes and it provides
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

These rules are not enforced by the TreeNode attach methods.

*/
//****************************************************************************
//****************************************************************************
//****************************************************************************
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

//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach an object node to this subject node, before it

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

   parent->mFirstChildNode = object
   +-----------+
   | parent    |<-----------------------+
   +-----------+                        |
      |    ^                            |
      |    |                            |
      v    |                            |   
   +-----------+                   +-----------+
   | object    |<----------------->| subject   |       
   +-----------+                   +-----------+
   object->mParentNode = parent    subject->mBeforeNode = object
   object->mBeforeNode = 0         
   object->mAfterNode  = subject   

   CASE2 BEFORE, there is a node before the subject node

   +-----------+                   +-----------+
   | before    |<----------------->| subject   |       
   +-----------+                   +-----------+
   object->mAfterNode = subject    subject->mBeforeNode = before       

   CASE2 AFTER, there is a node before the subject node

   +-----------+                   +-----------+                   +-----------+
   | before    |<----------------->| object    |<----------------->| subject   |
   +-----------+                   +-----------+                   +-----------+
   before->mAfterNode = object     object->mBeforeNode = before    subject->mBeforeNode = object       
                                   object->mAfterNode  = subject
                                   object->mParentNode = subject->mParentNode
*/        
//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach an object node to this subject node, after it

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

   CASE1 AFTER, there is no node before the subject node

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
   subject->mAfterNode = after     after->mBeforeNode = subject   

   CASE2 AFTER, there is a node after the subject node

   +-----------+                   +-----------+                   +-----------+
   | subject   |<----------------->| object    |<----------------->| after     |
   +-----------+                   +-----------+                   +-----------+
   subject->mAfterNode = object    object->mBeforeNode = subject   after->mBeforeNode = object       
                                   object->mAfterNode  = after
                                   object->mParentNode = subject->mParentNode
*/
//****************************************************************************
//****************************************************************************
//****************************************************************************
// Detach this subject node from its parent and before and after nodes

/*
   CASE1 BEFORE, there is no node before the subject node

   parent->mFirstChildNode = subject
   +-----------+
   | parent    |<-----------------------+
   +-----------+                        |
      |    ^                            |
      |    |                            |
      v    |                            |   
   +-----------+                   +-----------+
   | subject   |<----------------->| after     |       
   +-----------+                   +-----------+
   subject->mBeforeNode = 0        after->mBeforeNode = subject
   subject->mAfterNode  = after   

   CASE1 AFTER, there is no node before the subject node

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

   CASE2 BEFORE, there is a node before the subject node

   +-----------+                   +-----------+                   +-----------+
   | before    |<----------------->| subject   |<----------------->| after     |
   +-----------+                   +-----------+                   +-----------+
   before->mAfterNode = subject    subject->mBeforeNode = before    after->mBeforeNode = subject       
                                   subject->mAfterNode  = after

   CASE2 AFTER, there is a node before the subject node

   +-----------+                   +-----------+
   | before    |<----------------->| after     |       
   +-----------+                   +-----------+
   object->mAfterNode = after      after->mBeforeNode = before

   CASE3 BEFORE, there is no node after the subject node

   parent->mLastChildNode = subject
   +-----------+
   | parent    |<-----------------------+
   +-----------+                        |
      |    ^                            |
      |    |                            |
      v    |                            |   
   +-----------+                   +-----------+
   | before    |<----------------->| subject   |       
   +-----------+                   +-----------+
   before->mAfterNode = subject    subject->mBeforeNode = before        
                                   subject->mAfterNode  = 0   

   CASE3 AFTER, there is no node after the subject node

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

   CASE4 BEFORE, there is a node after the subject node

   +-----------+                   +-----------+                   +-----------+
   | before    |<----------------->| subject   |<----------------->| after     |
   +-----------+                   +-----------+                   +-----------+
   before->mAfterNode = subject    subject->mBeforeNode = before    after->mBeforeNode = subject       
                                   subject->mAfterNode  = after

   CASE4 AFTER, there is a node before the subject node

   +-----------+                   +-----------+
   | before    |<----------------->| after     |       
   +-----------+                   +-----------+
   before->mAfterNode = after      after->mBeforeNode = before       

*/        

#endif