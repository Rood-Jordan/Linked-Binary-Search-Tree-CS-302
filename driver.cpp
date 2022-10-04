//Jordan Rood
//Homework 5 - Binary Search Tree & Binary Tree
//11-01-2021

#include <iostream>
#include <fstream>
#include "linkedBTree.h"
#include "bSearchTree.h"
#define SIZE 100

using namespace std;

void visit(int& );
void writeToFile(int& );
void fileFormat();

int main(){
    int numbers[SIZE];

    for(int i = 0; i < SIZE; i++){
        int random = rand() % 200 + 1;
        numbers[i] = random;
    }

    try{
        LinkedBSearchTree<int> bSearch;

        //insert them into the BST 
        for(int i = 0; i < SIZE; i++){
            bSearch.add(numbers[i]);
        }

        //print height and inorder, preorder, postorder traversals to a test file
        ofstream testFile;
        testFile.open("test.txt", ios::out);
        testFile << "Binary Search Tree Test File" << endl;
        testFile << "Height: " << bSearch.getHeight() << endl;
        testFile << "1st line - Preorder Traversal " << endl;
        testFile << "2nd line - Inorder Traversal " << endl;
        testFile << "3rd line - Postorder Traversal " << endl;
        testFile.close();

        bSearch.preorderTraverse(writeToFile);
        fileFormat();
        bSearch.inorderTraverse(writeToFile);
        fileFormat();
        bSearch.postorderTraverse(writeToFile);
    }
    catch(const char* e){
        cout << e << endl;
    }

    return 0;
}

void visit(int& item){
    cout << item << " ";
}

void writeToFile(int& item){
    ofstream testFile;
    testFile.open("test.txt", ios::app);
    testFile << item << " ";
    testFile.close();
}

void fileFormat(){
    ofstream testFile;
    testFile.open("test.txt", ios::app);
    testFile << "\n";
    testFile.close();
}