#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include "Patient.h"

struct RecordNode {
    Patient data;
    RecordNode *left, *right;
    RecordNode(Patient p) : data(p), left(NULL), right(NULL) {}
};

class PatientRecordBST {
private:
    RecordNode* root;

    RecordNode* insert(RecordNode* node, Patient p) {
        if (!node)
            return new RecordNode(p);

        if (p.id < node->data.id)
            node->left = insert(node->left, p);
        else if (p.id > node->data.id)
            node->right = insert(node->right, p);
        else
            std::cout << "  [!] Duplicate Patient ID not allowed\n";

        return node;
    }

    void searchByNameRec(RecordNode* node, std::string name, bool &found) {
        if (!node) return;

        searchByNameRec(node->left, name, found);

        if (node->data.name == name) {
            std::cout << "  [Found] ID: " << node->data.id
                      << " | Age: " << node->data.age
                      << " | Issue: " << node->data.symptoms << "\n";
            found = true;
        }

        searchByNameRec(node->right, name, found);
    }

    void deleteTree(RecordNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    PatientRecordBST() : root(NULL) {}

    ~PatientRecordBST() {
        deleteTree(root);
    }

    void addRecord(Patient p) {
        root = insert(root, p);
    }

    void searchByID(int id) {
        RecordNode* curr = root;
        while (curr) {
            if (curr->data.id == id) {
                std::cout << "  Record Found: "
                          << curr->data.name
                          << " | Issue: "
                          << curr->data.symptoms << "\n";
                return;
            }
            curr = (id < curr->data.id) ? curr->left : curr->right;
        }
        std::cout << "  [!] ID not found\n";
    }

    void searchByName(std::string name) {
        bool found = false;
        searchByNameRec(root, name, found);
        if (!found)
            std::cout << "  [!] Name not found\n";
    }
};

#endif
