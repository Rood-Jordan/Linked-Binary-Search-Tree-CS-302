//Jordan Rood - Binary Search Tree header file

#ifndef BST_H
#define BST_H

#include "linkedBTreeNode.h"
#include "linkedBTree.h"

template<class ItemType>
class LinkedBSearchTree : public LinkedBTree<ItemType>{
    //Attribute & functions commented out are those inherited from the binary tree

    //LinkedBTreeNode<ItemType>* rootPtr;

public:
    //LinkedBSearchTree();
    //bool isEmpty() const override;
    //int getHeight() const;
    //int getNumberOfNodes() const;
    //ItemType getRootData() const;
    bool add(const ItemType& newData) override;
    bool remove(const ItemType& data) override;
    //void clear();
    ItemType getEntry(const ItemType& anEntry) const override;
    //bool contains(const ItemType& anEntry) const;

    //void preorderTraverse(void visit(ItemType&)) const;
    //void inorderTraverse(void visit(ItemType&)) const;
    //void postorderTraverse(void visit(ItemType&)) const;

    //~LinkedBSearchTree();
    
protected:
    LinkedBTreeNode<ItemType>* placeNode(LinkedBTreeNode<ItemType>* subTreePtr, LinkedBTreeNode<ItemType>* newNodePtr);
    LinkedBTreeNode<ItemType>* removeValue(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful);
    LinkedBTreeNode<ItemType>* removeNode(LinkedBTreeNode<ItemType>* nodePtr);
    LinkedBTreeNode<ItemType>* removeLeftmostNode(LinkedBTreeNode<ItemType>* nodePtr, ItemType& inorderSuccessor);
    LinkedBTreeNode<ItemType>* findNode(LinkedBTreeNode<ItemType>* treePtr, const ItemType& target) const;

};
#include "bSearchTree.cpp"
#endif