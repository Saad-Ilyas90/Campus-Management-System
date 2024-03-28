//
// Created by basit on 12/10/2023.
//

#ifndef OOP_NEW_PROJECT_STAFFMEMEBERCHECK_H
#define OOP_NEW_PROJECT_STAFFMEMEBERCHECK_H


#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include"Person.h"

using namespace std;

class StaffMember1 : public Person {
private:
    string department;
    string position;
    string Phonno;
public:
    StaffMember1() : Person("", "", "") {}

    string getName() const {
        return Person::getName();
    }
    string getId() const {
        return Person::getID();
    }
    string getDepartment() const {
        return department;
    }
    string getPosition() const {
        return position;
    }
    void setName(string n) {
        Person::setName(n);
    }

    void setID(const string& id) {
        this->id = id;
    }
    void setDepartment(string d) {
        department = d;
    }
    void setPosition(string p) {
        position = p;
    }

    // Provide implementation for the pure virtual function from the Person class
    void printDetails() const override {
        cout << "Name: " << getName() << endl;
        cout << "Phoneno " << getId() << endl;
        cout << "Department: " << getDepartment() << endl;
        cout << "Position: " << getPosition() << endl;
    }
};
void checkStaffMemberProfile() {
    string name;
    ifstream file;
    StaffMember1 staffMember;
    bool found = false; // Flag to indicate if a staff member profile was found
    cin.ignore();

    while (!found) { // Loop until a valid staff member profile is found
        cout << "Enter the Name of the staff member: ";
        getline(cin, name);

        // If the input string is empty, continue with the next iteration of the loop
        if (name.empty()) {
            continue;
        }

        file.open("staff_" + name+ ".txt");

        if (!file.is_open()) {
            cout << "No staff member found with the Name " << name<< "\n";
        } else {
            found = true; // Set the flag to true as the staff member profile is found
            string line;
            getline(file, line); // Skip the first line (Staff 1)
            getline(file, line);
            staffMember.setName(line.substr(line.find(": ") + 2));
            getline(file, line); // Skip Email
            getline(file, line);
            staffMember.setID(line.substr(line.find(": ") + 2));
            getline(file, line);
            staffMember.setDepartment(line.substr(line.find(": ") + 2));
            getline(file, line);
            staffMember.setPosition(line.substr(line.find(": ") + 2));
            // Skip the rest of the lines or extract additional fields if needed

            break; // Break out of the loop since the profile is found
        }

        file.close(); // Close the file after processing or if not found
    }

    // Display staff member details only if a profile was found
    if (found) {
        staffMember.printDetails();
        // Display any additional fields you have in the staff member profile
        cout << "Press any key to return to the main menu...";
        cin.get(); // Wait for user input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    }
}
#endif //OOP_NEW_PROJECT_STAFFMEMEBERCHECK_H