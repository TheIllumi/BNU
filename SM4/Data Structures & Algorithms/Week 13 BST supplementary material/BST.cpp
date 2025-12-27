#include <iostream>
#include <string>
using namespace std;

class IntBinaryTree
{
private:
    struct TreeNode
    {
        int value;         // The value in the node
        TreeNode* left;    // Pointer to left child node
        TreeNode* right;   // Pointer to right child node
    };

    TreeNode* root;       // Pointer to the root node

    // Private member functions
    void insert(TreeNode*&, TreeNode*&);
    void destroySubTree(TreeNode*);
    void deleteNode(int, TreeNode*&);
    void makeDeletion(TreeNode*&);
    void displayInOrder(TreeNode*) const;
    void displayPreOrder(TreeNode*) const;
    void displayPostOrder(TreeNode*) const;

public:
    // Constructor
    IntBinaryTree()
    {
        root = nullptr;
    }

    // Destructor
    ~IntBinaryTree()
    {
        destroySubTree(root);
    }

    // Binary tree operations
    void insertNode(int);
    bool searchNode(int);
    void remove(int);

    void displayInOrder() const
    {
        displayInOrder(root);
    }

    void displayPreOrder() const
    {
        displayPreOrder(root);
    }

    void displayPostOrder() const
    {
        displayPostOrder(root);
    }

    void showStructure() const;
    void showHelper(TreeNode* p, int level) const;
};

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************

