#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include "Contact.h"

using namespace std;

// Node for the AVL Tree
struct AVLNode {
    Contact data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(Contact c) : data(c), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;
    
    int getHeight(AVLNode* N) { return N ? N->height : 0; }
    int getMax(int a, int b) { return (a > b) ? a : b; }
    
    // Check if the left and right branches are uneven
    int getBalance(AVLNode* N) { return N ? getHeight(N->left) - getHeight(N->right) : 0; }
    
    // Rotate right to fix a heavy left side
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        // Update heights after moving nodes around
        y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }
    
    // Rotate left to fix a heavy right side
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }
    
    // Recursive function to insert a contact alphabetically
    AVLNode* insertNode(AVLNode* node, Contact c) {
        // Normal BST insertion
        if (!node) return new AVLNode(c);
        if (c.name < node->data.name) node->left = insertNode(node->left, c);
        else if (c.name > node->data.name) node->right = insertNode(node->right, c);
        else return node; // No exact duplicates allowed

        // Update height and check if tree became unbalanced
        node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Balance the tree using the 4 possible rotation cases
        if (balance > 1 && c.name < node->left->data.name) return rightRotate(node);
        if (balance < -1 && c.name > node->right->data.name) return leftRotate(node);
        if (balance > 1 && c.name > node->left->data.name) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && c.name < node->right->data.name) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    
    // Print contacts from A to Z
    void inOrder(AVLNode* root) {
        if (root) {
            inOrder(root->left);
            cout << root->data.name << " | " << root->data.phone << "\n";
            inOrder(root->right);
        }
    }
    
    // Clean up memory when the program closes
    void destroyTree(AVLNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroyTree(root); }
    
    void insert(Contact c) { root = insertNode(root, c); }
    void display() { inOrder(root); }
};
#endif
