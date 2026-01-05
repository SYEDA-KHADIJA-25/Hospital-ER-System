#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileManager::FileManager(const std::string& file)
    : filename(file) {}

// Save patients to CSV
void FileManager::savePatients(const std::vector<Patient>& patients) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error: Could not open file for writing.\n";
        return;
    }

    // Write CSV header
    file << "ID,Name,Age,Symptoms,Priority\n";

    // Write patient data
    for (const auto& p : patients) {
        file << p.id << "," 
             << p.name << "," 
             << p.age << "," 
             << p.symptoms << "," 
             << p.priority << "\n";
    }

    file.close();
    std::cout << "Patient records saved to " << filename << "\n";
}

// Load patients from CSV
std::vector<Patient> FileManager::loadPatients() {
    std::vector<Patient> patients;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Warning: Could not open file. Starting with empty records.\n";
        return patients;
    }

    std::string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        if (firstLine) { 
            firstLine = false; // skip header
            continue; 
        }

        std::stringstream ss(line);
        std::string idStr, name, ageStr, symptoms, priorityStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, ageStr, ',');
        std::getline(ss, symptoms, ',');
        std::getline(ss, priorityStr, ',');

        if (idStr.empty()) continue;

        Patient p(
            std::stoi(idStr),
            name,
            std::stoi(ageStr),
            symptoms,
            std::stoi(priorityStr)
        );

        patients.push_back(p);
    }

    file.close();
    std::cout << "Loaded " << patients.size() << " patient records from " << filename << "\n";
    return patients;
}
