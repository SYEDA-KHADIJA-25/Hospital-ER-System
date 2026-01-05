#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <iostream>

struct Doctor {
    int id;
    std::string name;
    std::string specialization;
    bool available; // true = free , false = busy

    Doctor(); // default
    Doctor(int i, const std::string& n, const std::string& s, bool avail=true);

    void display() const;
    void setAvailability(bool status);
};

#endif
