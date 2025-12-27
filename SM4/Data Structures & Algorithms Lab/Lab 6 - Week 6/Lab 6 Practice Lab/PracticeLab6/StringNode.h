#pragma once

#include <string>
using namespace std;

class StringNode
{
private:
    string elem;				        // element value
    StringNode* next;				    // next item in the list

    friend class StringLinkedList;		// provide StringLinkedList access
};