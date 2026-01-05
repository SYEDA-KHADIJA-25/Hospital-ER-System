#include "Resource.h"
#include <iostream>

// Default constructor
Resource::Resource() {
    id = 0;
    name = "";
    available = true; // default: free
}

// Parameterized constructor
Resource::Resource(int i, const std::string& n, bool avail) {
    id = i;
    name = n;
    available = avail;
}

// Optional helper: print info
void Resource::display() const {
    std::cout << "ID: " << id
              << " | Name: " << name
              << " | Status: " << (available ? "AVAILABLE" : "IN USE")
              << std::endl;
}

// Optional: toggle availability
void Resource::setAvailability(bool status) {
    available = status;
}
