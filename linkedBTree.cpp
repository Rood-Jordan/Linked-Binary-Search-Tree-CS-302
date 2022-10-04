//Jordan Rood - Binary tree cpp file

template<class ItemType>
LinkedBTree<ItemType>::LinkedBTree(){
    rootPtr = nullptr;
}

template<class ItemType>
bool LinkedBTree<ItemType>::isEmpty() const{
    return rootPtr == nullptr;
}

template<class ItemType>
int LinkedBTree<ItemType>::getHeight() const{
    return getHeightHelper(rootPtr);
}

template<class ItemType>
int LinkedBTree<ItemType>::getNumberOfNodes() const{
    return getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType LinkedBTree<ItemType>::getRootData() const{
    if(rootPtr != nullptr){
        return rootPtr->getItem();
    }
    else{
        throw "Tree is empty so cannot return root data!";
    }
}

template<class ItemType>
bool LinkedBTree<ItemType>::add(const ItemType& newEntry){
    LinkedBTreeNode<ItemType>* newNodePtr = new LinkedBTreeNode<ItemType>(newEntry, nullptr, nullptr);

    rootPtr = balancedAdd(rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
bool LinkedBTree<ItemType>::remove(const ItemType& anEntry){
    bool isFound = false;
    if(isEmpty()){
        cout << "Binary Tree is empty!" << endl;
        return isFound;
    }

    rootPtr = removeValue(rootPtr, anEntry, isFound);
    return isFound;
}

template<class ItemType>
void LinkedBTree<ItemType>::clear(){
    if(rootPtr != nullptr){
        destroyTree(rootPtr);
    }
}

template<class ItemType>
ItemType LinkedBTree<ItemType>::getEntry(const ItemType& anEntry) const{
    bool gotEntry = false;
    if(isEmpty()){
        throw "Tree is empty so cannot get item!";
    }
    else{
        LinkedBTreeNode<ItemType>* node = findNode(rootPtr, anEntry, gotEntry);
        return node->getItem();
    }
}

template<class ItemType>
bool LinkedBTree<ItemType>::contains(const ItemType& anEntry) const{
    bool isInTree = false;
    if(isEmpty()){
        throw "Tree is empty so no entry to get!";
    }
    else{
        LinkedBTreeNode<ItemType>* node = findNode(rootPtr, anEntry, isInTree);
    }
    return isInTree;
}

template<class ItemType>
LinkedBTree<ItemType>::~LinkedBTree(){
    destroyTree(rootPtr);
}

template<class ItemType>
void LinkedBTree<ItemType>::preorderTraverse(void visit(ItemType&)) const{
    preorder(visit, rootPtr);
}

template<class ItemType>
void LinkedBTree<ItemType>::inorderTraverse(void visit(ItemType&)) const{
    inorder(visit, rootPtr);
}

template<class ItemType>
void LinkedBTree<ItemType>::postorderTraverse(void visit(ItemType&)) const{
    postorder(visit, rootPtr);
}

//helper functions
template<class ItemType>
int LinkedBTree<ItemType>::getHeightHelper(LinkedBTreeNode<ItemType>* subTreePtr) const{
    if(subTreePtr == nullptr){
        return 0;
    }
    else{
        return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
    }
}

template<class ItemType>
int LinkedBTree<ItemType>::getNumberOfNodesHelper(LinkedBTreeNode<ItemType>* subTreePtr) const{
    if(subTreePtr == nullptr){
        return 0;
    }
    else{
        return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
    }
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBTree<ItemType>::balancedAdd(LinkedBTreeNode<ItemType>* subTreePtr, LinkedBTreeNode<ItemType>* newNodePtr){
    if(subTreePtr == nullptr){
        return newNodePtr;
    }
    else{
        LinkedBTreeNode<ItemType>* leftPtr = subTreePtr->getLeftChildPtr();
        LinkedBTreeNode<ItemType>* rightPtr = subTreePtr->getRightChildPtr();

        if(getHeightHelper(leftPtr) > getHeightHelper(rightPtr)){
            rightPtr = balancedAdd(rightPtr, newNodePtr);

            subTreePtr->setRightChildPtr(rightPtr);
        }
        else{
            leftPtr = balancedAdd(leftPtr, newNodePtr);

            subTreePtr->setLeftChildPtr(leftPtr);
        }
        return subTreePtr;
    }
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBTree<ItemType>::removeValue(LinkedBTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful){
    //starting at the root, find the deepest and rightmost node in binary tree and node to delete
    if(subTreePtr == nullptr){
        isSuccessful = false;
        return nullptr;
    }
    else if(subTreePtr->getItem() == target){
        subTreePtr = moveValuesUpTree(subTreePtr);
        isSuccessful = true;
        return subTreePtr;
    }
    else{
        LinkedBTreeNode<ItemType>* tempLeft = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
        LinkedBTreeNode<ItemType>* tempRight = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
        if(tempLeft != nullptr){
            return tempLeft;
        }
        else{
            return tempRight;
        }
    }
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBTree<ItemType>::moveValuesUpTree(LinkedBTreeNode<ItemType>* subTreePtr){
    LinkedBTreeNode<ItemType>* tempPtr;
    if(subTreePtr->isLeaf()){
        delete subTreePtr;
        subTreePtr = nullptr;
        return nullptr;
    }
    else if(subTreePtr->getLeftChildPtr() != nullptr && subTreePtr->getRightChildPtr() == nullptr){
        tempPtr = subTreePtr->getLeftChildPtr();
        delete subTreePtr;
        subTreePtr = nullptr;
        return tempPtr;
    }
    else if(subTreePtr->getLeftChildPtr() == nullptr && subTreePtr->getRightChildPtr() != nullptr){
        tempPtr = subTreePtr->getRightChildPtr();
        delete subTreePtr;
        subTreePtr = nullptr;
        return tempPtr;
    }
    else{
        tempPtr = subTreePtr->getLeftChildPtr();
        subTreePtr->setItem(tempPtr->getItem());
        moveValuesUpTree(tempPtr);
    }
    return subTreePtr;
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBTree<ItemType>::findNode(LinkedBTreeNode<ItemType>* treePtr, const ItemType& target, bool& isSuccessful) const{
    if(treePtr == nullptr || treePtr->getItem() == target){
        return treePtr;
    }
    else if(treePtr != nullptr && treePtr->getItem() == target){
        return treePtr; 
    }
    else{
        LinkedBTreeNode<ItemType>* leftPtr = findNode(treePtr->getLeftChildPtr(), target, isSuccessful);
        treePtr->setLeftChildPtr(leftPtr);
        LinkedBTreeNode<ItemType>* rightPtr = findNode(treePtr->getRightChildPtr(), target, isSuccessful);
        treePtr->setRightChildPtr(rightPtr);
        if(leftPtr != nullptr){
            return leftPtr;
        }
        else{
            return rightPtr;
        }
    }
    isSuccessful = true;
}

template<class ItemType>
LinkedBTreeNode<ItemType>* LinkedBTree<ItemType>::copyTree(const LinkedBTreeNode<ItemType>* oldTreeRootPtr) const{
    LinkedBTreeNode<ItemType>* newTreePtr;

    if(oldTreeRootPtr !=nullptr){
        newTreePtr = LinkedBTreeNode<ItemType>(oldTreeRootPtr->getItem(), nullptr, nullptr);

        newTreePtr->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr()));
        newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
    }
}

template<class ItemType>
void LinkedBTree<ItemType>::destroyTree(LinkedBTreeNode<ItemType>* subTreePtr){
    if(subTreePtr == nullptr){
        return;
    }
    //destroy tree
    destroyTree(subTreePtr->getLeftChildPtr());
    destroyTree(subTreePtr->getRightChildPtr());
    free(subTreePtr);
}

template<class ItemType>
void LinkedBTree<ItemType>::preorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const{
    if(treePtr != nullptr){
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
    }
}

template<class ItemType>
void LinkedBTree<ItemType>::inorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const{
    if(treePtr != nullptr){
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        inorder(visit, treePtr->getRightChildPtr());
    }
}

template<class ItemType>
void LinkedBTree<ItemType>::postorder(void visit(ItemType&), LinkedBTreeNode<ItemType>* treePtr) const{
    if(treePtr != nullptr){
        postorder(visit, treePtr->getLeftChildPtr());
        postorder(visit, treePtr->getRightChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
    }
}