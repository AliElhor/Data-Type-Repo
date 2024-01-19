/*======================================================================
AVL tree object methods
**======================================================================*/

#include "avl-tree.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>

bool AVLTree::insert(DataType val){
    BinarySearchTree::insert(val);
    balance(val);
    return true;
}

bool AVLTree::remove(DataType val){
    BinarySearchTree::remove(val);
    balance(val);
    return true;
}

bool AVLTree::leftRotation(Node *alpha, Node *parent){
    Node *A = nullptr;
    if(getNodeDepth(alpha->left) > getNodeDepth(alpha->right)){
        A = alpha->left;
    }
    else{
        A = alpha->right;
    }

    alpha->right = A->left;
    A->left = alpha;

    if(parent == nullptr){
        root_ = A;
        return true;
    }

    if(parent->left == alpha){
        parent->left = A;
    }
    else{
        parent->right = A;
    }
    return true;
}

bool AVLTree::rightRotation(Node *alpha, Node *parent){
    Node *A = nullptr;
    if(getNodeDepth(alpha->left) > getNodeDepth(alpha->right)){
        A = alpha->left;
    }
    else{
        A = alpha->right;
    }

    alpha->left = A->right;
    A->right = alpha;

    if(parent == nullptr){
        root_ = A;
        return true;
    }
    if(parent->left == alpha){
        parent->left = A;
    }
    else{
        parent->right = A;
    }
    return true;
}

bool AVLTree::balance(DataType val){
    Node *parent = nullptr;
    Node *alpha = nullptr;
    Node *A = nullptr;
    Node *B = nullptr;

    Node *curr = root_;
    Node *prev = nullptr;

    while(curr != nullptr){
        if(abs(getNodeDepth(curr->left) - getNodeDepth(curr->right)) == 2){
            alpha = curr;
            parent = prev;
        }

        prev = curr;

        if(val > curr->val){
            curr = curr->right;
        }
        else{
            curr = curr->left;
        }
    }

    //tree is already balanced
    if(alpha == nullptr){
        return true;
    }

    if(getNodeDepth(alpha->left) > getNodeDepth(alpha->right)){
        A = alpha->left;
    }
    else{
        A = alpha->right;
    }

    if(getNodeDepth(A->left) > getNodeDepth(A->right)){
        B = A->left;
    }
    else{
        B = A->right;
    }

    //single-left rotation
    if(B->val > alpha->val && B->val > A->val){
        leftRotation(alpha, parent);
    }

    //single-right rotation
    else if(B->val < alpha->val && B->val < A->val){
        rightRotation(alpha, parent);
    }

    //left-right rotation
    else if(B->val < alpha->val && B->val > A->val){
        leftRotation(A, alpha);
        rightRotation(alpha, parent);
    }

    //right-left rotation
    else{
        rightRotation(A, alpha);
        leftRotation(alpha, parent);
    }

    return true;
}


int AVLTree::getNodeDepth(Node* n) {
    if(n == nullptr){
        return 0;
    }
    else if(n->right == nullptr && n->left == nullptr){
        return 1;
    }
    else{
        return (1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right)));
    }
}