#ifndef _CCTREENODEATTACH_H_
#define _CCTREENODEATTACH_H_

#include "ccTreeNode.h"

namespace CC
{

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// These attach a subject node to an object node.

// Attach a subject node to an object node, before it
void attachBefore (TreeNode* aSubjectNode,TreeNode* aObjectNode);

// Attach a subject node to an object node, after it
void attachAfter (TreeNode* aSubjectNode,TreeNode* aObjectNode);

// Attach a subject node to the first child of an object node, before it
// The subject node becomes the object node's first child.
void attachBeforeFirstChild (TreeNode* aSubjectNode,TreeNode* aObjectNode);

// Attach a subject node to the last child of an object node, after it
// The subject node becomes the object node's last child.
void attachAfterLastChild (TreeNode* aSubjectNode,TreeNode* aObjectNode);

// Detach a subject node from all of the nodes to which it is attached
void detach(TreeNode* aSubjectNode);


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