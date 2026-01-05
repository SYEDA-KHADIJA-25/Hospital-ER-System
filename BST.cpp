#include "BST.h"

// BSTNode constructor
BSTNode::BSTNode(Patient p)
    : data(p), left(nullptr), right(nullptr) {}

// PatientRecords constructor
PatientRecords::PatientRecords()
    : root(nullptr) {}

// Recursive insertion
BSTNode* PatientRecords::insertRecursive(BSTNode* node, const Patient& p) {
    if (!node)
        return new BSTNode(p);

    if (p.id < node->data.id)
        node->left = insertRecursive(node->left, p);
    else
        node->right = insertRecursive(node->right, p);

    return node;
}

// Add a patient record
void PatientRecords::addRecord(const Patient& p) {
    root = insertRecursive(root, p);
}

// Recursive search by ID
void PatientRecords::searchByIDRecursive(BSTNode* node, int id, bool& found) const {
    if (!node || found) return;

    if (node->data.id == id) {
        found = true;
        std::cout << "Patient found: " << node->data.name 
                  << ", Age: " << node->data.age 
                  << ", Symptoms: " << node->data.symptoms 
                  << ", Priority: " << node->data.priority << "\n";
        return;
    }

    searchByIDRecursive(node->left, id, found);
    searchByIDRecursive(node->right, id, found);
}

// Recursive search by Name
void PatientRecords::searchByNameRecursive(BSTNode* node, const std::string& name, bool& found) const {
    if (!node || found) return;

    if (node->data.name == name) {
        found = true;
        std::cout << "Patient found: ID " << node->data.id
                  << ", Age: " << node->data.age 
                  << ", Symptoms: " << node->data.symptoms 
                  << ", Priority: " << node->data.priority << "\n";
        return;
    }

    searchByNameRecursive(node->left, name, found);
    searchByNameRecursive(node->right, name, found);
}

// Public search by ID
void PatientRecords::searchByID(int id) const {
    bool found = false;
    searchByIDRecursive(root, id, found);
    if (!found) std::cout << "Patient with ID " << id << " not found.\n";
}

// Public search by Name
void PatientRecords::searchByName(const std::string& name) const {
    bool found = false;
    searchByNameRecursive(root, name, found);
    if (!found) std::cout << "Patient with Name " << name << " not found.\n";
}
