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
// Node collections are ordered in two ways. First, any given node can
// havea node before it or a node after it. Second, any node can have a
// parent node that it belongs to above it, or it can have some number of
// child nodes that belong to it below it.
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
   
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Node flags, these encode relationship's that this node has with other 
   // nodes, within its tree structure. These flags all default to false.

   typedef union TreeNodeFlags
   {
      // Flags
      struct
      {
         // This is true if the node is a root, that it has no parent node.
         bool mIsRoot        : 1;
         // This is true if the node is a parent node of some child nodes.
         bool mIsParent      : 1;
         // This is true if the node is the first child of its parent node.
         bool mIsFirstChild  : 1;
         // This is true if the node is the last child of its parent node.
         bool mIsLastChild   : 1;
      };
      // Binary value
      unsigned char mValue;
   } TreeNodeFlags;

   TreeNodeFlags mTreeNodeFlags;

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // These attach this subject node to an object node.

   // Attach an object node to this subject node, before it
   void attachBefore (TreeNode* aObjectNode);

   // Attach an object node to this subject node, after it
   void attachAfter (TreeNode* aObjectNode);

   // Attach an object node to the first child of this subject node, before it.
   // The object node becomes this subject node's first child.
   void attachBeforeFirstChild (TreeNode* aObjectNode);

   // Attach an object node to the last child of this subject node, after it.
   // The object node becomes this subject node's last child.
   void attachAfterLastChild (TreeNode* aObjectNode);

   // Detach this subject node from all of the nodes to which it is attached
   void detachFromAll();

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // These detach attached object nodes from this parent subject node.

   // Detach the first child node of this parent subject node. Return a
   // pointer to the detached child node.
   TreeNode* detachFirstChild ();

   // Detach the last child node of this parent subject node. Return a
   // pointer to the detached child node.
   TreeNode* detachLastChild ();

   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   //--------------------------------------------------------------------------
   // Methods provided by inheritors

   // This is called on this subject node after it is attached to an object
   // node
   virtual void onAttached() {}

   // This method calls the class destructor and then deallocates the object
   // from system memory or from block universe short term or long term
   // memory block pools. It is analogous to delete. It is overloaded by
   // inheriting classes.

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
// Attach a subject node to an object node, before it

/*
   CASE1 BEFORE, there is no node before the object node

   parent->mFirstChildNode = object
   +-----------+
   | parent    |
   +-----------+
      |     ^
      |     |
      v     |
   +-----------+
   | object    |
   +-----------+
   object->mParentNode = parent
   object->mBeforeNode = 0

   CASE1 AFTER, there is no node before the object node

   parent->mFirstChildNode = object
   +-----------+
   | parent    |<-----------------------+
   +-----------+                        |
      |    ^                            |
      |    |                            |
      v    |                            |   
   +-----------+                   +-----------+
   | subject   |<----------------->| object    |       
   +-----------+                   +-----------+
   subject->mParentNode = parent   object->mBeforeNode = subject
   subject->mBeforeNode = 0         
   subject->mAfterNode  = object   

   CASE2 BEFORE, there is a node before the object node

   +-----------+                   +-----------+
   | before    |<----------------->| object    |       
   +-----------+                   +-----------+
   before->mAfterNode = object     object->mBeforeNode = before       

   CASE2 AFTER, there is a node before the object node

   +-----------+                   +-----------+                   +-----------+
   | before    |<----------------->| subject   |<----------------->| object    |
   +-----------+                   +-----------+                   +-----------+
   before->mAfterNode = subject    subject->mBeforeNode = before   object->mBeforeNode = subject       
                                   subject->mAfterNode  = object
                                   subject->mParentNode = object->mParentNode
*/        
//****************************************************************************
//****************************************************************************
//****************************************************************************
// Attach a subject node to an object node, after it

/*
   CASE1 BEFORE, there is no node after the object node

   parent->mLastChildNode = object
   +-----------+
   | parent    |
   +-----------+
      |     ^
      |     |
      v     |
   +-----------+
   | object    |
   +-----------+
   object->mParentNode = parent
   object->mAfterNode  = 0

   CASE1 AFTER, there is no node after the object node

   parent->mLastChildNode = subject
   +-----------+
   | parent    |<-----------------------+
   +-----------+                        |
      |    ^                            |
      |    |                            |
      v    |                            |   
   +-----------+                   +-----------+
   | object    |<----------------->| subject   |       
   +-----------+                   +-----------+
   object->mAfterNode = subject    subject->mBeforeNode = object 
                                   subject->mAfterNode  = 0
                                   subject->mParentNode = parent

   CASE2 BEFORE, there is a node after the object node

   +-----------+                   +-----------+
   | object    |<----------------->| after     |       
   +-----------+                   +-----------+
   object->mAfterNode = after      after->mBeforeNode = object   

   CASE2 AFTER, there is a node after the object node

   +-----------+                   +-----------+                   +-----------+
   | object    |<----------------->| subject   |<----------------->| after     |
   +-----------+                   +-----------+                   +-----------+
   object->mAfterNode = subject    subject->mBeforeNode = object   after->mBeforeNode = subject       
                                   subject->mAfterNode  = after
                                   subject->mParentNode = object->mParentNode
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