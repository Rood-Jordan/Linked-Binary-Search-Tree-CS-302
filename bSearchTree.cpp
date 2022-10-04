//Jordan Rood - Binary search tree cpp file

template<class ItemType>
bool LinkedBSearchTree<ItemType>::add(const ItemType& newData){
    LinkedBTreeNode<ItemType>* newNodePtr = new LinkedBTreeNode<ItemType>(newData, nullptr, nullptr);

    this->rootPtr = placeNode(this->rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
bool LinkedBSearchTree<ItemType>::remove(const ItemType& data){
    bool isFound = false;
    if(this->isEmpty()){
        cout << "Binary Search Tree is empty!" << endl;
        return isFound;
    }

    this->rootPtr = removeValue(this->rootPtr, data, isFound);
    return isFound;
}

template<class ItemType>
ItemType LinkedBSearchTree<ItemType>::getEntry(const ItemType& anEntry) const{
    LinkedBTreeNode<ItemType>* nodePtr = findNode(this->rootPtr, anEntry);

    if(nodePtr != nullptr){
        return nodePtr->getItem();
    }
    else{
        throw "Binary search tree item not found!";
    }
}


//helper functions
template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::placeNode(LinkedBTreeNode<ItemType>* subTreePtr, LinkedBTreeNode<ItemType>* newNodePtr){
    if(subTreePtr == nullptr){
        return newNodePtr;
    }
    else if(subTreePtr->getItem() > newNodePtr->getItem()){
        LinkedBTreeNode<ItemType>* goingLeftPtr = placeNode(subTreePtr->getLeftChildPtr(), newNodePtr);
        subTreePtr->setLeftChildPtr(goingLeftPtr);
    }
    else{
        LinkedBTreeNode<ItemType>* goingRightPtr = placeNode(subTreePtr->getRightChildPtr(), newNodePtr);
        subTreePtr->setRightChildPtr(goingRightPtr); 
    }
    return subTreePtr;
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeValue(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful){
    if(subTreePtr == nullptr){
        isSuccessful = false;
    }
    else if(subTreePtr->getItem() == target){
        isSuccessful = true;
        return removeNode(subTreePtr);
    }
    else if(subTreePtr->getItem() > target){
        LinkedBTreeNode<ItemType>* temporaryPtr = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
        subTreePtr->setLeftChildPtr(temporaryPtr);
    }
    else{
        LinkedBTreeNode<ItemType>* temporaryPtr = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
        subTreePtr->setRightChildPtr(temporaryPtr);
    }
    return subTreePtr;
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeNode(LinkedBTreeNode<ItemType>* nodePtr){
    if(nodePtr == nullptr){
        //if node is a leaf
        delete nodePtr;
        nodePtr = nullptr;
        return nullptr;
    }
    else if(nodePtr->getLeftChildPtr() == nullptr && nodePtr->getRightChildPtr() != nullptr  || nodePtr->getLeftChildPtr() != nullptr && nodePtr->getRightChildPtr() == nullptr){
        //if node has only one child
        delete nodePtr;
        if(nodePtr->getLeftChildPtr() != nullptr){
            return nodePtr->getLeftChildPtr();
        }
        else{
            return nodePtr->getRightChildPtr();
        }
    }
    else{
        //if node has two children
        //find inorder successor(leftmost node)
        ItemType item = nodePtr->getItem();
        LinkedBTreeNode<ItemType>* successor = removeLeftmostNode(this->rootPtr, item);
        //remove it
        delete nodePtr;
        nodePtr = nullptr;
        //return inorder successor (to replace current node)
        return successor;
    }
    return nodePtr;
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeLeftmostNode(LinkedBTreeNode<ItemType>* nodePtr, ItemType& inorderSuccessor){
    if(nodePtr->getLeftChildPtr() == nullptr){
        inorderSuccessor = nodePtr->getItem();
        return removeNode(nodePtr);
    }
    else{
        LinkedBTreeNode<ItemType>* temporaryPtr = removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor);
        nodePtr->setLeftChildPtr(temporaryPtr);
        return nodePtr;
    }
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBSearchTree<ItemType>::findNode(LinkedBTreeNode<ItemType>* treePtr, const ItemType& target) const{
    if(treePtr == nullptr || treePtr->getItem() == target){
        //if node is a leaf or equals target
        return treePtr;
    }
    else if(treePtr->getItem() > target){
        //if node is of greater precedence than target
        return findNode(treePtr->getLeftChildPtr(), target); 
    }
    else{
        //if node is of lesser precedence than target 
        return findNode(treePtr->getRightChildPtr(), target);
    }
}