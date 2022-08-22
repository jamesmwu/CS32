//
//  WeddingGuest.cpp
//  Project 2
//
//  Created by James Wu on 7/4/22.
//

//#include <stdio.h>
#include "WeddingGuest.h"

//Constructor
WeddingGuest::WeddingGuest(){
    head = nullptr;
}

//Destructor
WeddingGuest::~WeddingGuest(){
    while(head){
        Node *p = head;
        head = head->next;
        delete p;
    }
}

//Copy Constructor
WeddingGuest::WeddingGuest(const WeddingGuest& copy){
    if(copy.noGuests()) return;
    
    //Assign head to a new node (there must be at least one node since above statement didn't return)
    head = new Node();
    copy.verifyGuestOnTheList(0, head->first, head->last, head->val);
    
    Node *p = head;
    Node *dummy = new Node();
    Node *dummyHead = dummy;
    dummy->next = head;
    
    //Iterate through copy and assign each node to a node in this linked list
    for(int i = 1; i < copy.guestCount(); i++){
        Node *add = new Node();
        copy.verifyGuestOnTheList(i, add->first, add->last, add->val);
        p->next = add;
        p->prev = dummy;
        p = p->next;
        dummy = dummy->next;
    }
    
    //Delete all dynamically allocated extra Nodes and reassign pointers
    delete dummyHead;
    dummyHead = nullptr;
    dummy = nullptr;
    p = nullptr;
    
}

//Assignment Operator
const WeddingGuest& WeddingGuest::operator=(const WeddingGuest& copy){
    
    //First, clear existing WeddingGuest object
    while(head){
        Node *p = head;
        head = head->next;
        delete p;
    }
    
    //Now copy in new objects into this one
    if(copy.noGuests()) return *this;
    
    head = new Node();
    copy.verifyGuestOnTheList(0, head->first, head->last, head->val);
    
    Node *p = head;
    Node *dummy = new Node();
    Node *dummyHead = dummy;
    dummy->next = head;
    
    //Iterate through copy and assign all nodes to equal those of copy
    for(int i = 1; i < copy.guestCount(); i++){
        Node *add = new Node();
        copy.verifyGuestOnTheList(i, add->first, add->last, add->val);
        p->next = add;
        p->prev = dummy;
        p = p->next;
        dummy = dummy->next;
    }
    
    delete dummyHead;
    dummyHead = nullptr;
    dummy = nullptr;
    p = nullptr;
    
    return *this;
}

//Return true if WeddingGuest list is empty, else false
bool WeddingGuest::noGuests() const {
    //If there exists at least one element (head), then the list is not empty.
    return head ? false : true;
}

//Return number of matches on WeddingGuest list
int WeddingGuest::guestCount() const {
    int count = 0;
    Node *p = head;
    
    //Iterate through list and keep track of how many items there are.
    while(p){
        p = p->next;
        count++;
    }
    
    return count;
}

bool WeddingGuest::inviteGuest(const std::string &firstName, const std::string &lastName, const GuestType &value){
    //No items in list edge case
    if(!head){
        head = new Node(firstName, lastName, value);

        return true;
    }
    
    Node *p = head;
    
    while(p){
        //Guest already exists
        if(p->first == firstName && p->last == lastName) return false;
        
        p = p->next;
    }
    
    //The name must be unique
    p = head;
    Node *dummyHead = new Node();
    Node *dummy = dummyHead;
    dummy->next = head; //Dummy node to track prev
    bool added = false;
    
    //Iterate through list and use comparison operators to determine whether an object is in the correct alphabetical order
    while(p){
        //Edge case
        if(lastName < p->last && p == head){
            Node *add = new Node(firstName, lastName, value, head, nullptr);
            head = add;
            added = true;
            break;
        }
        else if(lastName < p->last){
            Node *add = new Node(firstName, lastName, value, p, dummy);
            dummy->next = add;
            p->prev = add;
            added = true;
            break;
        }
        else if(lastName == p->last){
            if(firstName < p->first){
                Node *add = new Node(firstName, lastName, value, p, dummy);
                dummy->next = add;
                p->prev = add;
                added = true;
                break;
            }
        }
        
        dummy = dummy->next;
        p = p->next;
        
    }
    
    //Account for case where inserted values are at the tail end of node
    if(!added){
        //Dummy will be at the tail when p ends
        Node *add = new Node(firstName, lastName, value, nullptr, dummy);
        dummy->next = add;
    }
    
    delete dummyHead;
    
    return true;
}

bool WeddingGuest::alterGuest(const std::string &firstName, const std::string &lastName, const GuestType &value){
    
    Node *p = head;
    //Iterate through list, if first and last are equivalent then alter value
    while(p){
        if(p->first == firstName && p->last == lastName){
            p->val = value;
            return true;
        }
        p = p->next;
    }
    
    return false;
}

