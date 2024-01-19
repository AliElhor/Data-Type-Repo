/*======================================================================
Binary search tree object methods
**======================================================================*/

#include "binary-search-tree.h"
#include <iostream>
#include <queue>
#include <algorithm>


BinarySearchTree::Node::Node(DataType newval) {
    val = newval;
    left = nullptr;
    right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if(n == nullptr){
        return -9999;
    }
    else if(n->right == nullptr && n->left == nullptr){
        return 0;
    }
    else{
        return (1 + std::max(getNodeDepth(n->left), getNodeDepth(n->right)));
    }
}

BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree() {
    std::queue <Node*> Q;
    if(root_ == nullptr){
        std::cout << "Tree is empty" << std::endl;
        return;
    }
    Q.push(root_);
    while(!Q.empty()){
        Node *del = Q.front();
        if(del->left != nullptr){
            Q.push(del->left);
        }
        if(del->right != nullptr){
            Q.push(del->right);
        }
        Q.pop();
        delete del;
    }
}
j
unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    Node *max = root_;
    while(max->right != nullptr){
        max = max->right;
    }
    return max->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const {
    Node *min = root_;
    while(min->left != nullptr){
        min = min->left;
    }
    return min->val;
}

unsigned int BinarySearchTree::depth() const {
    unsigned int depth = getNodeDepth(root_);
    return depth;
}

void BinarySearchTree::print() const {
    if(root_ == nullptr){
        std::cout << "Tree is empty." << std::endl;
        return;
    }
    else{
        std::queue <Node*> Q;
        Q.push(root_);
        while(!Q.empty()){
            Node *node = Q.front();
            Q.pop();
            std::cout << node->val << ", ";
            if(node->left != nullptr){
                Q.push(node->left);
            }
            if(node->right != nullptr){
                Q.push(node->right);
            }
        }
        std::cout << std::endl;
    }
}

bool BinarySearchTree::exists(DataType val) const {
    Node *current = root_;
    while(current != nullptr){
        if(current->val == val){
            return true;
        }
        else if(val < current->val){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    return false;
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;

}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
    Node *insert = new Node(val);

    if(exists(val)){
        return false;
    }
    if(root_ == nullptr){
        root_ = insert;
        size_ = 1;
        return true;
    }

    Node *current = root_;
    Node *parent = nullptr;

    while(current != nullptr) {
        parent = current;
        if (val < current->val) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if(val < parent->val){
        parent->left = insert;
    }
    else{
        parent->right = insert;
    }
    size_++;
    return true;
}

bool BinarySearchTree::remove(DataType val) {
    if(!exists(val)){
        return false;
    }

    Node *removed = root_;
    Node *parent = nullptr;

    while(removed != nullptr && removed->val != val){
        parent = removed;
        if(val < removed->val){
            removed = removed->left;
        }
        else{
            removed = removed->right;
        }
    }

    //Case 1: Node has no children
    if(removed->right == nullptr && removed->left == nullptr){
        if(removed == root_){
            delete root_;
            root_ = nullptr;
        }
        else if(parent->left == removed){
            delete removed;
            parent->left = nullptr;
        }
        else{
            delete removed;
            parent->right = nullptr;
        }
    }

    //Case 2: Node has a left child, no right child
    else if(removed->left != nullptr && removed->right == nullptr){
        if(removed == root_){
            root_ = removed->left;
        }
        else if(parent->left == removed){
            parent->left = removed->left;
        }
        else{
            parent->right = removed->left;
        }
        delete removed;
    }

    //Case 3: Node has a right child, no left child
    else if(removed->right != nullptr && removed->left == nullptr){
        if(removed == root_){
            root_ = removed->right;
        }
        else if(parent->left == removed){
            parent->left = removed->right;
        }
        else{
            parent->right = removed->right;
        }
        delete removed;
    }

    //Case 4: Node has two children
    else if(removed->left != nullptr && removed->right != nullptr) {
        Node *predecessor = removed->left;
        Node *predecessor_parent = removed;

        while (predecessor->right != nullptr) {
            predecessor_parent = predecessor;
            predecessor = predecessor->right;
        }
        removed->val = predecessor->val;

        //predecessor has no left child
        if(predecessor->left == nullptr){
            if(predecessor == removed->left){
                removed->left = nullptr;
            }
            else{
                predecessor_parent->right = nullptr;
            }
        }
        //predecessor has a left child
        else{
            if(predecessor == removed->left){
                predecessor_parent->left = predecessor->left;
            }
            else{
                predecessor_parent->right = predecessor->left;
            }
        }
        delete predecessor;
        predecessor = nullptr;
        predecessor_parent = nullptr;
    }
    removed = nullptr;
    parent = nullptr;
    size_--;
    return true;
}
