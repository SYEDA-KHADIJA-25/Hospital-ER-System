#include "PatientRecordBST.h"
#include <iostream>
#include <fstream>
#include <sstream>

PatientRecordBST::PatientRecordBST() {
    root = nullptr;
}

// -------- INSERT --------
RecordNode* PatientRecordBST::insertNode(RecordNode* node, Patient p) {
    if(node == nullptr) {
        RecordNode* newNode = new RecordNode{p, nullptr, nullptr};
        return newNode;
    }

    if(p.id < node->patient.id)
        node->left = insertNode(node->left, p);
    else
        node->right = insertNode(node->right, p);

    return node;
}

void PatientRecordBST::insert(Patient p) {
    root = insertNode(root, p);
}

// -------- SEARCH --------
RecordNode* PatientRecordBST::searchNode(RecordNode* node, int id) {
    if(node == nullptr || node->patient.id == id)
        return node;

    if(id < node->patient.id)
        return searchNode(node->left, id);
    else
        return searchNode(node->right, id);
}

Patient* PatientRecordBST::search(int id) {
    RecordNode* result = searchNode(root, id);
    if(result)
        return &result->patient;
    return nullptr;
}

// -------- DISPLAY --------
void PatientRecordBST::inorderDisplay(RecordNode* node) {
    if(node == nullptr) return;

    inorderDisplay(node->left);

    std::cout << "ID: " << node->patient.id
              << " | Name: " << node->patient.name
              << " | Age: " << node->patient.age
              << " | Priority: " << node->patient.priority << "\n";

    inorderDisplay(node->right);
}

void PatientRecordBST::displayAll() {
    std::cout << "\n=== Patient Records (BST Inorder) ===\n";
    inorderDisplay(root);
}

// -------- FILE SAVE --------
void PatientRecordBST::saveNodeToFile(RecordNode* node, std::ofstream& file) {
    if(node == nullptr) return;

    saveNodeToFile(node->left, file);

    file << node->patient.id << ","
         << node->patient.name << ","
         << node->patient.age << ","
         << node->patient.symptoms << ","
         << node->patient.priority << "\n";

    saveNodeToFile(node->right, file);
}

void PatientRecordBST::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    saveNodeToFile(root, file);
    file.close();
}

// -------- FILE LOAD --------
void PatientRecordBST::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if(!file) return;

    std::string line;
    while(getline(file, line)) {
        std::stringstream ss(line);
        std::string temp;
        Patient p;

        getline(ss, temp, ','); p.id = stoi(temp);
        getline(ss, p.name, ',');
        getline(ss, temp, ','); p.age = stoi(temp);
        getline(ss, p.symptoms, ',');
        getline(ss, temp); p.priority = stoi(temp);

        insert(p);
    }
    file.close();
}
