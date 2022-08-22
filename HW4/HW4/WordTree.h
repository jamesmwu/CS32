//
//  WordTree.h
//  HW4
//
//  Created by James Wu on 8/8/22.
//

#ifndef WordTree_h
#define WordTree_h

#include <iostream>
#include <string>   //Should this be included if the HW runs without it

typedef std::string WordType;

struct WordNode {
    WordType m_data;
    WordNode *m_left;
    WordNode *m_right;
    int repeats;    //Starts at 0

    WordNode(WordType v) : m_data(v), repeats(0), m_left(nullptr), m_right(nullptr) {}
};


class WordTree {
private:
    WordNode *root;
    WordNode* insert(WordNode* root, WordType val);
    int searchNodes(WordNode* root, bool includeDupes) const;
    std::string print(WordNode* root, std::string& result) const;
    void reassign(const WordNode* root);
    void cleanUp(WordNode*& root);
    WordNode* copyInsert(WordNode* root, WordType val, int repeats);
    
public:
    // default constructor
    WordTree();

    // copy constructor
    WordTree(const WordTree& rhs);

    // assignment operator
    const WordTree& operator=(const WordTree& rhs);
        
    // Inserts v into the WordTree
    void add(WordType v);
        
    // Returns the number of distinct words / nodes
    int distinctWords() const;
    
    // Returns the total number of words inserted, including duplicate values
    int totalWords() const;

    // Prints the WordTree
    friend std::ostream& operator<<(std::ostream &out, const WordTree& rhs);
    
    // Destroys all the dynamically allocated memory in the tree
    ~WordTree();
    
};

#endif /* WordTree_h */
