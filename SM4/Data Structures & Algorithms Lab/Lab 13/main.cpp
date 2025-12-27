#include <iostream>
#include <cctype>
#include <string>
#include <queue>

using namespace std;

class TreeNode
{
public:
    char value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(char v) : value(v), left(nullptr), right(nullptr) {}
};

class ExpressionTree
{
private:
    void destroyTree(TreeNode *node)
    {
        if (node)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    TreeNode *root;
    ExpressionTree()
    {
        root = new TreeNode('*');
        root->left = new TreeNode('+');
        root->left->left = new TreeNode('5');
        root->left->right = new TreeNode('3');
        root->right = new TreeNode('-');
        root->right->left = new TreeNode('8');
        root->right->right = new TreeNode('2');
    }

    string getPrefix(TreeNode *node = nullptr)
    {
        if (node == nullptr)
        {
            return "";
        }
        string result = "";
        result += node->value;
        result += getPrefix(node->left);
        result += getPrefix(node->right);
        return result;
    }

    string getPostfix(TreeNode *node = nullptr)
    {

        if (node == nullptr)
        {
            return "";
        }
        string result = "";
        result += getPostfix(node->left);
        result += getPostfix(node->right);
        result += node->value;
        return result;
    }

    int evaluate(TreeNode *node = nullptr)
    {
        if (node == nullptr)
        {
            return 0;
        }

        if (isdigit(node->value))
        {
            return node->value - '0';
        }

        int leftValue = evaluate(node->left);
        int rightValue = evaluate(node->right);

        switch (node->value)
        {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            if (rightValue != 0)
            {
                return leftValue / rightValue;
            }
            else
            {
                cout << "Error: Division by zero!" << endl;
                return 0;
            }
        }
    }

    void findMaxValuesAtEachLevel()
    {
        if (root == nullptr)
        {
            return;
        }

        queue<TreeNode *> q;
        q.push(root);

        cout << "Maximum values at each level: ";
        while (!q.empty())
        {
            int level = q.size();
            int maxVal = 0;
            bool foundDigit = false;

            for (int i = 0; i < level; ++i)
            {
                TreeNode *current = q.front();
                q.pop();

                if (isdigit(current->value))
                {
                    int val = current->value - '0';
                    if (val > maxVal)
                    {
                        maxVal = val;
                    }
                    foundDigit = true;
                }
                if (current->left)
                {
                    q.push(current->left);
                }
                if (current->right)
                {
                    q.push(current->right);
                }
            }
            if (foundDigit != 0)
            {
                cout << maxVal << " ";
            }
            else
            {
                cout << "- ";
            }
        }
        cout << endl;
    }
    void countNodes(TreeNode *node, int &totalNodes, int &leafNodes, int &internalNodes)
    {
        if (node == nullptr)
        {
            return;
        }

        totalNodes++;

        if (node->left == nullptr && node->right == nullptr)
        {
            leafNodes++;
        }
        else
        {
            internalNodes++;
        }

        countNodes(node->left, totalNodes, leafNodes, internalNodes);
        countNodes(node->right, totalNodes, leafNodes, internalNodes);
    }
    void displayNodeCounts(TreeNode *root)
    {
        int totalNodes = 0;
        int leafNodes = 0;
        int internalNodes = 0;
        countNodes(root, totalNodes, leafNodes, internalNodes);

        cout << "Total number of nodes: " << totalNodes << endl;
        cout << "Total number of leaf nodes: " << leafNodes << endl;
        cout << "Total number of internal nodes: " << internalNodes << endl;
    }
    ~ExpressionTree()
    {
        destroyTree(root);
    }
};

int main()
{
    ExpressionTree tree;
    // Q1
    cout << "Prefix: " << tree.getPrefix(tree.root) << endl;
    cout << "Postfix: " << tree.getPostfix(tree.root) << endl;
    cout << "Evaluation Result: " << tree.evaluate(tree.root) << endl;

    // Q3
    tree.findMaxValuesAtEachLevel();

    // Q4

    tree.displayNodeCounts(tree.root);
    return 0;
}