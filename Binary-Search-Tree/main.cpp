//
//  main.cpp
//  Binary-Search-Tree
//
//  Created by Desislava Stoyanova on 10/23/15.
//  Copyright © 2015 Desislava Stoyanova. All rights reserved.
//

#include <iostream>
#include <cassert>

using namespace std;

struct Tree {
    int key;
    Tree* left;
    Tree* right;
    ~Tree() {
//        cout << endl << "Node with key " << key << " has been removed." << endl;
    }
};

// Deallocate the memory we have used for storing the tree 't'
void dealloc(Tree*& t) {
    if (t) {
        dealloc(t->left);
        dealloc(t->right);
        delete t;
    }
}

// Points to the node with the lowest key in 't'
Tree* minimum(Tree* t) {
    Tree* x = t;
    while (x->left) {
        x = x->left;
    }
    return x;
}

// Insert a new node with key 'k' into the tree 't'
void insert(Tree*& t,int k) {
    if (!t) {
        t = new Tree;
        assert(t);
        t->key = k;
        t->left = NULL;
        t->right = NULL;
    }
    else if (k < t->key) {
        insert(t->left, k);
    }
    else {
        insert(t->right, k);
    }
}

// Print the nodes' values in ascending order
void inorderwalk(Tree* t) {
    if (t) {
        inorderwalk(t->left);
        cout << t->key << " ";
        inorderwalk(t->right);
    }
}

// Remove node having key 'k' from the tree 't'
void remove(Tree*& t,int k) {
    Tree* x = t;
    Tree* parent = NULL;
    while (x->key != k) {
        parent = x;
        if (k < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    if (x == t) {
        t = NULL;
        delete x;
    }
    else if (x->left == NULL && x->right == NULL) {
        if (parent->left->key == k) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        delete x;
    }
    else if (x->left == NULL && x->right != NULL) {
        if (parent->left->key == k) {
            parent->left = x->right;
        }
        else {
            parent->right = x->right;
        }
        delete x;
    }
    else if (x->left != NULL && x->right == NULL) {
        if (parent->left->key == k) {
            parent->left = x->left;
        }
        else {
            parent->right = x->left;
        }
        delete x;
    }
    else {
        Tree* succ = minimum(x->right);
        x->key = succ->key;
        remove(x->right,succ->key);
    }
}

void test1() {
    Tree* t = NULL;
    insert(t, 10);
    insert(t, 3);
    insert(t, 5);
    insert(t, 1);
    inorderwalk(t);
    dealloc(t);
}

void test2() {
    Tree* t = NULL;
    insert(t, 2);
    insert(t, 6);
    insert(t, 7);
    insert(t, 4);
    insert(t, 1);
    cout << "\nBefore deletion: ";
    inorderwalk(t);
    remove(t,6);
    cout << "\nAfter deletion: ";
    inorderwalk(t);
    dealloc(t);
}

void test3() {
    Tree* t = NULL;
    insert(t, 1);
    cout << "\nBefore deletion: ";
    inorderwalk(t);
    remove(t,1);
    cout << "\nAfter deletion: ";
    inorderwalk(t);
    dealloc(t);
}

int main(int argc, const char * argv[]) {
    test1();
    test2();
    test3();
    cout << endl;
    return 0;
}
