#include "Doctor.h" 

// Default constructor
Doctor::Doctor() {
    id = 0;
    name = "";
    specialization = "";
    available = true; // default: free
}

// Parameterized constructor
Doctor::Doctor(int i, const std::string& n, const std::string& s, bool avail) {
    id = i;
    name = n;
    specialization = s;
    available = avail;
}

// Optional helper: print info
void Doctor::display() const {
    std::cout << "ID: " << id 
              << " | Name: " << name
              << " | Specialization: " << specialization
              << " | Status: " << (available ? "AVAILABLE" : "BUSY")
              << std::endl;
}

// Optional: toggle availability
void Doctor::setAvailability(bool status) {
    available = status;
}
