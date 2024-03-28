//
// Created by basit on 12/10/2023.
//

#ifndef OOP_NEW_PROJECT_FACUITYMEMBERCHECK_H
#define OOP_NEW_PROJECT_FACUITYMEMBERCHECK_H


#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include"Person.h"
using namespace std;

class FacultyMember1 : public Person {
private:
    string title;
    string department;

public:
    // Default constructor
    FacultyMember1() : Person("", "", "") {}

    // Getter and setter for title

    void setTitle(const string& title) {
        this->title = title;
    }

    // Getter and setter for department
    string getDepartment() const {
        return department;
    }

    void setDepartment(const string& department) {
        this->department = department;
    }

    // Override the printDetails method
    void printDetails() const override {
        cout << "Name: " << getName() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "Title: " << title << endl;
        cout << "Department: " << department << endl;
    }
};

void checkFacultyMemberProfile() {
    string name;
    ifstream file;
    FacultyMember1 facultyMember;
    bool found = false; // Flag to indicate if a faculty member profile was found

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (!found) { // Loop until a valid faculty member profile is found
        cout << "Enter the name of the faculty member: ";
        getline(cin, name);

        // If the input string is empty, continue with the next iteration of the loop
        if (name.empty()) {
            continue;
        }

        file.open("faculty_" + name + ".txt");
        if (!file.is_open()) {
            cout << "No faculty member found with this name " << name << "\n";
        } else {
            found = true; // Set the flag to true as the staff member profile is found
            string line;

            // Read and process each line from the file
            while (getline(file, line)) {
                // Process the line if it contains a colon
                size_t colonPos = line.find(": ");
                if (colonPos != string::npos) {
                    string key = line.substr(0, colonPos);
                    string value = line.substr(colonPos + 2);

                    // Set the corresponding faculty member property based on the key
                    if (key == "Name") {
                        facultyMember.setName(value);
                    } else if (key == "Email") {
                        facultyMember.setEmail(value);
                    } else if (key == "Department") {
                        facultyMember.setDepartment(value);
                    } else if (key == "Title") {
                        facultyMember.setTitle(value);
                        break; // Assuming Title is the last required field
                    }
                }
            }
            file.close(); // Close the file after processing
        }
    }

    // Display faculty member details only if a profile was found
    if (found) {
        facultyMember.printDetails();
        // Omitting Father's Name from the output
        cout << "Press any key to return to the main menu...";
        cin.get(); // Wait for user input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    }
}
#endif //OOP_NEW_PROJECT_FACUITYMEMBERCHECK_H