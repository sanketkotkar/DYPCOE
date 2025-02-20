#include <iostream>
#include <cstring>
#include <cctype>  // Required for isalpha()

using namespace std;

struct TreeNode {
    char data;
    TreeNode *left, *right;
};

class ExpressionTree {
    char expressionInput[20];  // Not used in this implementation

public:
    TreeNode *root;
    
    ExpressionTree() { root = nullptr; }
    
    void buildTreeFromPrefix(char[]);
    void postOrderTraversal(TreeNode *);
    void deleteTree(TreeNode *);
};

class Stack {
    TreeNode *stackData[30];
    int topIndex;

public:
    Stack() { topIndex = -1; }

    bool isEmpty() { return topIndex == -1; }

    void push(TreeNode *node) { stackData[++topIndex] = node; }

    TreeNode *pop() { return isEmpty() ? nullptr : stackData[topIndex--]; }
};

void ExpressionTree::buildTreeFromPrefix(char prefixExpr[]) {
    Stack stack;
    int length = strlen(prefixExpr);

    cout << "\nConstructing Expression Tree Step-by-Step:\n";

    for (int i = length - 1; i >= 0; i--) {
        TreeNode *node = new TreeNode;
        node->left = node->right = nullptr;
        node->data = prefixExpr[i];

        if (isalpha(prefixExpr[i])) {  // Operand
            stack.push(node);
            cout << "Inserted operand node: " << prefixExpr[i] << endl;
        } else if (prefixExpr[i] == '+' || prefixExpr[i] == '-' ||
                   prefixExpr[i] == '*' || prefixExpr[i] == '/') {  // Operator
            if (!stack.isEmpty()) node->left = stack.pop();
            if (!stack.isEmpty()) node->right = stack.pop();

            stack.push(node);
            cout << "Created operator node '" << prefixExpr[i] << "' with left child '"
                 << (node->left ? node->left->data : ' ') << "' and right child '"
                 << (node->right ? node->right->data : ' ') << "'\n";
        }
    }

    root = stack.pop();
    cout << "Expression Tree Constructed Successfully\n";
}

void ExpressionTree::postOrderTraversal(TreeNode *root) {
    if (!root) return;

    Stack stack1, stack2;
    stack1.push(root);

    cout << "\nPostorder Traversal: ";

    while (!stack1.isEmpty()) {
        TreeNode *currentNode = stack1.pop();
        stack2.push(currentNode);

        if (currentNode->left) stack1.push(currentNode->left);
        if (currentNode->right) stack1.push(currentNode->right);
    }

    while (!stack2.isEmpty()) {
        cout << stack2.pop()->data << " ";
    }

    cout << endl;
}

void ExpressionTree::deleteTree(TreeNode *node) {
    if (node == nullptr) return;

    deleteTree(node->left);
    deleteTree(node->right);

    cout << "Deleting Node: " << node->data << endl;
    delete node;
}

int main() {
    char prefixExpression[20];

    ExpressionTree expressionTree;

    cout << "Enter Prefix Expression: ";
    cin >> prefixExpression;

    expressionTree.buildTreeFromPrefix(prefixExpression);
    expressionTree.postOrderTraversal(expressionTree.root);
    expressionTree.deleteTree(expressionTree.root);

    return 0;
}
