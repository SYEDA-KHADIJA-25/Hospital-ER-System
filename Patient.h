#ifndef PATIENT_H
#define PATIENT_H
#include <string>

struct Patient {
    int id;
    std::string name;
    int age;
    std::string symptoms;
    int priority;   // 1: Critical, 2: Urgent, 3: Normal

    Patient(int i, std::string n, int a, std::string s, int p)
        : id(i), name(n), age(a), symptoms(s), priority(p) {}

    Patient() : id(0), name(""), age(0), symptoms(""), priority(3) {}
};

#endif
