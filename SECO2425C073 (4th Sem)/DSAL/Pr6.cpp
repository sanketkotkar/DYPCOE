#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = nullptr;
    }

    void create(int x) {
        root = new Node(x);
        cout << "Root node created with value " << x << endl;
    }

    void insertRecursive(int x) {
        if (root == nullptr) {
            create(x);
        } else {
            insertRecursive(x, root);
        }
    }

    void insertRecursive(int x, Node* node) {
        if (x < node->data) {
            if (node->left == nullptr) {
                node->left = new Node(x);
                cout << "Value " << x << " inserted to the left of " << node->data << endl;
            } else {
                insertRecursive(x, node->left);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new Node(x);
                cout << "Value " << x << " inserted to the right of " << node->data << endl;
            } else {
                insertRecursive(x, node->right);
            }
        }
    }

    void insertIterative(int x) {
        Node* newNode = new Node(x);
        if (root == nullptr) {
            create(x);
            return;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (x < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (x < parent->data) {
            parent->left = newNode;
            cout << "Value " << x << " inserted to the left of " << parent->data << endl;
        } else {
            parent->right = newNode;
            cout << "Value " << x << " inserted to the right of " << parent->data << endl;
        }
    }

    bool searchRecursive(int x) {
        cout << "Searching path for value " << x << ":" << endl;
        return searchRecursive(x, root);
    }

    bool searchRecursive(int x, Node* node) {
        if (node == nullptr) {
            cout << "Element not found." << endl;
            return false;
        }
        cout << "[" << node->data << "] -> ";
        if (x == node->data) {
            cout << "Element Found!" << endl;
            return true;
        }
        if (x < node->data) {
            cout << "Smaller, going to left subtree." << endl;
            return searchRecursive(x, node->left);
        } else {
            cout << "Greater, going to right subtree." << endl;
            return searchRecursive(x, node->right);
        }
    }

    bool searchIterative(int x) {
        Node* current = root;
        cout << "Searching path for value " << x << ":" << endl;

        while (current != nullptr) {
            cout << "[" << current->data << "] -> ";
            if (x == current->data) {
                cout << "Element Found!" << endl;
                return true;
            }
            if (x < current->data) {
                cout << "Smaller, going to left subtree." << endl;
                current = current->left;
            } else {
                cout << "Greater, going to right subtree." << endl;
                current = current->right;
            }
        }
        cout << "Element not found." << endl;
        return false;
    }

    int findHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = findHeight(node->left);
        int rightHeight = findHeight(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    int findMinValue(Node* node) {
        if (node == nullptr) {
            cout << "Tree is empty." << endl;
            return -1;
        }
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current->data;
    }

    void mirrorTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        swap(node->left, node->right);
        mirrorTree(node->left);
        mirrorTree(node->right);
    }

    void mirror() {
        mirrorTree(root);
        cout << "Tree structure mirrored successfully." << endl;
    }
};

int main() {
    BST tree;
    int ch, value;

    do {
        cout << "-------------Binary Search Tree-------------" << endl;
        cout << "1. Insert a Node (Recursion)" << endl;
        cout << "2. Insert a Node (Loop)" << endl;
        cout << "3. Search a Node (Recursion)" << endl;
        cout << "4. Search a Node (Loop)" << endl;
        cout << "5. Find Number of Nodes in Longest Path (Tree Height)" << endl;
        cout << "6. Find Minimum Data Value in the Tree" << endl;
        cout << "7. Mirror the Tree Structure" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insertRecursive(value);
                break;
            case 2:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insertIterative(value);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (!tree.searchRecursive(value)) {
                    cout << value << " not found in the tree." << endl;
                }
                break;
            case 4:
                cout << "Enter value to search: ";
                cin >> value;
                if (!tree.searchIterative(value)) {
                    cout << value << " not found in the tree." << endl;
                }
                break;
            case 5:
                cout << "Longest path from root (Tree Height): " << tree.findHeight(tree.root) << endl;
                break;
            case 6:
                cout << "Minimum data value in the tree: " << tree.findMinValue(tree.root) << endl;
                break;
            case 7:
                tree.mirror();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (ch != 8);

    return 0;
}
