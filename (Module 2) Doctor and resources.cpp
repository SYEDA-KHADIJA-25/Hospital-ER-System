#include "AllocationQueue.h"
#include <iostream>
#include <fstream>
#include <sstream>

AllocationQueue::AllocationQueue() {
    front = rear = nullptr;
}

bool AllocationQueue::isEmpty() {
    return front == nullptr;
}

void AllocationQueue::enqueue(Patient p, Doctor d, Resource r) {
    Node* newNode = new Node{p, d, r, nullptr};

    if(isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void AllocationQueue::dequeue() {
    if(isEmpty()) return;

    Node* temp = front;
    front = front->next;

    if(front == nullptr)
        rear = nullptr;

    delete temp;
}

void AllocationQueue::display() {
    std::cout << "\n=== Doctor & Resource Allocation ===\n";
    Node* temp = front;

    while(temp != nullptr) {
        std::cout << "Patient: " << temp->patient.name
                  << " | Doctor: " << temp->doctor.name
                  << " | Resource: " << temp->resource.name << "\n";
        temp = temp->next;
    }
}

// -------- File Management --------

void AllocationQueue::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    Node* temp = front;

    while(temp != nullptr) {
        file << temp->patient.id << ","
             << temp->patient.name << ","
             << temp->doctor.id << ","
             << temp->doctor.name << ","
             << temp->resource.id << ","
             << temp->resource.name << "\n";
        temp = temp->next;
    }
    file.close();
}

void AllocationQueue::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if(!file) return;

    std::string line;
    while(getline(file, line)) {
        std::stringstream ss(line);
        std::string temp;

        Patient p;
        Doctor d;
        Resource r;

        getline(ss, temp, ','); p.id = stoi(temp);
        getline(ss, p.name, ',');

        getline(ss, temp, ','); d.id = stoi(temp);
        getline(ss, d.name, ',');

        getline(ss, temp, ','); r.id = stoi(temp);
        getline(ss, r.name);

        enqueue(p, d, r);
    }
    file.close();
}
