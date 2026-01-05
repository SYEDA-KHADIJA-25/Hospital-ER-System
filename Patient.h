#ifndef PATIENT_H
#define PATIENT_H

#include <string>

struct Patient {
    int id;
    std::string name;
    int age;
    std::string symptoms;
    int priority;

    Patient();  // default constructor
    Patient(int i, const std::string& n, int a,
            const std::string& s, int p);
};

#endif // PATIENT_H
