#include "Patient.h"

Patient::Patient()
    : id(0), name(""), age(0), symptoms(""), priority(3) {}

Patient::Patient(int i, const std::string& n, int a,
                 const std::string& s, int p)
    : id(i), name(n), age(a), symptoms(s), priority(p) {}
