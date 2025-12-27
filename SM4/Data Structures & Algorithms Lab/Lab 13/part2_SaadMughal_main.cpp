#include <iostream>
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

    // ------- Q U E S T I O N  1 -----------
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
            return "";

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

    // ------- Q U E S T I O N  4 -----------
    void countNodes(TreeNode *ptr, int &totalCount, int &leafCount, int &internalCount)
    {
        if (ptr == nullptr)
            return;

        totalCount += 1;

        bool isLeaf = (ptr->left == nullptr && ptr->right == nullptr);
        if (isLeaf)
            leafCount += 1;
        else
            internalCount += 1;

        countNodes(ptr->left, totalCount, leafCount, internalCount);
        countNodes(ptr->right, totalCount, leafCount, internalCount);
    }

    void displayNodeCounts(TreeNode *root)
    {
        int total = 0, leaves = 0, internals = 0;
        countNodes(root, total, leaves, internals);

        std::cout << "Nodes count summary:\n";
        std::cout << "  Total nodes: " << total << "\n";
        std::cout << "  Leaf nodes: " << leaves << "\n";
        std::cout << "  Internal nodes: " << internals << std::endl;
    }

    // ------- Q U E S T I O N  3 -----------
    void findMaxValuesAtEachLevel()
    {
        if (root == nullptr)
            return;

        queue<TreeNode *> q;
        q.push(root);

        cout << "Maximum values at each level: ";

        while (!q.empty())
        {
            int levelSize = q.size();
            int maxVal = 0;
            bool digitFound = false;

            for (int i = 0; i < levelSize; i++)
            {
                TreeNode *node = q.front();
                q.pop();

                if (isdigit(node->value))
                {
                    int val = node->value - '0';
                    if (val > maxVal)
                        maxVal = val;
                    digitFound = true;
                }

                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }

            if (digitFound)
                cout << maxVal << " ";
            else
                cout << "- ";
        }

        cout << endl;
    }

    // destructor
    ~ExpressionTree()
    {
        destroyTree(root);
    }
};

int main()
{
    ExpressionTree tree;

    // ------- Q U E S T I O N  1 -----------
    cout << "Prefix: " << tree.getPrefix(tree.root) << endl;
    cout << "Postfix: " << tree.getPostfix(tree.root) << endl;
    cout << "Evaluation Result: " << tree.evaluate(tree.root) << endl;

    // ------- Q U E S T I O N  3 -----------
    tree.findMaxValuesAtEachLevel();

    // ------- Q U E S T I O N  4 -----------
    tree.displayNodeCounts(tree.root);

    return 0;
}