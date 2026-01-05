#include "PatientModule.h"
#include <algorithm>

// =======================
// Patient Constructors
// =======================
Patient::Patient()
    : id(0), name(""), age(0), symptoms(""), priority(3) {}

Patient::Patient(int i, const std::string& n, int a,
                 const std::string& s, int p)
    : id(i), name(n), age(a), symptoms(s), priority(p) {}


// =======================
// Emergency Queue (Min Heap)
// =======================
void EmergencyQueue::bubbleUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent].priority <= heap[idx].priority)
            break;
        std::swap(heap[parent], heap[idx]);
        idx = parent;
    }
}

void EmergencyQueue::bubbleDown(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap.size() &&
        heap[left].priority < heap[smallest].priority)
        smallest = left;

    if (right < heap.size() &&
        heap[right].priority < heap[smallest].priority)
        smallest = right;

    if (smallest != idx) {
        std::swap(heap[idx], heap[smallest]);
        bubbleDown(smallest);
    }
}

void EmergencyQueue::push(const Patient& p) {
    heap.push_back(p);
    bubbleUp(heap.size() - 1);
}

Patient EmergencyQueue::pop() {
    if (heap.empty())
        return Patient();

    Patient top = heap[0];
    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty())
        bubbleDown(0);

    return top;
}

bool EmergencyQueue::isEmpty() const {
    return heap.empty();
}

void EmergencyQueue::displayQueue() const {
    if (heap.empty()) {
        std::cout << "Queue is empty.\n";
        return;
    }

    for (const auto& p : heap) {
        std::cout << "[P" << p.priority << "] "
                  << p.id << " - " << p.name << "\n";
    }
}


// =======================
// BST Patient Records
// =======================
BSTNode::BSTNode(const Patient& p)
    : data(p), left(nullptr), right(nullptr) {}

PatientRecords::PatientRecords()
    : root(nullptr) {}

BSTNode* PatientRecords::insertRecursive(BSTNode* node,
                                         const Patient& p) {
    if (!node)
        return new BSTNode(p);

    if (p.id < node->data.id)
        node->left = insertRecursive(node->left, p);
    else if (p.id > node->data.id)
        node->right = insertRecursive(node->right, p);
    else
        std::cout << "Duplicate Patient ID: " << p.id << "\n";

    return node;
}

void PatientRecords::addRecord(const Patient& p) {
    root = insertRecursive(root, p);
}

BSTNode* PatientRecords::searchByIDRecursive(BSTNode* node,
                                             int id) const {
    if (!node || node->data.id == id)
        return node;

    if (id < node->data.id)
        return searchByIDRecursive(node->left, id);

    return searchByIDRecursive(node->right, id);
}

void PatientRecords::searchByID(int id) const {
    BSTNode* result = searchByIDRecursive(root, id);

    if (result) {
        std::cout << "Patient Found: "
                  << result->data.name
                  << " | Issue: "
                  << result->data.symptoms << "\n";
    } else {
        std::cout << "Patient ID not found.\n";
    }
}

void PatientRecords::searchByNameRecursive(BSTNode* node,
                                           const std::string& name,
                                           bool& found) const {
    if (!node) return;

    searchByNameRecursive(node->left, name, found);

    if (node->data.name == name) {
        std::cout << "Match: ID "
                  << node->data.id
                  << " | Issue: "
                  << node->data.symptoms << "\n";
        found = true;
    }

    searchByNameRecursive(node->right, name, found);
}

void PatientRecords::searchByName(const std::string& name) const {
    bool found = false;
    searchByNameRecursive(root, name, found);

    if (!found)
        std::cout << "No patient found with name: "
                  << name << "\n";
}
