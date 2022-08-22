//
//  main.cpp
//  HW1
//
//  Created by James Wu on 7/1/22.
//

#include <iostream>
#include "LinkedList.h"
#include <cassert>

using namespace std;

int main(int argc, const char * argv[]) {
    LinkedList first;
    LinkedList second;
    
    first = second;
    first.insertToFront("Hi");
    first.insertToFront("Bye");
    first.insertToFront("what's up");
    
    first.printList();
    
    string s;
    assert(first.size() == 3 && first.get(1, s) && s == "Bye");
    
    LinkedList third = first;
    assert(third.size() == 3 && third.get(2, s) && s == "Hi");
    assert(first.size() == 3 && first.get(0, s) && s == "what's up");
    
    LinkedList fourth;
    fourth.insertToFront("one");
    fourth.insertToFront("two");
    fourth.insertToFront("three");
    assert(fourth.size() == 3 && fourth.get(0,s) && s == "three");
    
    cout<<endl;
    first.printList();
    first.reverseList();
    first.printList();
    first.printReverse();
    cout << endl;
    
    first.append(fourth);
    first.printList();
    first.reverseList();
    first.printList();
    first.printReverse();
    
    cout << endl;
    
    first.swap(fourth);
    first.printList();
    fourth.printList();
    
    cout<<endl;
    
    LinkedList ls;
    ls.insertToFront("Hawkeye");
    ls.insertToFront("Thor");
    ls.insertToFront("Hulk");
    ls.insertToFront("Black Widow");
    ls.insertToFront("Iron Man");
    ls.insertToFront("Captain America");
    for (int k = 0; k < ls.size(); k++)
    {
     string x;
     ls.get(k, x);
     cout << x << endl;
    }
    
    cout<<endl;
    
    LinkedList ls2;
    ls2.insertToFront("The Mandalorian");
    ls2.insertToFront("Baby Yoda");
    ls2.insertToFront("Cara Dune");
    ls2.insertToFront("Greef Karga");
    ls2.printList();
    ls2.printReverse();
    cout<<endl;
    
    LinkedList e1;
    e1.insertToFront("Athos");
    e1.insertToFront("Porthos");
    e1.insertToFront("Aramis");
    LinkedList e2;
    e2.insertToFront("Robin");
    e2.insertToFront("Batman");
    e1.append(e2); // adds contents of e2 to the end of e1
    assert(e1.size() == 5 && e1.get(3, s) && s == "Batman");
    assert(e2.size() == 2 && e2.get(1, s) && s == "Robin");
    
    LinkedList e3;
    e3.insertToFront("Jim");
    e3.insertToFront("Oz");
    e3.insertToFront("Paul");
    e3.insertToFront("Kevin");
    e3.reverseList(); // reverses the contents of e1
    assert(e3.size() == 4 && e3.get(0, s) && s == "Jim");
    
    LinkedList e4;
    e4.insertToFront("A");
    e4.insertToFront("B");
    e4.insertToFront("C");
    e4.insertToFront("D");
    LinkedList e5;
    e5.insertToFront("X");
    e5.insertToFront("Y");
    e5.insertToFront("Z");
    e4.swap(e5); // exchange contents of e1 and e2
    assert(e4.size() == 3 && e4.get(0, s) && s == "Z");
    assert(e5.size() == 4 && e5.get(2, s) && s == "B");
    
    cout<<endl;
    
    cout << "Passed" << endl;
}
