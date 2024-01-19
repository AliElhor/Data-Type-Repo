/*======================================================================
Circular queue object methods
**======================================================================*/

#include "circular-queue.h"
#include <iostream>

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue() {
    capacity_ = 16;
    items_ = new QueueItem[capacity_];
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity) {
    capacity_ = capacity;
    items_ = new QueueItem[capacity_];
    size_ = 0;
    head_ = 0;
    tail_ = 0;
}

CircularQueue::~CircularQueue() {
    delete [] items_;
    items_ = nullptr;
}

unsigned int CircularQueue::size() const {
    return size_;

}

bool CircularQueue::empty() const {
    return (size_ == 0);
}

bool CircularQueue::full() const {
    return(size_ == capacity_);
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if(empty()){
        return EMPTY_QUEUE;
    }
    else{
        return items_[head_];
    }
}

bool CircularQueue::enqueue(QueueItem value) {
    if(full()){
        return false;
    }
    else{
        items_[tail_] = value;
        tail_++;
        size_++;
        if(tail_ == capacity_){
            tail_ = 0;
        }
        return true;
    }
}

CircularQueue::QueueItem CircularQueue::dequeue() {
    if(empty()){
        return EMPTY_QUEUE;
    }
    else{
        QueueItem dequeued = items_[head_];
        items_[head_] = EMPTY_QUEUE;
        head_++;
        size_--;
        if(head_ == capacity_){
            head_ = 0;
        }
        return dequeued;
    }
}

void CircularQueue::print() const {
    for(int i = 0; i < capacity_; i++){
        std::cout << items_[i] << std::endl;
    }

}
