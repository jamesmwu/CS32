//
//  WordTree.cpp
//  HW4
//
//  Created by James Wu on 8/8/22.
//

#include "WordTree.h"
//#include <iostream>
//#include <string>

//Constructor
WordTree::WordTree() : root(nullptr){
    
}

//Copy Constructor
WordTree::WordTree(const WordTree& rhs){
    root = nullptr; //Prevent undefined behavior
    
    //rhs is the EXISTING WordTree, assign all nodes in rhs to this BST
    reassign(rhs.root);
}

//PRIVATE helper function to reassign in copy constructor
void WordTree:: reassign(const WordNode *otherRoot){

    //Traverse all nodes and insert them into the BST.
    if(!otherRoot) return;
    
    reassign(otherRoot->m_left);   //Traverse left
    root = copyInsert(root, otherRoot->m_data, otherRoot->repeats);  //Process current
    reassign(otherRoot->m_right);    //Traverse right;
    
}

//PRIVATE helper function to insert from copy constructor (includes repeats)
WordNode* WordTree::copyInsert(WordNode *root, WordType val, int repeats){
    if(!root){
        WordNode* ins = new WordNode(val);
        ins->repeats = repeats;
        
        return ins;   //NULL base case
    }

    if(root->m_data < val)
        root->m_right = copyInsert(root->m_right, val, repeats);
    else if(root->m_data > val)
        root->m_left = copyInsert(root->m_left, val, repeats);

    return root;
}

//Assignment Operator
const WordTree& WordTree::operator=(const WordTree& rhs) {
    //Edge case to catch aliasing using CC
    WordTree dup = rhs;
        
    //Clear everything in this tree
    cleanUp(root);
    
    //Reassign everything from rhs into this tree
    reassign(dup.root);
    
    return *this;
}

//Insert v into WordTree
void WordTree::add(WordType v){
    
    //Helper function to recursively insert node.
    root = insert(root, v);
    
}

//PRIVATE helper function insert
WordNode* WordTree::insert(WordNode* root, WordType val){
    if(!root) return new WordNode(val);   //NULL base case
    
    if(root->m_data < val)
        root->m_right = insert(root->m_right, val);
    else if(root->m_data > val)
        root->m_left = insert(root->m_left, val);
    //There is an existing node with the same data type. Increment repeats and return.
    else
        root->repeats++;
    
    return root;
}

//Return number of distinct words / nodes
int WordTree::distinctWords() const {
    //Travel to each distinct node, don't count dupes
    return searchNodes(root, false);
}

//Return total number of words inserted, including duplicate vals
int WordTree::totalWords() const {
    //Travel to each node and count dupes
    return searchNodes(root, true);
}

//PRIVATE helper function searchNodes that finds distinct OR duplicate nodes
int WordTree::searchNodes(WordNode *root, bool includeDupes) const{
    if(!root) return 0;
    
    //Searches both left and right sides of existing node
    if(includeDupes)
        return 1 + root->repeats + searchNodes(root->m_left, true) + searchNodes(root->m_right, true);
    else
    return 1 + searchNodes(root->m_left, false) + searchNodes(root->m_right, false);
}

//Print WordTree in-order
std::ostream& operator << (std::ostream& stream, const WordTree& obj) {
    //If WordTree is empty print nothing
    if(!obj.root){
        stream << "";
    }
    else {
        //Not allowed to use STL Stack for HW4, so recursively print
        std::string s = "";
        obj.print(obj.root, s);
        stream << s;
//        stream << obj.root->m_data << " " << (obj.root->repeats + 1);
    }
    
    return stream;
}

//PRIVATE helper function to print WordTree
std::string WordTree::print(WordNode *root, std::string& result) const{
    
    if(!root) return "";
    
    print(root->m_left, result);    //Traverse left
    
    result += root->m_data + " " + std::to_string(root->repeats + 1);    //Process current
    result += "\n";
    
    print(root->m_right, result);   //Traverse right
    
    return result;
}

//Destructor
WordTree::~WordTree(){
    cleanUp(root);
}

//PRIVATE helper function to delete all existing nodes in WordTree
void WordTree::cleanUp(WordNode*& root){
    //Traverse all nodes and delete them from the BST
    if(!root) return;
    
    cleanUp(root->m_left);   //Traverse left
    cleanUp(root->m_right);    //Traverse right;
    
    //Process current
    delete root;
    root = NULL;
    
}
