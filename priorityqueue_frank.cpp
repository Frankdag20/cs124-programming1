#include <cmath>
#include "priorityQueue.h"

int main() { return 0; }

PriorityQueue::PriorityQueue(unsigned int capacity) {
    capacity_ = capacity;
    size_ = 0;
    heap_ = new DataType[capacity + 1];
    for (int i = 0; i < capacity; ++i)
        heap_[i] = NULL;
}

PriorityQueue::~PriorityQueue() {
    delete[] heap_;
}

unsigned int PriorityQueue::size() const {
    return size_;
}

bool PriorityQueue::empty() const {
    return size_ == 0;
}

bool PriorityQueue::full() const {
    return size_ == capacity_;
}

bool PriorityQueue::add(DataType val) {
    if (full()) return false;
    heap_[++size_] = val;
    int new_index = size_;
    while (heap_[new_index] > heap_[new_index / 2] && new_index / 2 != 0) {
        DataType temp = heap_[new_index];
        heap_[new_index] = heap_[new_index / 2];
        heap_[new_index / 2] = temp;
        new_index = new_index / 2;
    }
    return true;
}

int PriorityQueue::deletemin() {
    if (empty()) return false;
    heap_[1] = heap_[size_];
    int min_el = heap_[size_];
    --size_;
    int i = 1;
    int larger;
    while (2 * i < size_ && (heap_[i] < heap_[2 * i] || heap_[i] < heap_[2 * i + 1])) {
        larger = (heap_[2 * i] > heap_[2 * i + 1]) ? 2 * i : 2 * i + 1;
        DataType temp = heap_[i];
        heap_[i] = heap_[larger];
        heap_[larger] = temp;
        i = larger;
    }
    return min_el;
}
