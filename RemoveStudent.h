//
// Created by basit on 12/10/2023.
//

#ifndef OOP_NEW_PROJECT_REMOVESTUDENT_H
#define OOP_NEW_PROJECT_REMOVESTUDENT_H

#endif //OOP_NEW_PROJECT_REMOVESTUDENT_H
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include<filesystem>
#include"Person.h"
using namespace std;
class Student1 : public Person {
private:
    string department;
    string semester;
    string enrollment;
public:

    Student1() : Person("", "", ""), department(""), semester(""), enrollment("") {} // Added default constructor

    string getDepartment() {
        return department;
    }
    void setDepartment(string d) {
        department = d;
    }
    void setSemester(string s) {
        semester = s;
    }

    void setEnrollment(const string& enrollment) { this->enrollment = enrollment; } // Added setEnrollment method

    void printDetails() const override {
        cout << "Student Name: " << getName() << "\n";
        cout << "Email: " << getEmail() << "\n";
        cout << "Department: " << department << "\n";
        cout << "Semester: " << semester << "\n";
        cout << "Enrollment: " << enrollment << "\n"; // Added Enrollment to printDetails
    }
    void removeRelatedFiles(const string& enrollment) {
        for (const auto & entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
            string fileName = entry.path().filename().string();
            if (fileName.find(enrollment) != string::npos) {
                std::filesystem::remove(fileName);
            }
        }
    }
};
void removeStudent() {
    string enrollment;
    ifstream file;
    Student1 student;
    bool found = false; // Flag to indicate if a student profile was found
    cin.ignore();

    while (!found) { // Loop until a valid student profile is found
        cout << "Enter the enrollment number of the student to be removed: ";
        getline(cin, enrollment);

        // If the input string is empty, continue with the next iteration of the loop
        if (enrollment.empty()) {
            continue;
        }

        file.open("student_" + enrollment + ".txt");

        if (!file.is_open()) {
            cout << "No student found with the enrollment number " << enrollment << "\n";
        } else {
            found = true; // Set the flag to true as the student profile is found
            cout << "Student found with the enrollment number " << enrollment << "\n"; // Debugging statement

            string line;
            getline(file, line); // Skip the first line (Student 1)
            getline(file, line);
            student.setName(line.substr(line.find(": ") + 2));
            getline(file, line); // Skip Father's Name
            getline(file, line);
            student.setEmail(line.substr(line.find(": ") + 2)); // Set Email
            getline(file, line); // Skip Gender
            getline(file, line);
            student.setDepartment(line.substr(line.find(": ") + 2));
            getline(file, line);
            student.setSemester(line.substr(line.find(": ") + 2));
            getline(file, line);
            student.setEnrollment(line.substr(line.find(": ") + 2));
            // Skip the rest of the lines or extract additional fields if needed

            break; // Break out of the loop since the profile is found
        }

    }
        file.close(); // Close the file after processing or if not found


    // Display student details only if a profile was found
    if (found) {
        student.printDetails();
        // Display any additional fields you have in the student profile
        cout << "The above student will be removed. Press any key to continue...";
        cin.get(); // Wait for user input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        // Remove the student file
        // Remove the student profile file
        int result = remove(("student_" + enrollment + ".txt").c_str());
        if (result != 0) {
            cout << "Error deleting file. Error code: " << strerror(errno) << endl;
        } else {
            cout << "Student profile removed successfully.\n";
            // Remove all related files
            student.removeRelatedFiles(enrollment);
        }
    }
}