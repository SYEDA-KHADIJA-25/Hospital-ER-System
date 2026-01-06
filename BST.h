#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include "Patient.h"

struct BSTNode {
    Patient data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Patient p);
};

class PatientRecords {
private:
    BSTNode* root;

    BSTNode* insertRecursive(BSTNode* node, const Patient& p);
    void searchByIDRecursive(BSTNode* node, int id, bool& found) const;
    void searchByNameRecursive(BSTNode* node, const std::string& name, bool& found) const;

public:
    PatientRecords();

    void addRecord(const Patient& p);
    void searchByID(int id) const;
    void searchByName(const std::string& name) const;
};

#endif // BST_H
