//
// Created by basit on 12/10/2023.
//

#ifndef OOP_NEW_PROJECT_CHECKSTUDENTPROFILE_H
#define OOP_NEW_PROJECT_CHECKSTUDENTPROFILE_H

#endif //OOP_NEW_PROJECT_CHECKSTUDENTPROFILE_H
#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;
class Student : public Person {
private:
    string enrollment;
    string department;
    string semester;
public:
    Student() : Person("", "", "") {}

    string getDepartment() {
        return department;
    }
    void setID(string id) { // Added setID method
        this->id = id;
    }
    void setEnrollment(string e) {
        enrollment = e;
    }
    void setDepartment(string d) {
        department = d;
    }
    void setSemester(string s) {
        semester = s;
    }
    void printDetails() const override {
        cout << "Name: " << getName() << "\n";
        cout << "Email: " << getEmail() << "\n";
        cout << "Enrollment: " << enrollment << "\n";
        cout << "Department: " << department << "\n";
        cout << "Semester: " << semester << "\n";
    }
};
void checkStudentProfile() {
    string enrollment;
    ifstream file;
    Student student;
    bool found = false; // Flag to indicate if a student profile was found
    cin.ignore();

    while (!found) { // Loop until a valid student profile is found
        cout << "Enter the enrollment number of the student: ";
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

        file.close(); // Close the file after processing or if not found
    }

    // Display student details only if a profile was found
    if (found) {
        student.printDetails();
        // Display any additional fields you have in the student profile
        cout << "Press any key to return to the main menu...";
        cin.get(); // Wait for user input
    }
}