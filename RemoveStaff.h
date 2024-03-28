//
// Created by basit on 12/10/2023.
//

#ifndef OOP_NEW_PROJECT_REMOVESTAFF_H
#define OOP_NEW_PROJECT_REMOVESTAFF_H

#endif //OOP_NEW_PROJECT_REMOVESTAFF_H
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstring>
#include"Person.h"
using namespace std;

class StaffMember2 : public Person {
private:
    string department;
    string position;
public:
    StaffMember2() : Person("", "", "") {}

    string getDepartment() {
        return department;
    }
   void setId(string id) {
       this->id = id;
    }
    string getId() const {
        return id;
    }
    void setDepartment(string d) {
        department = d;
    }
    void setPosition(string p) {
        position = p;
    }


    // Override the printDetails function from the Person class
    void printDetails() const override {
        cout << "Name: " << getName() << "\n";
        cout<<"Phoeno: "<<getId()<<"\n";
        cout << "Department: " << department << "\n";
        cout << "Position: " << position << "\n";
    }
};
void removeStaff() {
    string name;
    ifstream file;
    StaffMember2 staff;
    bool found = false; // Flag to indicate if a staff profile was found
    cin.ignore();

    while (!found) { // Loop until a valid staff profile is found
        cout << "Enter the name of the staff to be removed: ";
        getline(cin, name);

        // If the input string is empty, continue with the next iteration of the loop
        if (name.empty()) {
            continue;
        }

        file.open("staff_" + name + ".txt");

        if (!file.is_open()) {
            cout << "No staff found with the name " << name << "\n";
        } else {
            found = true; // Set the flag to true as the staff profile is found
            string line;
            getline(file, line); // Skip the first line (Staff 1)
            getline(file, line);
            staff.setName(line.substr(line.find(": ") + 2));
            getline(file, line); // Skip Email
            getline(file, line);
            staff.setId(line.substr(line.find(": ") + 2));
            getline(file, line);
            staff.setDepartment(line.substr(line.find(": ") + 2));
            getline(file, line);
            staff.setPosition(line.substr(line.find(": ") + 2));
            // Skip the rest of the lines or extract additional fields if needed

            break; // Break out of the loop since the profile is found
        }

        file.close(); // Close the file after processing or if not found
    }

    // Display staff details only if a profile was found
    if (found) {
        staff.printDetails();
        file.close();
        // Display any additional fields you have in the staff profile
        cout << "The above staff will be removed. Press any key to continue...";
        cin.get(); // Wait for user input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        // Remove the staff file
        int result = remove(("staff_" + name + ".txt").c_str());
        if (result != 0) {
            cout << "Error deleting file. Error code: " << strerror(errno) << endl;
        } else {
            cout << "Staff removed successfully";
        }
    }
}