#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "Missing the <filesystem> header"
#endif

using namespace std;

void traverse(const fs::path& path) {
    if (!fs::exists(path)) return;

    fs::path leftPath = path / "left";
    fs::path rightPath = path / "right";

    if (fs::exists(leftPath) || fs::exists(rightPath)) {
        if (fs::exists(leftPath))
            traverse(leftPath);
        if (fs::exists(rightPath))
            traverse(rightPath);
    }
    else {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.path().extension() == ".txt") {
                cout << "Found: " << entry.path() << endl;

                ifstream file(entry.path());
                if (!file.is_open()) {
                    cerr << "Failed to open: " << entry.path() << endl;
                    continue;
                }

                char ch;
                cout << "Alphabets: ";
                while (file.get(ch)) {  // Use get() instead of >> to read all characters including whitespace
                    if (isalpha(ch)) cout << ch;
                }
                cout << endl;

                file.close();
            }
        }
    }
}

struct TreeNode {
    string data;           // Letters from .txt file
    TreeNode* left;
    TreeNode* right;

    TreeNode(string val = "") : data(val), left(nullptr), right(nullptr) {}
};

TreeNode* buildTreeFromFolder(const fs::path& folderPath) {
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) return nullptr;

    fs::path leftPath = folderPath / "left";
    fs::path rightPath = folderPath / "right";

    string letters = "";

    // Read all .txt files in the current folder (both leaf and internal nodes)
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".txt") {
            ifstream file(entry.path());
            if (file.is_open()) {
                char ch;
                while (file.get(ch)) {  // Use get() to read all characters
                    if (isalpha(ch)) {
                        letters += ch;
                    }
                }
                file.close();
            }
        }
    }

    TreeNode* node = new TreeNode(letters);

    // Build left and right subtrees
    if (fs::exists(leftPath))
        node->left = buildTreeFromFolder(leftPath);
    if (fs::exists(rightPath))
        node->right = buildTreeFromFolder(rightPath);

    return node;
}

void preorder(TreeNode* node, string& result) {
    if (node == nullptr) return;

    result += node->data;
    preorder(node->left, result);
    preorder(node->right, result);
}

void inorder(TreeNode* node, string& result) {
    if (node == nullptr) return;

    inorder(node->left, result);
    result += node->data;
    inorder(node->right, result);
}

void postorder(TreeNode* node, string& result) {
    if (node == nullptr) return;

    postorder(node->left, result);
    postorder(node->right, result);
    result += node->data;
}

int height(TreeNode* node) {
    if (!node) return 0;
    return 1 + max(height(node->left), height(node->right));
}

// Recursive breadth-first helper function
void breadthFirstLevel(TreeNode* node, int level, string& result) {
    if (node == nullptr) return;

    if (level == 1) {
        result += node->data;
    }
    else if (level > 1) {
        breadthFirstLevel(node->left, level - 1, result);
        breadthFirstLevel(node->right, level - 1, result);
    }
}

void breadthFirst(TreeNode* root, string& result) {
    if (!root) return;

    int h = height(root);
    for (int i = 1; i <= h; i++) {
        breadthFirstLevel(root, i, result);
    }
}

int countTextFiles(const fs::path& folderPath) {
    int count = 0;

    if (!fs::exists(folderPath)) return 0;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (fs::is_directory(entry.path())) {
            count += countTextFiles(entry.path());
        }
        else if (entry.path().extension() == ".txt") {
            count++;
        }
    }

    return count;
}

bool isBalanced(TreeNode* node) {
    if (!node) return true;

    int lh = height(node->left);
    int rh = height(node->right);

    if (abs(lh - rh) > 1) return false;

    return isBalanced(node->left) && isBalanced(node->right);
}

// Debug function to print tree structure
void printTree(TreeNode* node, int depth = 0) {
    if (!node) return;

    for (int i = 0; i < depth; i++) cout << "  ";
    cout << "Node: '" << node->data << "'" << endl;

    if (node->left || node->right) {
        if (node->left) {
            for (int i = 0; i < depth; i++) cout << "  ";
            cout << "Left:" << endl;
            printTree(node->left, depth + 1);
        }
        if (node->right) {
            for (int i = 0; i < depth; i++) cout << "  ";
            cout << "Right:" << endl;
            printTree(node->right, depth + 1);
        }
    }
}

int main() {
    fs::path rootFolder = "charTree";
    TreeNode* root = buildTreeFromFolder(rootFolder);

    if (root != nullptr) {
        cout << "Tree built successfully!" << endl;
        cout << "Root node data: " << root->data << endl;
    }
    else {
        cout << "Tree build failed." << endl;
        return 1;
    }

    string preorderResult = "";
    preorder(root, preorderResult);

    cout << "Preorder Traversal: " << preorderResult << endl;

    string inorderResult = "";
    inorder(root, inorderResult);

    cout << "Inorder Traversal: " << inorderResult << endl;

    string postorderResult = "";
    postorder(root, postorderResult);

    cout << "Postorder Traversal: " << postorderResult << endl;

    string bfsResult = "";
    breadthFirst(root, bfsResult);

    cout << "Breadth-First Traversal: " << bfsResult << endl;

    int treeHeight = height(root);
    cout << "Height of Tree: " << treeHeight << endl;

    int txtFileCount = countTextFiles(rootFolder);
    cout << "Total .txt files in charTree: " << txtFileCount << endl;

    bool balanced = isBalanced(root);
    cout << "Tree is Balanced? " << (balanced ? "Yes" : "No") << endl;

    ofstream out("Output.txt");
    if (out.is_open()) {
        out << "Preorder: " << preorderResult << "\n";
        out << "Inorder: " << inorderResult << "\n";
        out << "Postorder: " << postorderResult << "\n";
        out << "Breadth-First: " << bfsResult << "\n";
        out << "Height: " << treeHeight << "\n";
        out << "Total .txt files: " << txtFileCount << "\n";
        out << "Balanced: " << (balanced ? "Yes" : "No") << "\n";
        out.close();
        cout << "Output written to Output.txt\n";
    }
    else {
        cout << "Failed to write to Output.txt\n";
    }

    return 0;
}