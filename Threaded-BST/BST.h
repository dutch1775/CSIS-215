// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"

#ifndef BST_H
#define BST_H

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
private:

    BSTNode<Key, E>* root;      // Root of the BST
    int nodecount;              // Number of nodes in the BST

    // Private "helper" functions
    void clearhelp(BSTNode<Key, E>*);
    void inserthelp(BSTNode<Key, E>*, const Key&, const E&);
    BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
    BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
    BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
    E* findhelp(BSTNode<Key, E>*, const Key&) const;
    void vist(BSTNode<Key, E>*) const;

    //modified printHelp
    void printhelp(BSTNode<Key, E>*, int) const;

    //finds next node for inorder traversal
    BSTNode<Key, E>* findNextInorderNode(BSTNode<Key, E>* current) const;

    //finds next node for reverse traversal
    BSTNode<Key, E>* findNextReverseNode(BSTNode<Key, E>* current) const;

public:

    //contructor
    BST()
    {
        root = new BSTNode<Key, E>();       //make empty dummy node
        root->setLeftThread(true);          //left pointer is thread
        root->setRightThread(false);        //right pointer not thread
        root->setLeft(root);                //lc to itself
        root->setRight(root);               //rc to itself
    }

    //Note from Prof Sipantzi -- I've commented out the destructor
    //since you would have to change clearhelp() to make it work with
    //doubly-threaded trees and that is not part of the assignment.
    //~BST() { clearhelp(root); }    // Destructor

    // Reinitialize tree
    void clear()
    {
        clearhelp(root); root = NULL; nodecount = 0;
    }

    // Insert a record into the tree.
    // k Key value of the record.
    // e The record to insert.
    void insert(const Key& k, const E& e) {
        inserthelp(root, k, e);
        nodecount++;
    }

    // Remove a record from the tree.
    // k Key value of record to remove.
    // Return: The record removed, or NULL if there is none.
    E* remove(const Key& k)
    {
        E* temp = findhelp(root, k);   // First find it
        if (temp != NULL)
        {
            root = removehelp(root, k);
            nodecount--;
        }
        return temp;
    }

    // Remove and return the root node from the dictionary.
    // Return: The record removed, null if tree is empty.
    E* removeAny()
    {  // Delete min value
        if (root != NULL)
        {
            E* temp = new E;
            *temp = root->element();
            root = removehelp(root, root->key());
            nodecount--;
            return temp;
        }
        else return NULL;
    }

    // Return Record with key value k, NULL if none exist.
    // k: The key value to find. */
    // Return some record matching "k".
    // Return true if such exists, false otherwise. If
    // multiple records match "k", return an arbitrary one.
    E* find(const Key& k) const
    {
        return findhelp(root, k);
    }

    // Return the number of records in the dictionary.
    int size()
    {
        return nodecount;
    }

    // Print the contents of the BST
    void print() const
    {
        //if lc is root and rc is root then dummy node and empty BST
        if (root->left() == root && root->right() == root)
        {
            cout << "The BST is empty.\n";
        }
        else
        {
            printhelp(root->left(), 0);     //print BST
        }
    }

    void printInorder()
    {
        //if lc is root and rc is root then dummy node and empty BST
        if (root->left() == root && root->right() == root)
        {
            cout << "The BST is empty.\n";
        }
        else
        {
            BSTNode<Key, E>* current = root->left(); //dynamic node for actual first node

            //while  not a thread
            while (current->getLeftThread() == false)
            {
                current = current->left();  //traverse the left
            }

            //keep traversing while not root
            while (current != root)
            {
                std::cout << current->element() << std::endl;   //print element
                current = findNextInorderNode(current);         //find next node
            }
        }
    }

    void printReverse()
    {
        //if lc is root and rc is root then dummy node and empty BST
        if (root->left() == root && root->right() == root)
        {
            cout << "The BST is empty.\n";
        }
        else
        {
            BSTNode<Key, E>* current = root->left();    //actual first node in tree

            //while right is not a thread
            while (current->getRightThread() == false)
            {
                current = current->right(); //traverse right
            }

            //keep taversing while not root
            while (current != root)
            {
                std::cout << current->element() << std::endl;   //print element
                current = findNextReverseNode(current);         //find next reverse
            }
        }
    }
};

