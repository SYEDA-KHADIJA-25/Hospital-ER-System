#ifndef ALLOCATIONQUEUE_H
#define ALLOCATIONQUEUE_H

#include "Patient.h"
#include "Doctor.h"
#include "Resource.h"
#include <string>

struct Node {
    Patient patient;
    Doctor doctor;
    Resource resource;
    Node* next;
};

class AllocationQueue {
private:
    Node* front;
    Node* rear;

public:
    AllocationQueue();

    void enqueue(Patient p, Doctor d, Resource r);
    void dequeue();
    bool isEmpty();
    void display();

    // File Management
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

#endif
