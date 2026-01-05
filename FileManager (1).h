#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "Patient.h"

class FileManager {
private:
    std::string filename;

public:
    FileManager(const std::string& file); // constructor with file name

    // Save patient records to CSV file
    void savePatients(const std::vector<Patient>& patients);

    // Load patient records from CSV file
    std::vector<Patient> loadPatients();
};

#endif // FILEMANAGER_H
