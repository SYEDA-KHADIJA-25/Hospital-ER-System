#ifndef PATIENT_RECORD_BST_H
#define PATIENT_RECORD_BST_H

#include "Patient Reg (Module 1).h"
#include <string>

struct RecordNode {
    Patient patient;
    RecordNode* left;
    RecordNode* right;
};

class PatientRecordBST {
private:
    RecordNode* root;

    RecordNode* insertNode(RecordNode* node, Patient p);
    RecordNode* searchNode(RecordNode* node, int id);
    void inorderDisplay(RecordNode* node);
    void saveNodeToFile(RecordNode* node, std::ofstream& file);

public:
    PatientRecordBST();

    void insert(Patient p);
    Patient* search(int id);
    void displayAll();

    // File Management
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

#endif
