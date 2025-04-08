#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

struct Book {
    string title;
    string author;
    string isbn;
    string genre;

    // Default constructor
    Book() : title(""), author(""), isbn(""), genre("") {}

    // Parameterized constructor
    Book(string t, string a, string i, string g) : title(t), author(a), isbn(i), genre(g) {}
};

// AVL Tree Node
struct AVLNode {
    Book book;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Book b) : book(b), left(nullptr), right(nullptr), height(1) {}
};

// AVL Tree Class
class AVLTree {
public:
    AVLNode* root;

    AVLTree() : root(nullptr) {}

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLNode* insert(AVLNode* node, Book book) {
        if (!node) return new AVLNode(book);

        if (book.title < node->book.title)
            node->left = insert(node->left, book);
        else if (book.title > node->book.title)
            node->right = insert(node->right, book);
        else
            return node; // Duplicate titles are not allowed

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // Balancing the tree
        if (balance > 1 && book.title < node->left->book.title)
            return rightRotate(node);
        if (balance < -1 && book.title > node->right->book.title)
            return leftRotate(node);
        if (balance > 1 && book.title > node->left->book.title) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && book.title < node->right->book.title) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    AVLNode* remove(AVLNode* root, string title) {
        if (!root) return root;

        if (title < root->book.title)
            root->left = remove(root->left, title);
        else if (title > root->book.title)
            root->right = remove(root->right, title);
        else {
            if (!root->left || !root->right) {
                AVLNode* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp; // Copy the contents of the non-empty child
                delete temp;
            } else {
                AVLNode* temp = minValueNode(root->right);
                root->book = temp->book;
                root->right = remove(root->right, temp->book.title);
            }
        }

        if (!root) return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        // Balancing the tree
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void inOrder(AVLNode* node) {
        if (node) {
            inOrder(node->left);
            cout << "-----------------------------------\n";
            cout << "Title: " << node->book.title << "\nAuthor: " << node->book.author << "\nISBN: " << node->book.isbn << "\nGenre: " << node->book.genre << endl;
            cout << "-----------------------------------\n";
            inOrder(node->right);
        }
    }

    void display() {
        inOrder(root);
    }

    void removeBook(string title) {
        root = remove(root, title);
    }
};

// Hash Table Class
class HashTable {
private:
    unordered_map<string, Book> table;

public:
    void insert(string isbn, Book book) {
        table[isbn] = book;
    }

    Book* search(string isbn) {
        if (table.find(isbn) != table.end())
            return &table[isbn];
        return nullptr;
    }

    void remove(string isbn) {
        table.erase(isbn);
    }
};

// Main Function
int main() {
    AVLTree avlTree;
    HashTable hashTable;
    vector<Book> allBooks;

    int choice;
    do {
        cout << "\n===================================\n";
        cout << "       Library Management System    \n";
        cout << "===================================\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book by ISBN\n";
        cout << "3. Display All Books\n";
        cout << "4. Remove Book\n";
        cout << "5. List Books by Genre\n";
        cout << "6. Exit\n";
        cout << "-----------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, author, isbn, genre;
                cout << "\nEnter book details:\n";
                cout << "Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Author: ";
                getline(cin, author);
                cout << "ISBN: ";
                getline(cin, isbn);
                cout << "Genre: ";
                getline(cin, genre);

                Book newBook(title, author, isbn, genre);
                avlTree.root = avlTree.insert(avlTree.root, newBook);
                hashTable.insert(isbn, newBook);
                allBooks.push_back(newBook);
                cout << "\nBook added successfully!\n";
                break;
            }
            case 2: {
                string isbn;
                cout << "\nEnter ISBN to search: ";
                cin.ignore();
                getline(cin, isbn);
                Book* book = hashTable.search(isbn);
                if (book) {
                    cout << "-----------------------------------\n";
                    cout << "Found Book - Title: " << book->title << ", Author: " << book->author << ", Genre: " << book->genre << endl;
                    cout << "-----------------------------------\n";
                } else {
                    cout << "Book not found.\n";
                }
                break;
            }
            case 3: {
                cout << "\nAll Books:\n";
                avlTree.display();
                break;
            }
            case 4: {
                string title;
                cout << "\nEnter title of the book to remove: ";
                cin.ignore();
                getline(cin, title);
                avlTree.removeBook(title);
                hashTable.remove(title); // Remove from hash table as well
                cout << "\nBook removed successfully!\n";
                break;
            }
            case 5: {
                string genre;
                cout << "\nEnter genre to list books: ";
                cin.ignore();
                getline(cin, genre);
                cout << "Books in genre '" << genre << "':\n";
                for (const auto& book : allBooks) {
                    if (book.genre == genre) {
                        cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.isbn << endl;
                    }
                }
                break;
            }
            case 6:
                cout << "\nExiting the system. Thank you!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
