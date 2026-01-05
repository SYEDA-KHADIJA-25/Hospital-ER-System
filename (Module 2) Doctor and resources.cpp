#include "Module2.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
using namespace std;

/*================ GLOBAL STORAGE ================*/

static vector<Doctor> doctors;
static vector<Resource> resources;
static AllocationQueue allocationQueue;

static int nextDoctorID = 1;
static int nextResourceID = 1;

/*================ Utility ================*/

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*================ Allocation Queue ================*/

AllocationQueue::AllocationQueue() {
    front = rear = nullptr;
}

bool AllocationQueue::isEmpty() {
    return front == nullptr;
}

Node* AllocationQueue::getFront() {
    return front;
}

void AllocationQueue::enqueue(PatientLite p, Doctor d, Resource r) {
    Node* n = new Node{p, d, r, nullptr};

    if (isEmpty())
        front = rear = n;
    else {
        rear->next = n;
        rear = n;
    }
}

void AllocationQueue::dequeue() {
    if (isEmpty()) return;

    Node* temp = front;
    front = front->next;

    if (!front)
        rear = nullptr;

    delete temp;
}

void AllocationQueue::display() {

    if (isEmpty()) {
        cout << "No allocations.\n";
        return;
    }

    Node* t = front;
    while (t) {
        cout << "Patient: " << t->patient.name
             << " | Doctor: " << t->doctor.name
             << " | Resource: " << t->resource.name << endl;
        t = t->next;
    }
}

/*================ File I/O ================*/

void AllocationQueue::saveToFile(const string& file) {

    ofstream f(file);
    Node* t = front;

    while (t) {
        f << t->patient.id << "," << t->patient.name << ","
          << t->doctor.id << "," << t->doctor.name << ","
          << t->resource.id << "," << t->resource.name << "\n";
        t = t->next;
    }
}

void AllocationQueue::loadFromFile(const string& file) {

    ifstream f(file);
    if (!f) return;

    string line;
    while (getline(f, line)) {

        stringstream ss(line);
        string temp;

        PatientLite p;
        Doctor d;
        Resource r;

        getline(ss, temp, ','); p.id = stoi(temp);
        getline(ss, p.name, ',');

        getline(ss, temp, ','); d.id = stoi(temp);
        getline(ss, d.name, ',');

        getline(ss, temp, ','); r.id = stoi(temp);
        getline(ss, r.name);

        enqueue(p, d, r);
    }
}

/*================ Doctor / Resource Persistence ================*/

void saveDoctors() {
    ofstream f("doctors.csv");
    for (auto& d : doctors)
        f << d.id << "," << d.name << "," << d.specialization
          << "," << d.available << "\n";
}

void loadDoctors() {
    ifstream f("doctors.csv");
    if (!f) return;

    doctors.clear();
    string line;

    while (getline(f, line)) {
        stringstream ss(line);
        Doctor d;
        string temp;

        getline(ss, temp, ','); d.id = stoi(temp);
        getline(ss, d.name, ',');
        getline(ss, d.specialization, ',');
        getline(ss, temp); d.available = (temp == "1");

        doctors.push_back(d);
        nextDoctorID = max(nextDoctorID, d.id + 1);
    }
}

void saveResources() {
    ofstream f("resources.csv");
    for (auto& r : resources)
        f << r.id << "," << r.name << "," << r.available << "\n";
}

void loadResources() {
    ifstream f("resources.csv");
    if (!f) return;

    resources.clear();
    string line;

    while (getline(f, line)) {
        stringstream ss(line);
        Resource r;
        string temp;

        getline(ss, temp, ','); r.id = stoi(temp);
        getline(ss, r.name, ',');
        getline(ss, temp); r.available = (temp == "1");

        resources.push_back(r);
        nextResourceID = max(nextResourceID, r.id + 1);
    }
}

/*================ MAIN MENU (MODULE 2) ================*/

void runModule2Menu() {

    loadDoctors();
    loadResources();
    allocationQueue.loadFromFile("allocation_queue.csv");

    int c;
    while (true) {

        cout << "\n=== MODULE 2 : DOCTOR & RESOURCE MANAGEMENT ===\n"
             << "1 Add Doctor\n"
             << "2 Add Resource\n"
             << "3 Allocate Patient\n"
             << "4 Release Patient\n"
             << "5 Show Allocations\n"
             << "6 Exit Module 2\n"
             << "Choice: ";

        cin >> c;

        if (c == 1) {
            Doctor d;
            d.id = nextDoctorID++;
            clearInput();
            cout << "Doctor Name: ";
            getline(cin, d.name);
            cout << "Specialization: ";
            getline(cin, d.specialization);
            d.available = true;
            doctors.push_back(d);
        }

        else if (c == 2) {
            Resource r;
            r.id = nextResourceID++;
            clearInput();
            cout << "Resource Name: ";
            getline(cin, r.name);
            r.available = true;
            resources.push_back(r);
        }

        else if (c == 3) {

            PatientLite p;
            cout << "Patient ID: ";
            cin >> p.id;
            clearInput();
            cout << "Patient Name: ";
            getline(cin, p.name);

            Doctor* d = nullptr;
            Resource* r = nullptr;

            for (auto& doc : doctors)
                if (doc.available) { d = &doc; break; }

            for (auto& res : resources)
                if (res.available) { r = &res; break; }

            if (!d || !r) {
                cout << "No doctor or resource available.\n";
                continue;
            }

            d->available = false;
            r->available = false;

            allocationQueue.enqueue(p, *d, *r);
        }

        else if (c == 4) {

            if (allocationQueue.isEmpty()) {
                cout << "Queue empty.\n";
                continue;
            }

            Node* f = allocationQueue.getFront();

            for (auto& d : doctors)
                if (d.id == f->doctor.id) d.available = true;

            for (auto& r : resources)
                if (r.id == f->resource.id) r.available = true;

            allocationQueue.dequeue();
            cout << "Patient released.\n";
        }

        else if (c == 5)
            allocationQueue.display();

        else break;
    }

    saveDoctors();
    saveResources();
    allocationQueue.saveToFile("allocation_queue.csv");
}
