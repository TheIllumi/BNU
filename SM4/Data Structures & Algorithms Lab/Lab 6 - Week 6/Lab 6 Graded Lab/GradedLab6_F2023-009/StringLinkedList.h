#pragma once

#include <iostream>
using namespace std;

#include "StringNode.h"

class StringLinkedList
{
public:
    StringLinkedList();				    // empty list constructor
    ~StringLinkedList();			    // destructor
    bool empty() const;				    // is list empty?
    const string& front() const;		// get front element
    void addFront(const string& e);		// add to front of list
    void removeFront();				    // remove front item list
    void display() const;                // display all elements
    void removeLast();                   // delete last element
    void addBack(const string& e);       // add element at the end
    void doubleList();                   // double the list
    int search(const string& e);          // Search the node
    void insertToClass(int index, const string& e);  // Insert in the middle
    bool isEqual(StringLinkedList& other); // are two lists equal?
private:
    StringNode* head;				    // pointer to the head of list
};