bool WeddingGuest::inviteOrAlter(const std::string &firstName, const std::string &lastName, const GuestType &value){
    
    //If the name can be altered, alter guest. Otherwise, the name does not exist and guest should be invited.
    if(alterGuest(firstName, lastName, value))
        alterGuest(firstName, lastName, value);
    else
        inviteGuest(firstName, lastName, value);
    
    return true;
}

bool WeddingGuest::crossGuestOff(const std::string &firstName, const std::string &lastName){
    
    Node *p = head;
    Node *dummyHead = new Node();
    Node *dummy = dummyHead;    //Used to track prev node
    dummy->next = head;
    
    //Iterate through list and delete when target is found
    while(p){
        if(p->first == firstName && p->last == lastName){
            //Edge case if p is at head
            if(p == head) head = p->next;
            
            dummy->next = p->next;
            //Edge case if p is at the tail
            if(p->next) p->next->prev = dummy;
            
            delete p;
            delete dummyHead;
            return true;
        }
        dummy = dummy->next;
        p = p->next;
    }
    
    delete dummyHead;
    return false;
}

bool WeddingGuest::invitedToTheWedding(const std::string &firstName, const std::string &lastName) const {
    Node *p = head;
    //Iterate through list until the target name is found, if not found then return false
    while(p){
        if(p->first == firstName && p->last == lastName){
            return true;
        }
        p = p->next;
    }
    
    return false;
}

bool WeddingGuest::matchInvitedGuest(const std::string &firstName, const std::string &lastName, GuestType &value) const {
    Node *p = head;
    //Iterate through list, if target name is found then reassign value, otherwise return false
    while(p){
        if(p->first == firstName && p->last == lastName){
            value = p->val;
            return true;
        }
        p = p->next;
    }
    
    return false;
}

bool WeddingGuest::verifyGuestOnTheList(int i, std::string &firstName, std::string &lastName, GuestType &value) const {
    int tot = 0;
    Node *p = head;
    
    //Determine total guests on list
    while(p){
        tot++;
        p = p->next;
    }
    
    //Account for edge cases and if index is valid
    if(tot == 0) return false;
    else if(i < 0 || i >= tot) return false;
    
    p = head;
    //Places pointer p exactly on the target node
    for(int j = 0; j < i; j++){
        p = p->next;
    }
    
    //Reassign parameters
    firstName = p->first;
    lastName = p->last;
    value = p->val;
    
    return true;
    
}

void WeddingGuest::swapWeddingGuests(WeddingGuest &other){
    //Use temp var with copy constructor and assignment operator in order to swap guests.
    //"temp" will auto destruct at the end of this block of code.
    WeddingGuest temp = other;
    other = *this;
    *this = temp;
    
}

bool joinGuests(const WeddingGuest & odOne, const WeddingGuest & odTwo, WeddingGuest & odJoined){
    
    //To account for edge cases, wait until end to assign odJoined = returnGuest
    WeddingGuest returnGuest = odOne;
    bool ret = true;
    
    //Append all of odTwo to returnGuest
    for(int i = 0; i < odTwo.guestCount(); i++){
        std::string first;
        std::string last;
        GuestType val;
        GuestType val2;
        
        odTwo.verifyGuestOnTheList(i, first, last, val);
        
        //Determine if the entry has a match in returnGuest
        bool add = returnGuest.matchInvitedGuest(first, last, val2);
        
        //Either the name doesn't even exist, or the name exists and the values are same
        if(!add || (add && val == val2))
            returnGuest.inviteGuest(first, last, val);
        
        //Otherwise, the name exists and values are different. Cross off the name.
        else{
            returnGuest.crossGuestOff(first, last);
            ret = false;
        }
        
    }
    
    odJoined = returnGuest;
    
    return ret;
}

void attestGuests (const std::string& fsearch,
 const std::string& lsearch,
 const WeddingGuest& odOne,
 WeddingGuest& odResult){
    
    //Catch edge case if odResult and odOne refer to same WeddingGuest.
    WeddingGuest search;
    search = odOne;
    
    //Ensure odResult is cleared.
    WeddingGuest temp;
    odResult = temp;    //This ensures odResult starts with no elements.

    for(int i = 0; i < search.guestCount(); i++){
        std::string first;
        std::string last;
        GuestType val;
        
        search.verifyGuestOnTheList(i, first, last, val);
        
        //Invite guest if it fits parameter
        if((first == fsearch && last == lsearch)
           || (first == fsearch && lsearch == "*")
           || (fsearch == "*" && last == lsearch)
           || (fsearch == "*" && lsearch == "*"))
            odResult.inviteGuest(first, last, val);
    }
    
}
