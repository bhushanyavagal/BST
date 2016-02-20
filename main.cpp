/* 
 * File:   main.cpp
 * Author: Bhushan
 *
 * Created on February 3, 2016, 10:58 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <math.h>
#include <stdio.h>

using namespace std;

class BSTnode {
    friend class BST;
    int data;
    BSTnode *parent;
    BSTnode *right;
    BSTnode *left;
public:

    BSTnode() {
        data = -1;
        parent = NULL;
        right = NULL;
        left = NULL;
    }

    void SetData(int value) {
        data = value;
    };

    void SetParent(BSTnode* par) {
        parent = par;
    };

    void SetRchild(BSTnode* rchild) {
        right = rchild;
    };

    void SetLchild(BSTnode* lchild) {
        left = lchild;
    };
};

class BST {
    BSTnode * root;
    void printPostorder(BSTnode* node, int indent);
    void insert(BSTnode* node, int key);
    void search(BSTnode* node, int key);
    void rdelete(BSTnode* node, int key);
    int findMin(BSTnode* node);
public:

    BST() {
        root = NULL;
    }
    void printBST();
    void insertBST(int key);
    void searchBST(int key);
    void deleteBST(int key);
};

void BST::insertBST(int key) {

    if (root == NULL) {
        BSTnode* rootnode = new BSTnode();
        rootnode->SetData(key);
        root = rootnode;
    } else
        insert(root, key);
}

void BST::searchBST(int key) {

    if (root == NULL)
        cout << "\nsearchBST: The tree is empty!" << endl;
    else
        search(root, key);
}

void BST::deleteBST(int key) {

    if (root == NULL)
        cout << "\ndeleteBST: The tree is empty!" << endl;
    else
        rdelete(root, key);
}

void BST::printBST() {

    if (root == NULL)
        cout << "\nprint: The tree is empty!" << endl;

    else {
        printPostorder(root, 0);
    }
}

void BST::printPostorder(BSTnode* node, int indent) {
    if (node != NULL) {
        if (node->right) {
            printPostorder(node->right, indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (node->right) std::cout << " /\n" << std::setw(indent) << ' ';
        std::cout << node->data << "\n ";
        if (node->left) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            printPostorder(node->left, indent + 4);
        }
    }

}

void BST::insert(BSTnode* node, int key) {
    if (key < node->data) {
        if (node->left == NULL) {
            BSTnode* newnode = new BSTnode();
            newnode->SetData(key);
            node->left = newnode;
            newnode->parent = node;
        } else
            insert(node->left, key);
    } else {
        if (node->right == NULL) {
            BSTnode* newnode = new BSTnode();
            newnode->SetData(key);
            node->right = newnode;
            newnode->parent = node;
        } else
            insert(node->right, key);
    }
}

void BST::search(BSTnode* node, int key) {
    if (key < node->data) {
        if (node->left == NULL)
            cout << "\nsearch: Key " << key << " not found in Tree!" << endl;
        else
            search(node->left, key);
    } else if (key > node->data) {
        if (node->right == NULL)
            cout << "\nsearch: Key " << key << " not found in Tree!" << endl;
        else
            search(node->right, key);
    } else //key found
        cout << "\nsearch: Key " << key << " is present in Tree!" << endl;

}

int BST::findMin(BSTnode* node) {

    if (node->left == NULL)
        return node->data;
    else
        return findMin(node->left);
}

void BST::rdelete(BSTnode* node, int key) {
    if (key < node->data) {
        if (node->left == NULL)
            cout << "\ndelete: Key " << key << " not found in Tree!" << endl;
        else
            rdelete(node->left, key);
    } else if (key > node->data) {
        if (node->right == NULL)
            cout << "\ndelete: Key " << key << " not found in Tree!" << endl;
        else
            rdelete(node->right, key);
    } else {//key found
        if (node->right == NULL && node->left == NULL) { // key node is a leaf
            if (node->parent == NULL) { //node to be deleted is root
                delete node;
                root = NULL;
            } else {

                BSTnode* parentnode = node->parent;
                if (parentnode->data > node->data)
                    parentnode->left = NULL;
                else
                    parentnode->right = NULL;
                delete node;
                cout << "\ndelete: Key deleted from Tree!" << endl;
            }
        } else if (node->right == NULL) { // key node with no right sub tree
            BSTnode* parentnode = node->parent;
            BSTnode* newchildnode = node->left;
            if (parentnode->data > node->data)
                parentnode->left = newchildnode;
            else
                parentnode->right = newchildnode;
            delete node;
            newchildnode->parent = parentnode;
            cout << "\ndelete: Key deleted from Tree!" << endl;
        } else if (node->left == NULL) { // key node with no left sub tree
            BSTnode* parentnode = node->parent;
            BSTnode* newchildnode = node->right;
            if (parentnode->data > node->data)
                parentnode->left = newchildnode;
            else
                parentnode->right = newchildnode;
            delete node;
            newchildnode->parent = parentnode;
            cout << "\ndelete: Key deleted from Tree!" << endl;
        } else { //keynode has both sub trees
            BSTnode* rightnode = node->right;
            int min = findMin(rightnode);
            node->data = min;
            rdelete(rightnode, min);
        }

    }

}

/*
 * 
 */

int main(int argc, char** argv) {

    BST bst;
    int choice = 0, key;
    while (choice != 5) {
        cout << "\n ----Binary Search Tree---- " << endl;
        cout << "1. Insert " << endl;
        cout << "2. Search " << endl;
        cout << "3. Delete " << endl;
        cout << "4. Print " << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin>>choice;
        switch (choice) {
            case 1:
                cout << "\nEnter key to insert: ";
                cin>>key;
                bst.insertBST(key);
                break;
            case 2:
                cout << "\nEnter key to search: ";
                cin>>key;
                bst.searchBST(key);
                break;
            case 3:
                cout << "\nEnter key to delete: ";
                cin>>key;
                bst.deleteBST(key);
                break;
            case 4:
                cout << "\n\n";
                bst.printBST();
                break;
            case 5:
                break;
            default:
                cout << "\nWrong choice, try again!" << endl;
        }
    }


    return 0;
}

