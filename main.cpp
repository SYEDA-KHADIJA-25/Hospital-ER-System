#include <iostream>
#include <string>
// Include your existing module headers
#include "Patient Reg (Module 1).h"
#include "(Module 1)MinHeap.cpp"
#include "Patient Records (Module 3).h" 
#include "Doctor and resources (Module 2).h"

int main() {
    // ==============================
    // 1. MODULE OBJECTS (Dynamic Memory)
    // ==============================
    // These objects manage data in RAM using linked lists, trees, and vectors
    MinHeap hospitalQueue;          
    PatientAVL recordTree;          
    Doctor doctorManager;           
    
    // Starting ID for the session
    int nextId = 101; 

    std::cout << ">>> Hospital Management System <<<\n";

    // ==============================
    // 2. MAIN INTERACTIVE MENU
    // ==============================
    int choice;
    while (true) {
        std::cout << "\n========================================";
        std::cout << "\n      HOSPITAL MANAGEMENT SYSTEM";
        std::cout << "\n========================================";
        std::cout << "\n1. Register New Patient (Emergency)";
        std::cout << "\n2. Process/Treat Next Patient (Min-Heap)";
        std::cout << "\n3. Display Waiting Queue (Min-Heap)";
        std::cout << "\n4. Display All Patient Records (AVL Tree)";
        std::cout << "\n5. Search Patient by ID (AVL Search)";
        std::cout << "\n6. Manage Doctors & Resources";
        std::cout << "\n7. Exit System";
        std::cout << "\n----------------------------------------";
        std::cout << "\nEnter choice: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) {
            Patient p;
            p.id = nextId++;
            std::cin.ignore();
            std::cout << "Enter Name: "; std::getline(std::cin, p.name);
            std::cout << "Enter Age: "; std::cin >> p.age;
            std::cin.ignore();
            std::cout << "Enter Symptoms: "; std::getline(std::cin, p.symptoms);
            std::cout << "Priority (1:Critical, 2:Urgent, 3:Standard): "; 
            std::cin >> p.priority;

            // Data is stored in the Heap and AVL Tree structures in RAM
            hospitalQueue.insert(p);
            recordTree.addRecord(p);
            
            std::cout << "\n[Success] Patient " << p.name << " registered with ID: " << p.id << "\n";

        } else if (choice == 2) {
            if (hospitalQueue.isEmpty()) {
                std::cout << "\n[Info] No patients currently in the emergency queue.\n";
            } else {
                // Extracting from heap (O(log n))
                Patient p = hospitalQueue.extractMin();
                std::cout << "\n>>> TREATING PATIENT <<<\n";
                std::cout << "Name: " << p.name << " | ID: " << p.id << " | Symptoms: " << p.symptoms << "\n";
                
                // Assign to doctor object in memory
                doctorManager.assignPatient(&p);
            }

        } else if (choice == 3) {
            // Displays the current state of the vector-based heap
            hospitalQueue.display();

        } else if (choice == 4) {
            // Performs In-order traversal of the AVL tree in memory
            std::cout << "\n=== Permanent Medical Records (AVL - Sorted by ID) ===\n";
            recordTree.displayAll();

        } else if (choice == 5) {
            int sid;
            std::cout << "Enter Patient ID to Search: ";
            std::cin >> sid;
            // O(log n) search through dynamic memory nodes
            recordTree.find(sid);

        } else if (choice == 6) {
            doctorManager.showDoctors();

        } else if (choice == 7) {
            std::cout << "\nCleaning up dynamic memory... Exiting system.\n";
            break;

        } else {
            std::cout << "\n[Error] Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
