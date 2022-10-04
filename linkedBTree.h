//Jordan Rood - Binary Tree header file

#ifndef LINKED_BTREE_H
#define LINKED_BTREE_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "linkedBTreeNode.h"
#include "bTreeInterface.h"

using namespace std;

template<class ItemType>
class LinkedBTree : public BinaryTreeInterface<ItemType>{
public:
    LinkedBTreeNode<ItemType>* rootPtr;

    LinkedBTree(); //ctor

    virtual bool isEmpty() const;
    virtual int getHeight() const;
    virtual int getNumberOfNodes() const;
    virtual ItemType getRootData() const;
    bool add(const ItemType& newEntry);
    bool remove(const ItemType& anEntry);
    virtual void clear();
    ItemType getEntry(const ItemType& anEntry) const;
    virtual bool contains(const ItemType& anEntry) const;
    virtual ~LinkedBTree();

    virtual void preorderTraverse(void visit(ItemType&)) const;
    virtual void inorderTraverse(void visit(ItemType&)) const;
    virtual void postorderTraverse(void visit(ItemType&)) const;

protected:
    int getHeightHelper(LinkedBTreeNode<ItemType>* subTreePtr) const;
    int getNumberOfNodesHelper(LinkedBTreeNode<ItemType>* subTreePtr) const;
    LinkedBTreeNode<ItemType>* balancedAdd(LinkedBTreeNode<ItemType>* subTreePtr, LinkedBTreeNode<ItemType>* newNodePtr);
    LinkedBTreeNode<ItemType>* removeValue(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful);
    LinkedBTreeNode<ItemType>* moveValuesUpTree(LinkedBTreeNode<ItemType>* subTreePtr);
    LinkedBTreeNode<ItemType>* findNode(LinkedBTreeNode<ItemType>* treePtr, const ItemType& target, bool& isSuccessful) const;
    LinkedBTreeNode<ItemType>* copyTree(const LinkedBTreeNode<ItemType>* oldTreeRootPtr) const;

    void destroyTree(LinkedBTreeNode<ItemType>* subTreePtr);
    void preorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const;
    void inorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const;
    void postorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const;

};
#include "linkedBTree.cpp"
#endif