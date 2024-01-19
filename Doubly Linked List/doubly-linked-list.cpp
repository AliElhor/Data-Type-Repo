/*======================================================================
Doubly linked list object methods
**======================================================================*/

#include "doubly-linked-list.h"

DoublyLinkedList::Node::Node(DataType data) {
    value = data;
    next = nullptr;
    prev = nullptr;
}


DoublyLinkedList::DoublyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}


DoublyLinkedList::~DoublyLinkedList() {
   int i = 0;
   Node *current = head_;
   while(i < size_){
       Node *temp = current;
       current = current->next;
       delete temp;
       temp = nullptr;
   }
}


unsigned int DoublyLinkedList::size() const {
    return size_;
}


unsigned int DoublyLinkedList::capacity() const {
    return CAPACITY;
}


bool DoublyLinkedList::empty() const {
    return size_ == 0;
}


bool DoublyLinkedList::full() const {
    return size_ == CAPACITY;
}


DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {
    if(index > size_ - 1){
        return tail_->value;
    }
    else{
        Node *current = getNode(index);
        return current->value;
    }
}


unsigned int DoublyLinkedList::search(DataType value) const {
    int index = 0;
    Node *current = head_;
    while(index < size_){
        if(current->value == value){
            return index;
        }
        current = current->next;
        index++;
    }
    return size_;
}


void DoublyLinkedList::print() const {
    if(size_ == 0){
        std::cout << "List is empty.";
        return;
    }
    Node *current = head_;
    for(int i = 0; i < size_; i++){
        if(current->next == nullptr){
            std::cout << current->value << std::endl;
            break;
        }
        std::cout << current->value << "->";
        current = current->next;
    }
}


DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const {
    int i = 0;
    Node *current = head_;
    while(i < index){
        current = current->next;
        i++;
    }
    return current;
}


bool DoublyLinkedList::insert(DataType value, unsigned int index) {
    if(full() || index > size_){
        return false;
    }

    if(index == 0){
        insert_front(value);
        return true;
    }

    else if(index == size_){
        insert_back(value);
        return true;
    }

    else{
        Node* newNode = new Node(value);
        Node *after = getNode(index);
        Node *previous = after->prev;
        previous->next = after;
        newNode->prev = previous;
        newNode->next = after;
        previous->next = newNode;
        after->prev = newNode;
        size_++;
        return true;
    }
}


bool DoublyLinkedList::insert_front(DataType value) {
    if(full()){
        return false;
    }

    Node *newNode = new Node(value);
    if(empty()){
        head_ = newNode;
        tail_ = newNode;
        size_ = 1;
        return true;
    }

    else{
        newNode->next = head_;
        head_->prev = newNode;
        head_ = newNode;
        size_++;
        return true;
    }
}


bool DoublyLinkedList::insert_back(DataType value) {
    if(full()){
        return false;
    }

    Node *newNode = new Node(value);
    if(empty()){
        head_ = newNode;
        tail_ = newNode;
        size_ = 1;
        return true;
    }

    else{
        tail_->next = newNode;
        newNode->prev = tail_;
        tail_ = newNode;
        size_++;
        return true;
    }

}


bool DoublyLinkedList::remove(unsigned int index) {
    if(index > size_ - 1 || empty()){
        return false;
    }

    else if(index == 0){
        remove_front();
        return true;
    }

    else if(index == size_ - 1){
        remove_back();
        return true;
    }

    else if(size_ == 1){
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
        return true;
    }

    else{
        Node *remove = getNode(index);
        Node *previous = remove->prev;
        previous->next = remove;
        Node *after = remove->next;
        after->prev = remove;
        previous->next = after;
        after->prev = previous;
        delete remove;
        remove = nullptr;
        size_--;
        return true;
    }
}


bool DoublyLinkedList::remove_front() {
    if(empty()){
        return false;
    }
    else if(size_ == 1){
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
        return true;
    }
    else{
        Node *remove = head_;
        head_ = head_->next;
        delete remove;
        remove = nullptr;
        size_--;
        return true;
    }
}


bool DoublyLinkedList::remove_back() {
    if(empty()){
        return false;
    }
    else if(size_ == 1){
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
        return true;
    }
    else{
        Node *remove = tail_;
        tail_ = tail_->prev;
        delete remove;
        remove = nullptr;
        tail_->next = nullptr;
        size_--;
        return true;
    }

}


bool DoublyLinkedList::replace(unsigned int index, DataType value) {
    if(empty() || index > size_ - 1){
        return false;
    }
    Node *replaced = getNode(index);
    replaced->value = value;
    return true;
}
