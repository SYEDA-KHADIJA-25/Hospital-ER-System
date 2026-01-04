#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h> 

struct 	Patient {
    int id;
    std::string name;
    int age;
    int priority; // 1: Critical, 2: Urgent, 3: Standard
    std::string symptoms;
};

// --- AVL Tree Logic for Permanent Records ---
struct AVLNode {
    Patient data;
    AVLNode *left, *right;
    int height;
    AVLNode(Patient p) : data(p), left(NULL), right(NULL), height(1) {}
};

class PatientAVL {
private:
    AVLNode* root;

    int getHeight(AVLNode* n) { return n ? n->height : 0; }
    int getBalance(AVLNode* n) { return n ? getHeight(n->left) - getHeight(n->right) : 0; }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    AVLNode* insert(AVLNode* node, Patient p) {
        if (!node) return new AVLNode(p);
        if (p.id < node->data.id) node->left = insert(node->left, p);
        else if (p.id > node->data.id) node->right = insert(node->right, p);
        else return node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && p.id < node->left->data.id) return rightRotate(node);
        if (balance < -1 && p.id > node->right->data.id) return leftRotate(node);
        if (balance > 1 && p.id > node->left->data.id) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && p.id < node->right->data.id) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void inOrder(AVLNode* node) {
        if (!node) return;
        inOrder(node->left);
        std::cout << "ID: " << node->data.id << " | Name: " << node->data.name 
                  << " | Age: " << node->data.age << " | Symptoms: " << node->data.symptoms << "\n";
        inOrder(node->right);
    }

    void search(AVLNode* node, int id) {
        if (!node) { std::cout << "\nPatient ID " << id << " not found.\n"; return; }
        if (node->data.id == id) {
            std::cout << "\n--- Record Found ---\nID: " << node->data.id << "\nName: " << node->data.name 
                      << "\nAge: " << node->data.age << "\nSymptoms: " << node->data.symptoms << "\n";
            return;
        }
        if (id < node->data.id) search(node->left, id);
        else search(node->right, id);
    }

public:
    PatientAVL() : root(NULL) {}
    void addRecord(Patient p) { root = insert(root, p); }
    void displayAll() { if(!root) std::cout << "No records found.\n"; else inOrder(root); }
    void find(int id) { search(root, id); }

    // Load data from record file into AVL tree at startup
    void loadFromFile(const std::string& filename, int &maxId) {
        std::ifstream file(filename.c_str());
        if(!file) return;
        std::string line;
        while(std::getline(file, line)) {
            if(line.empty()) continue;
            std::stringstream ss(line);
            Patient p; std::string tId, tAge, tPri;
            std::getline(ss, tId, ','); std::getline(ss, p.name, ',');
            std::getline(ss, tAge, ','); std::getline(ss, tPri, ',');
            std::getline(ss, p.symptoms);
            p.id = atoi(tId.c_str()); p.age = atoi(tAge.c_str()); p.priority = atoi(tPri.c_str());
            if(p.id > 0) {
                addRecord(p);
                if(p.id >= maxId) maxId = p.id + 1;
            }
        }
        file.close();
    }
};

// --- MinHeap for Emergency Queue ---
class MinHeap {
private:
    std::vector<Patient> heap;
    void heapifyUp(int i) {
        if(i == 0) return;
        int p = (i - 1) / 2;
        if(heap[i].priority < heap[p].priority) { std::swap(heap[i], heap[p]); heapifyUp(p); }
    }
    void heapifyDown(int i) {
        int l = 2 * i + 1, r = 2 * i + 2, s = i;
        if(l < (int)heap.size() && heap[l].priority < heap[s].priority) s = l;
        if(r < (int)heap.size() && heap[r].priority < heap[s].priority) s = r;
        if(s != i) { std::swap(heap[i], heap[s]); heapifyDown(s); }
    }
public:
    void insert(Patient p) { heap.push_back(p); heapifyUp(heap.size() - 1); }
    bool isEmpty() { return heap.empty(); }
    
    Patient extractMin() {
        Patient top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return top;
    }

    void display() {
        if(heap.empty()) { std::cout << "\nQueue is currently empty.\n"; return; }
        std::cout << "\n=== Current Emergency Queue (Heap) ===\n";
        for(int i = 0; i < (int)heap.size(); ++i) {
            std::string pStr = (heap[i].priority == 1) ? "Critical" : (heap[i].priority == 2 ? "Urgent" : "Standard");
            std::cout << "[" << pStr << "] ID: " << heap[i].id << " | Name: " << heap[i].name << "\n";
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename.c_str());
        if(!file) return;
        for(int i = 0; i < (int)heap.size(); ++i) {
            file << heap[i].id << "," << heap[i].name << "," << heap[i].age << ","
                 << heap[i].priority << "," << heap[i].symptoms << "\n";
        }
        file.close();
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename.c_str());
        if(!file) return;
        std::string line;
        while(std::getline(file, line)) {
            if(line.empty()) continue;
            std::stringstream ss(line);
            Patient p; std::string tId, tAge, tPri;
            std::getline(ss, tId, ','); std::getline(ss, p.name, ',');
            std::getline(ss, tAge, ','); std::getline(ss, tPri, ',');
            std::getline(ss, p.symptoms);
            p.id = atoi(tId.c_str()); p.age = atoi(tAge.c_str()); p.priority = atoi(tPri.c_str());
            if(p.id > 0) insert(p);
        }
        file.close();
    }
};
