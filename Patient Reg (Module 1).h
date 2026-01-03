#ifndef PATIENT_H
#define PATIENT_H

#include <string>

struct Patient {
    int id;               // Unique patient ID
    std::string name;     // Patient name
    int age;              // Patient age
    int priority;         // 1=Critical, 2=Urgent, 3=Standard
    std::string symptoms; // Symptoms description
};

#endif
