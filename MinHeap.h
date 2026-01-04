#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "Patient.h"

class EmergencyQueue {
private:
    std::vector<Patient> heap;

    void bubbleUp(int idx) {
        while (idx > 0 && heap[idx].priority < heap[(idx - 1) / 2].priority) {
            std::swap(heap[idx], heap[(idx - 1) / 2]);
            idx = (idx - 1) / 2;
        }
    }

    void bubbleDown(int idx) {
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

public:
    void push(Patient p) {
        heap.push_back(p);
        bubbleUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) {
            std::cout << "  Queue is empty\n";
            return;
        }

        Patient top = heap[0];
        std::cout << "  Treating Patient: "
                  << top.name << " (Priority " << top.priority << ")\n";

        heap[0] = heap.back();
        heap.pop_back();
        bubbleDown(0);
    }

    void displayQueue() {
        if (heap.empty()) {
            std::cout << "  Queue is empty\n";
            return;
        }

        for (auto &p : heap)
            std::cout << "  [P" << p.priority << "] "
                      << p.id << " - " << p.name << "\n";
    }
};

#endif