void IntBinaryTree::insert(TreeNode*& nodePtr, TreeNode*& newNode)
{
    if (nodePtr == nullptr)
        nodePtr = newNode;                  // Insert the node.
    else if (newNode->value < nodePtr->value)
        insert(nodePtr->left, newNode);     // Search the left branch
    else
        insert(nodePtr->right, newNode);    // Search the right branch
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************

void IntBinaryTree::insertNode(int num)
{
    TreeNode* newNode = nullptr;	// Pointer to a new node.

    // Create a new node and store num in it.
    newNode = new TreeNode;
    newNode->value = num;
    newNode->left = newNode->right = nullptr;

    // Insert the node.
    insert(root, newNode);
}

//***************************************************
// destroySubTree is called by the destructor. It   *
// deletes all nodes in the tree.                   *
//***************************************************

void IntBinaryTree::destroySubTree(TreeNode* nodePtr)
{
    if (nodePtr)
    {
        if (nodePtr->left)
            destroySubTree(nodePtr->left);
        if (nodePtr->right)
            destroySubTree(nodePtr->right);
        cout << "\ndeleted" << nodePtr->value << "\n";
        delete nodePtr;
    }
}

//***************************************************
// searchNode determines if a value is present in   *
// the tree. If so, the function returns true.      *
// Otherwise, it returns false.                     *
//***************************************************

bool IntBinaryTree::searchNode(int num)
{
    TreeNode* nodePtr = root;

    while (nodePtr)
    {
        if (nodePtr->value == num)
            return true;
        else if (num < nodePtr->value)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }
    return false;
}

//**********************************************
// remove calls deleteNode to delete the       *
// node whose value member is the same as num. *
//**********************************************

void IntBinaryTree::remove(int num)
{
    deleteNode(num, root);
}


//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************

void IntBinaryTree::deleteNode(int num, TreeNode*& nodePtr)
{
    if (nodePtr)
    {
        if (num < nodePtr->value)
            deleteNode(num, nodePtr->left);
        else if (num > nodePtr->value)
            deleteNode(num, nodePtr->right);
        else
            makeDeletion(nodePtr);
    }
    else
        cout << "\nthis val doesn't exist in the tree\n";
}


//***********************************************************
// makeDeletion takes a reference to a pointer to the node  *
// that is to be deleted. The node is removed and the       *
// branches of the tree below the node are reattached.      *
//***********************************************************

void IntBinaryTree::makeDeletion(TreeNode*& nodePtr)
{
    // Define a temporary pointer to use in reattaching
    // the left subtree.
    TreeNode* tempNodePtr = nullptr;

    if (nodePtr == nullptr)
        cout << "Cannot delete empty node.\n";
    else if (nodePtr->right == nullptr)
    {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->left;   // Reattach the left child
        delete tempNodePtr;
    }
    else if (nodePtr->left == nullptr)
    {
        tempNodePtr = nodePtr;
        nodePtr = nodePtr->right;  // Reattach the right child
        delete tempNodePtr;
    }
    // If the node has two children.
    else
    {
        // Move one node the right.
        tempNodePtr = nodePtr->right;
        // Go to the end left node.
        while (tempNodePtr->left)
            tempNodePtr = tempNodePtr->left;
        // Reattach the left subtree.
        tempNodePtr->left = nodePtr->left;
        tempNodePtr = nodePtr;
        // Reattach the right subtree.
        nodePtr = nodePtr->right;
        delete tempNodePtr;
    }
}

//****************************************************************
// The displayInOrder member function displays the values        *
// in the subtree pointed to by nodePtr, via inorder traversal.  *
//****************************************************************

void IntBinaryTree::displayInOrder(TreeNode* nodePtr) const
{
    if (nodePtr)
    {
        displayInOrder(nodePtr->left);
        cout << nodePtr->value << endl;
        displayInOrder(nodePtr->right);
    }
}

//****************************************************************
// The displayPreOrder member function displays the values       *
// in the subtree pointed to by nodePtr, via preorder traversal. *
//****************************************************************

void IntBinaryTree::displayPreOrder(TreeNode* nodePtr) const
{
    if (nodePtr)
    {
        cout << nodePtr->value << endl;
        displayPreOrder(nodePtr->left);
        displayPreOrder(nodePtr->right);
    }
}

//****************************************************************
// The displayPostOrder member function displays the values      *
// in the subtree pointed to by nodePtr, via postorder traversal.*
//****************************************************************

void IntBinaryTree::displayPostOrder(TreeNode* nodePtr) const
{
    if (nodePtr)
    {
        displayPostOrder(nodePtr->left);
        displayPostOrder(nodePtr->right);
        cout << nodePtr->value << endl;
    }
}


void IntBinaryTree::showStructure() const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
    if (root == 0)
        cout << "Empty tree" << endl;
    else
    {
        cout << endl;
        showHelper(root, 1);
        cout << endl;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


void IntBinaryTree::showHelper(TreeNode* p, int level) const

// Recursive helper for showStructure. 
// Outputs the subtree whose root node is pointed to by p. 
// Parameter level is the level of this node within the tree.

{
    int j;   // Loop counter

    if (p != 0)
    {
        showHelper(p->right, level + 1);         // Output right subtree
        for (j = 0; j < level; j++)    // Tab over to level
            cout << "\t";
        cout << " " << p->value;   // Output key
        if ((p->left != 0) &&           // Output "connector"
            (p->right != 0))
            cout << "<";
        else if (p->right != 0)
            cout << "/";
        else if (p->left != 0)
            cout << "\\";
        cout << endl;
        showHelper(p->left, level + 1);          // Output left subtree
    }
}

int main()
{
    IntBinaryTree tree1;
    tree1.insertNode(100);
    tree1.insertNode(200);
    tree1.insertNode(50);
    tree1.insertNode(65);

    tree1.showStructure();

    tree1.remove(25);
    tree1.showStructure();
    // Display inorder.
    cout << "Inorder traversal:\n";
    tree1.displayInOrder();

    // Display preorder.
    cout << "\nPreorder traversal:\n";
    tree1.displayPreOrder();

    // Display postorder.
    cout << "\nPostorder traversal:\n";
    tree1.displayPostOrder();

    /*
    IntBinaryTree tree, tree1, tree3;

    tree3.insertNode(100);
    tree3.insertNode(95);
    tree3.insertNode(78);
    tree3.insertNode(120);
    tree3.insertNode(125);
    tree3.insertNode(124);
    tree3.displayPostOrder();
    tree3.showStructure();
    tree3.displayPreOrder();


    // VERSION A
    // Insert some nodes.
    cout << "Inserting nodes.\n";
    tree.insertNode(100);
    tree.insertNode(123);
    tree.insertNode(95);
    tree.insertNode(78);
    tree.insertNode(98);
    tree.insertNode(111);
    tree.insertNode(120);
    tree.insertNode(130);
    tree.insertNode(125);
    tree.insertNode(126);
    tree.insertNode(124);
    tree.showStructure();
    tree.remove(123);
    tree.remove(125);
    tree.remove(111);
    tree.remove(130);
    tree.remove(95);
    tree.showStructure();

    // VERSION B
    // Insert some nodes.
    cout << "Inserting nodes.\n";
    tree1.insertNode(100);
    tree1.insertNode(123);
    tree1.insertNode(98);
    tree1.insertNode(78);
    tree1.insertNode(95);
    tree1.insertNode(111);
    tree1.insertNode(130);
    tree1.insertNode(120);
    tree1.insertNode(124);
    tree1.insertNode(126);
    tree1.insertNode(125);
    tree1.showStructure();
    tree1.remove(123);
    tree1.remove(126);
    tree1.remove(111);
    tree1.remove(130);
    tree1.remove(98);
    tree1.showStructure();
    // Display inorder.
    cout << "Inorder traversal:\n";
    tree1.displayInOrder();

    // Display preorder.
    cout << "\nPreorder traversal:\n";
    tree1.displayPreOrder();

    // Display postorder.
    cout << "\nPostorder traversal:\n";
    tree1.displayPostOrder();
    return 0;

    */
}