//--PRIVATE FUNCTION IMPLEMENTATIONS-----------------
//
// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key, E>* r) const
{
    cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::clearhelp(BSTNode<Key, E>* root)
{
    if (root == NULL) return;
    clearhelp(root->left());
    clearhelp(root->right());
    delete root;
}

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
void BST<Key, E>::inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it)
{
    //new node to hold insertion values
    BSTNode<Key, E>* node = new BSTNode<Key, E>(k, it, NULL, NULL);

    //if lc is root and rc is root then dummy node
    if (root->left() == root && root->right() == root)
    {
        node->setLeft(root);            //set lc to dummy node
        root->setLeft(node);            //root lc is node
        node->setLeftThread(true);      //lc is thread
        node->setRightThread(true);     //rc is thread
        node->setRight(root);           //rc to root
        root->setLeftThread(false);     //root lc is pointer
    }
    else //if non-empty tree
    {
        //curr starts as first acutal node
        BSTNode<Key, E>* current = root->left();

        while (true) //loop until found position
        {
            //if insert value is less than current
            if (k < current->key())
            {
                //if lc is thread
                if (current->getLeftThread() == true)
                {
                    node->setLeft(current->left());     //node lc is current lc
                    current->setLeft(node);             //current lc is node
                    node->setLeftThread(true);          //node lc is thread
                    current->setLeftThread(false);      //current lc is thread
                    node->setRight(current);            //node rc is to current
                    node->setRightThread(true);         //rc is a thread
                    break;                              //break loop
                }
                else
                {
                    //if not thread then keep traversing
                    current = current->left();
                }
            }
            else //if insert value is greater than current value
            {
                //if current rc is thread
                if (current->getRightThread() == true)
                {
                    node->setRight(current->right());   //node rc is current rc
                    current->setRight(node);            //current rc is node
                    node->setRightThread(true);         //node rc is thread
                    current->setRightThread(false);     //current rc is not thread
                    node->setLeft(current);             //node lc is current
                    node->setLeftThread(true);          //node lc is thread
                    break;                              //break loop
                }
                else //if not thread
                {
                    //keep traversing right
                    current = current->right();
                }
            }
        }
    }
}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::getmin(BSTNode<Key, E>* rt)
{
    if (rt->left() == NULL)
        return rt;
    else return getmin(rt->left());
}

template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::deletemin(BSTNode<Key, E>* rt)
{
    if (rt->left() == NULL) // Found min
        return rt->right();
    else
    {                      // Continue left
        rt->setLeft(deletemin(rt->left()));
        return rt;
    }
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::removehelp(BSTNode<Key, E>* rt, const Key& k)
{
    if (rt == NULL) return NULL;    // k is not in tree
    else if (k < rt->key())
        rt->setLeft(removehelp(rt->left(), k));
    else if (k > rt->key())
        rt->setRight(removehelp(rt->right(), k));
    else      // Found: remove it
    {
        BSTNode<Key, E>* temp = rt;
        if (rt->left() == NULL)       // Only a right child
        {
            rt = rt->right();         //  so point to right
            delete temp;
        }
        else if (rt->right() == NULL) // Only a left child
        {
            rt = rt->left();          //  so point to left
            delete temp;
        }
        else // Both children are non-empty
        {
            BSTNode<Key, E>* temp = getmin(rt->right());
            rt->setElement(temp->element());
            rt->setKey(temp->key());
            rt->setRight(deletemin(rt->right()));
            delete temp;
        }
    }
    return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root, const Key& k) const
{
    if (root == NULL) return NULL;          // Empty tree
    if (k < root->key())
        return findhelp(root->left(), k);   // Check left
    else if (k > root->key())
        return findhelp(root->right(), k);  // Check right
    else {
        E* temp = new E;
        *temp = root->element();
        return temp;  // Found it
    }
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* root, int level) const
{
    //if lc is root and rc is root then dummy node
    if (root->left() == root && root->right() == root)
    {
        return;
    }

    //is lc is not thread
    if (root->getLeftThread() == false)
    {
        printhelp(root->left(), level + 1);     //print left subtree
    }

    //print spaces for level
    for (int i = 0; i < level; i++)
    {
        cout << "  ";
    }
    cout << root->key() << "\n";                //print node key

    //is rc is not thread
    if (root->getRightThread() == false)
    {
        printhelp(root->right(), level + 1);    //print right subtree
    }
}

// Get the inorder successor
template<typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::findNextInorderNode(BSTNode<Key, E>* current) const
{
    //if rc is thread
    if (current->getRightThread() == true)
    {
        return current->right();    //return rc
    }
    else
    {
        current = current->right(); //current is rc

        while (current->getLeftThread() == false)   //while lc is not a thrad
        {
            current = current->left();              //traverse left
        }
        return current;                             //return next node
    }
}

template<typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::findNextReverseNode(BSTNode<Key, E>* current) const
{
    //if lc is thread
    if (current->getLeftThread() == true)
    {
        return current->left();    //return lc
    }
    else
    {
        current = current->left(); //current is lc

        while (current->getRightThread() == false)   //while rc is not a thrad
        {
            current = current->right();              //traverse right
        }
        return current;                             //return reverse node
    }
}


#endif