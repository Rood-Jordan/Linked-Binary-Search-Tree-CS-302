#ifndef LINKED_BINARY_TREE_NODE_H
#define LINKED_BINARY_TREE_NODE_H

using namespace std;

template<class ItemType>
class LinkedBTreeNode {
    ItemType item;
    LinkedBTreeNode<ItemType>* leftChildPtr;
    LinkedBTreeNode<ItemType>* rightChildPtr;

public:
    LinkedBTreeNode();
    LinkedBTreeNode(const ItemType& newData, LinkedBTreeNode<ItemType>* left, LinkedBTreeNode<ItemType>* right);
    void setItem(const ItemType& newData);
    ItemType getItem() const;
    bool isLeaf() const;

    LinkedBTreeNode<ItemType>* getLeftChildPtr() const;
    LinkedBTreeNode<ItemType>* getRightChildPtr() const;

    void setLeftChildPtr(LinkedBTreeNode<ItemType>* newLeftChildPtr);
    void setRightChildPtr(LinkedBTreeNode<ItemType>* newRightChildPtr);
};

#include "linkedBTreeNode.cpp"
#endif