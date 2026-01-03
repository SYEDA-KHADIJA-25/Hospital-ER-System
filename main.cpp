#include <iostream>
#include "Patient.h"
#include "MinHeap.h"
#include "MedicalRecords.h"
#include "Doctor.h"

int main() {

    // ==============================
    // MODULE OBJECTS
    // ==============================

    MinHeap emergencyQueue;          // Module 1: Priority Queue
    MedicalRecords patientRecords;   // Module 3: BST + File I/O
    DoctorQueue doctorQueue;         // Module 2: Doctors

    int nextPatientID = 1;

    // ==============================
    // LOAD DATA FROM FILES
    // ==============================

    patientRecords.loadFromFile("patients.csv");
    emergencyQueue.loadFromFile("queue.csv");      // simple heap load
    doctorQueue.loadFromFile("doctors.csv");       // doctor list load

    std::cout << "Data loaded successfully.\n";

    // ==============================
    // SIMPLE DEMO FLOW (TEMP)
    // ==============================

    Patient p;
    p.id = nextPatientID++;
    p.name = "Ali";
    p.age = 45;
    p.symptoms = "Heart Attack";
    p.priority = 1;

    emergencyQueue.insert(p);
    patientRecords.addRecord(p);

    // Assign doctor (optional module)
    doctorQueue.assignPatient(&p);

    // ==============================
    // DISPLAY (FOR TESTING)
    // ==============================

    emergencyQueue.display();
    patientRecords.displayAll();
    doctorQueue.showDoctors();

    // ==============================
    // SAVE DATA TO FILES
    // ==============================

    patientRecords.saveToFile("patients.csv");
    emergencyQueue.saveToFile("queue.csv");
    doctorQueue.saveToFile("doctors.csv");

    std::cout << "Data saved. Program exiting...\n";

    return 0;
}
