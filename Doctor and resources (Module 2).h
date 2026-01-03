#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>

struct Doctor {
    int id;
    std::string name;
    std::string specialization;
    bool available;
};

#endif
