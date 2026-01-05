#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include "Patient.h"

class EmergencyQueue {
private:
    std::vector<Patient> heap;

    void bubbleUp(int idx);
    void bubbleDown(int idx);

public:
    EmergencyQueue();

    void push(const Patient& p);
    Patient pop();
    bool isEmpty() const;
    void displayQueue() const;
};

#endif // MINHEAP_H
