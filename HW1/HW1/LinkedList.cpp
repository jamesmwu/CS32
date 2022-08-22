//
//  LinkedList.cpp
//  HW1
//
//  Created by James Wu on 7/1/22.
//

#include <stdio.h>
#include "LinkedList.h"
using namespace std;

//Constructor
LinkedList::LinkedList(){
    head = nullptr;
    tot = 0;
}

//Copy constructor
LinkedList::LinkedList(const LinkedList& rhs){
    if(rhs.size() == 0){
        tot = 0;
        head = nullptr;
        return;
    }
    
    head = new Node();
    rhs.get(0, head->value);
    tot = 1;
    
    Node* p = head;
    for(int i = 1; i < rhs.size(); i++){
        Node* add = new Node();
        rhs.get(i, add->value);
        p->next = add;
        p = p->next;
        tot++;
    }
}

//Destructor
LinkedList::~LinkedList(){
    Node* p = head;
    while(p){
        Node* temp = p;
        p=p->next;
        delete temp;
        temp = nullptr;
    }
    head = nullptr;
    tot = 0;
}

//Assignment operator
const LinkedList& LinkedList::operator=(const LinkedList& rhs){
    
    //Delete all items in existing linked list
    while(head){
        Node* temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
    
    tot = 0;
    
    if(rhs.size() == 0) return *this;
    
    //Assign head to new node
    head = new Node();
    rhs.get(0, head->value);
    tot++;
    
    Node* p = head;
    //Make "this" point to a copy of rhs
    for(int i = 1; i < rhs.size(); i++){
        p->next = new Node();
        p = p->next;
        rhs.get(i, p->value);
        tot++;
    }
    
    return *this;
}

//Insert val at front of list
void LinkedList::insertToFront(const ItemType &val){
    Node* add = new Node();
    add->value = val;
    add->next = head;
    head = add;
    tot++;
}

//Print LinkedList
void LinkedList::printList() const{
    if(!head) return;
    
    Node* p = head;
    while(p){
        cout << p->value << " ";
        p = p->next;
    }
    cout << endl;
}

//Sets the "item" to value at specified position, return false if i is invalid index
bool LinkedList::get(int i, ItemType& item) const{
    if(i < 0 || i >= tot) return false;
    
    Node* p = head;
    for(int j = 0; j < i; j++){
        p = p->next;
    }
    
    item = p->value;
    return true;
}

//Reverses linked list
void LinkedList::reverseList(){
    if(!head) return;
    
    Node* p = head;
    while(p->next){
        //Flip around nodes
        Node* temp = p->next;
        p->next = temp->next;
        temp->next = head;
        
        head = temp;
    }
}

//Prints LinkedList in reverse order
void LinkedList::printReverse() const{
    if(!head) return;
    
    Node* cur = head;
    Node* last = nullptr;
    
    while(last != head){
        //Determine element to print
        while(cur->next != last){
            cur = cur->next;
        }
        
        last = cur;
        cout << cur->value << " ";
        cur = head;
    }
    cout <<  endl;
}

//Appends values of other onto end of Linked List
void LinkedList::append(const LinkedList &other){
    //Edge case of if head is nullptr or empty list is passed in
    if(other.size() == 0) return;
    if(!head){
        Node* p = new Node();
        other.get(0, p->value);
        head = p;
        
        for(int i = 1; i < other.size(); i++){
            Node* add = new Node();
            other.get(i, add->value);
            p->next = add;
            p = p->next;
            tot++;
        }
        
        return;
    }
    
    Node* p = head;
    while(p->next){
        p = p->next;
    }
    
    for(int i = 0; i < other.size(); i++){
        Node* add = new Node();
        other.get(i, add->value);
        p->next = add;
        p = p->next;
        tot++;
    }
    
}

//Swaps contents of LinkedList with the other one
void LinkedList::swap(LinkedList &other){
    LinkedList temp = other;
    other = *this;
    *this = temp;
}

//Returns number of items in LL
int LinkedList::size() const{
//    Node* p = head;
//    int count = 0;
//    while(p){
//        p = p->next;
//        count++;
//    }
    
//    return count;
    
    return tot;
}
