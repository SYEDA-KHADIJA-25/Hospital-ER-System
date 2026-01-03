#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

struct Resource {
    int id;
    std::string name;      // e.g. ICU Bed, Ventilator
    bool available;        // 1 = available, 0 = in use
};

#endif
