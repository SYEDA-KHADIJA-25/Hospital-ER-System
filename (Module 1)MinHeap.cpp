#include "MinHeap.h"
#include <iostream>
#include <fstream>
#include <sstream>

// ---------- Heap Logic ----------

void MinHeap::heapifyUp(int index) {
    if(index == 0) return;

    int parent = (index - 1) / 2;
    if(heap[index].priority < heap[parent].priority) {
        std::swap(heap[index], heap[parent]);
        heapifyUp(parent);
    }
}

void MinHeap::heapifyDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if(left < heap.size() && heap[left].priority < heap[smallest].priority)
        smallest = left;

    if(right < heap.size() && heap[right].priority < heap[smallest].priority)
        smallest = right;

    if(smallest != index) {
        std::swap(heap[index], heap[smallest]);
        heapifyDown(smallest);
    }
}

void MinHeap::insert(Patient p) {
    heap.push_back(p);
    heapifyUp(heap.size() - 1);
}

Patient MinHeap::extractMin() {
    if(heap.empty())
        return Patient{-1, "", 0, 3, ""};

    Patient top = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return top;
}

void MinHeap::display() {
    std::cout << "\n=== Emergency Queue ===\n";
    for(auto &p : heap) {
        std::cout << "ID: " << p.id
                  << " | Name: " << p.name
                  << " | Priority: " << p.priority
                  << " | Symptoms: " << p.symptoms << "\n";
    }
}

// ---------- File Management ----------

void MinHeap::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if(!file) return;

    for(auto &p : heap) {
        file << p.id << ","
             << p.name << ","
             << p.age << ","
             << p.priority << ","
             << p.symptoms << "\n";
    }
    file.close();
}

void MinHeap::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if(!file) return;

    heap.clear();
    std::string line;

    while(getline(file, line)) {
        std::stringstream ss(line);
        Patient p;
        std::string temp;

        getline(ss, temp, ','); p.id = stoi(temp);
        getline(ss, p.name, ',');
        getline(ss, temp, ','); p.age = stoi(temp);
        getline(ss, temp, ','); p.priority = stoi(temp);
        getline(ss, p.symptoms);

        heap.push_back(p);
    }
    file.close();
}

