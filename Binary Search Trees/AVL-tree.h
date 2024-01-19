/*======================================================================
Header file for AVL tree
**======================================================================*/

#ifndef LAB3_AVL_TREE_H
#define LAB3_AVL_TREE_H

#include "binary-search-tree.h"

class AVLTree : public BinarySearchTree {
public:
    // Overridden insert and remove functions
    // Do not modify these definitions

    // The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);
    bool leftRotation(Node *alpha, Node *parent);
    bool rightRotation(Node *alpha, Node *parent);
    bool balance(DataType val);
    int getNodeDepth(Node* n);



    // Define additional functions and attributes below if you need
};

#endif  // LAB3_AVL_TREE_H
