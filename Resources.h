#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>

struct Resource {
    int id;
    std::string name;
    bool available;   // true = free , false = in use

    Resource(); // default
    Resource(int i, const std::string& n, bool avail=true);

    void display() const;
    void setAvailability(bool status);
};

#endif
