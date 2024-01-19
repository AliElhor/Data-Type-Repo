/*======================================================================
Dynamic stack object methods
**======================================================================*/

#include "dynamic-stack.h"
#include <iostream>
const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack() {
    size_ = 0;
    init_capacity_ = 16;
    capacity_ = init_capacity_;
    items_ = new StackItem[capacity_];

}

DynamicStack::DynamicStack(unsigned int capacity){
    capacity_ = capacity;
    init_capacity_ = capacity;
    items_ = new StackItem[capacity];
    size_ = 0;
}

DynamicStack::~DynamicStack() {
    delete[] items_;
    items_ = nullptr;
}

unsigned int DynamicStack::size() const {
    return size_;
}

bool DynamicStack::empty() const {
    return (size_ == 0);
}

DynamicStack::StackItem DynamicStack::peek() const {
    if(empty()){
        return EMPTY_STACK;
    }
    else{
        return items_[size_ - 1];
    }
}

void DynamicStack::push(StackItem value) {
    if(size_ == capacity_){
        std::cout << "Stack capacity has been reached. Doubling capacity." << std::endl;
        StackItem *copy = new StackItem[2*capacity_];
        capacity_ *= 2;
        for(int i = 0; i < size_; i++){
            copy[i] = items_[i];
        }
        StackItem *remove = items_;
        items_ = copy;
        delete [] remove;
        remove = nullptr;
        copy = nullptr;
    }
    items_[size_] = value;
    size_++;
    return;
}

DynamicStack::StackItem DynamicStack::pop() {
    if(empty()){
        return EMPTY_STACK;
    }
    else{
        StackItem popped= items_[size_ - 1];
        items_[size_ - 1] = EMPTY_STACK;
        size_--;
        if(size_ <= (capacity_/4) && (capacity_/2) >= init_capacity_){
            std::cout << "Stack capacity is being halved." << std::endl;
            capacity_ = capacity_/2;
            StackItem *copy = new StackItem[capacity_];
            for(int i = 0; i < size_; i++){
                copy[i] = items_[i];
            }
            StackItem *remove = items_;
            items_ = copy;
            delete [] remove;
            remove = nullptr;
            copy = nullptr;
            return popped;
        }

    }
}

void DynamicStack::print() const {
    for(int i = 0; i < size_; i++){
        std::cout << items_[i] << std::endl;
    }
    return;
}
