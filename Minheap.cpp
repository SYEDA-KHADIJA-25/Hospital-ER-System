#include "MinHeap.h"
#include <iostream>
#include <algorithm>

EmergencyQueue::EmergencyQueue() {}

// Move element up to maintain min-heap
void EmergencyQueue::bubbleUp(int idx) {
    while (idx > 0 && heap[idx].priority < heap[(idx - 1) / 2].priority) {
        std::swap(heap[idx], heap[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

// Move element down to maintain min-heap
void EmergencyQueue::bubbleDown(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap.size() && heap[left].priority < heap[smallest].priority)
        smallest = left;

    if (right < heap.size() && heap[right].priority < heap[smallest].priority)
        smallest = right;

    if (smallest != idx) {
        std::swap(heap[idx], heap[smallest]);
        bubbleDown(smallest);
    }
}

// Insert patient into queue
void EmergencyQueue::push(const Patient& p) {
    heap.push_back(p);
    bubbleUp(heap.size() - 1);
}

// Remove highest priority patient
Patient EmergencyQueue::pop() {
    if (heap.empty())
        return Patient();

    Patient top = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty())
        bubbleDown(0);

    return top;
}

// Check if empty
bool EmergencyQueue::isEmpty() const {
    return heap.empty();
}

// Display queue contents
void EmergencyQueue::displayQueue() const {
    if (heap.empty()) {
        std::cout << "Queue is empty.\n";
        return;
    }

    for (const auto& p : heap) {
        std::cout << "[P" << p.priority << "] ID: "
                  << p.id << " - " << p.name << "\n";
    }
}
