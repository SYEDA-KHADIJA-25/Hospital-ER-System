#ifndef MINHEAP_H
#define MINHEAP_H

#include "Patient Reg (Module 1).h"
#include <vector>
#include <string>

class MinHeap {
private:
    std::vector<Patient> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    // Core operations
    void insert(Patient p);
    Patient extractMin();
    void display();

    // File Management
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

#endif
