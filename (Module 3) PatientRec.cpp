#ifndef MEDICAL_RECORDS_H
#define MEDICAL_RECORDS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// =====================
// Patient Class
// =====================
class Patient {
public:
    int id;
    string name;
    int age;
    int priority;
    vector<string> medicalHistory;

    Patient();
    Patient(int id, string name, int age, int priority);

    void addHistory(const string& record);
    bool isValid() const;
};

// =====================
// BST Node
// =====================
struct RecordNode {
    Patient data;
    RecordNode* left;
    RecordNode* right;

    RecordNode(const Patient& p);
};

// =====================
// Medical Records (BST)
// =====================
class MedicalRecords {
private:
    RecordNode* root;

    RecordNode* insertRecord(RecordNode* node, const Patient& p);
    RecordNode* searchRecord(RecordNode* node, int id);
    void inorderDisplay(RecordNode* node);
    void saveInorder(RecordNode* node, ofstream& file);

public:
    MedicalRecords();

    void addPatient(const Patient& p);
    void addMedicalHistory(int patientID, const string& record);
    void searchByID(int id);
    void displayAll();

    // File Handling
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
};

#endif
