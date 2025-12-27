// Practice_lab6.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Graded_lab6.cpp
#include <iostream>
#include "StringLinkedList.h"
using namespace std;

int main() {
    StringLinkedList list;
    StringLinkedList listOne;
    StringLinkedList listTwo;

    list.addFront("XYZ");
    list.addFront("CDE");
    list.addFront("ABC");

    listOne.addFront("MAN");
    listOne.addFront("CAN");
    listOne.addFront("VAN");

    listTwo.addFront("XYZ");
    listTwo.addFront("CDE");
    listTwo.addFront("ABC");

    std::cout << "Initial list: ";
    list.display();

    // Add an element at the end of the list
    list.addBack("MNO");
    cout << "After adding 'MNO' at the end: ";
    list.display();

    // Remove the last element
    list.removeLast();
    cout << "After removing the last element: ";
    list.display();

    // Double the list
    list.doubleList();
    cout << "After doubling the list: ";
    list.display();

    // Search the list
    list.search("XYZzzz");
    list.search("XYZ");

    // Insert in the middle
    cout << "List before insertion: ";
    list.display();
    list.insertToClass(5, "BAT");

    // Are two lists equal?
    list.isEqual(listOne);
    list.isEqual(listTwo);

    return 0;
}