//
// Created by basit on 12/13/2023.
//

#ifndef OOP_NEW_PROJECT_UPDATESTAFF_H
#define OOP_NEW_PROJECT_UPDATESTAFF_H


#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include<cstring>
#include"Person.h"
using namespace std;
class Staff : public Person{
private:
    string department;
    string position;
    string phone;
    string fathersName;
public:
    // Add constructors that initialize the base class
    Staff() : Person("", "", "") {}

    // Getter and setter methods for the new attributes
    string getDepartment() const { return department; }
    void setDepartment(const string& department) { this->department = department; }

    string getPosition() const { return position; }
    void setPosition(const string& position) { this->position = position; }

    string getPhone() const { return phone; }
    void setPhone(const string& phone) { this->phone = phone; }

    string getFathersName() const {
        return fathersName;
    }
    void setFathersName(const string& fathersName) {
        this->fathersName = fathersName;
    }

    // Provide implementation for the pure virtual function from the Person class
    void printDetails() const override {
        cout << "Name: " << getName() << endl;
        cout << "Father's Name: " << getFathersName() << endl;
        cout << "Phone: " << getPhone() << endl;
        cout << "Department: " << getDepartment() << endl;
        cout << "Position: " << getPosition() << endl;
    }
};
void updateStaffProfile() {
    string name, newPhone, newDepartment, newPosition, newFathersName;
    Staff staff;
    bool found = false;
    string line, oldFileName, newFileName;
    ifstream inFile;
    ofstream outFile, tempFile;

    cin.ignore();
    while (!found) {
        cout << "Enter the name of the staff member: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Name cannot be empty. Please try again.\n";
            continue;
        }

        oldFileName = "staff_" + name + ".txt";
        inFile.open(oldFileName);

        if (!inFile.is_open()) {
            cout << "No staff member found with the name " << name << "\n";
            inFile.close();
        } else {
            found = true;
            inFile.close();
        }
    }

    if (found) {
        do {
            cout << "Enter new name: ";
            getline(cin, name);
            if (name.length() > 10 || name.length() < 3) {
                cout << "\nName should be less than 10 characters and more than 3 characters";
            } else if (name != "") {
                bool hasNonAlpha = false;
                for (int i = 0; i < name.length(); i++) {
                    if (!isalpha(name[i]) && name[i] != ' ') {
                        hasNonAlpha = true;
                        break;
                    }
                }
                if (hasNonAlpha) {
                    cout << "Name should not contain numbers or special characters";
                } else {
                    break;
                }
            }
        } while (true);
        staff.setName(name);

        do {
            cout << "Enter new father's name: ";
            getline(cin, newFathersName);
            if (newFathersName.length() > 50 || newFathersName.length() < 3) {
                cout << "\nFather's name should be less than 50 characters and more than 3 characters";
            } else if (newFathersName != "") {
                bool hasNonAlpha = false;
                for (int i = 0; i < newFathersName.length(); i++) {
                    if (!isalpha(newFathersName[i]) && newFathersName[i] != ' ') {
                        hasNonAlpha = true;
                        break;
                    }
                }
                if (hasNonAlpha) {
                    cout << "Father's name should not contain numbers or special characters";
                } else {
                    break;
                }
            }
        } while (true);
        // Generate new name
        string baseName = name;
        string finalName = baseName;
        int count = 1;

        // Check if a file with the same name already exists
        while (fs::exists("staff_" + finalName + ".txt")) {
            // If it does, append a number to the end of the base name and check again
            finalName = baseName + to_string(count++);
        }

        staff.setName(finalName);

        do {
            cout << "Enter new phone number: ";
            getline(cin, newPhone);
            if (newPhone.length() != 11) {
                cout << "Phone number should be 11 digits. Please try again.\n";
            } else {
                break;
            }
        } while (true);
        staff.setPhone(newPhone);

        do {
            cout << "Enter new department: ";
            getline(cin, newDepartment);
            if (newDepartment.empty() || newDepartment.length() < 2) {
                cout << "Department name should not be empty and should be at least 2 characters long." << endl;
            } else {
                bool hasNonAlpha = false;
                for (int i = 0; i < newDepartment.length(); i++) {
                    if (!isalpha(newDepartment[i]) && newDepartment[i] != ' ') {
                        hasNonAlpha = true;
                        break;
                    }
                }
                if (hasNonAlpha) {
                    cout << "Department name should not contain numbers or special characters." << endl;
                } else {
                    break;
                }
            }
        } while (true);
        staff.setDepartment(newDepartment);

        do {
            cout << "Enter new position: ";
            getline(cin, newPosition);
            if (newPosition.empty()) {
                cout << "\nPosition should not be empty";
            } else {
                bool hasNonAlpha = false;
                for (int i = 0; i < newPosition.length(); i++) {
                    if (!isalpha(newPosition[i]) && newPosition[i] != ' ') {
                        hasNonAlpha = true;
                        break;
                    }
                }
                if (hasNonAlpha) {
                    cout << "Position should not contain numbers or special characters";
                } else {
                    break;
                }
            }
        } while (true);
        staff.setPosition(newPosition);

        newFileName = "staff_" + staff.getName() + ".txt";
        tempFile.open("temp.txt");

        if (!tempFile) {
            cout << "Error opening temporary file. Error code: " << strerror(errno) << endl;
        } else {
            tempFile << "Staff Member 1\n";
            tempFile << "Name: " << staff.getName() << "\n";
            tempFile << "Father's Name: " << staff.getFathersName() << "\n";
            tempFile << "Phone: " << staff.getPhone() << "\n";
            tempFile << "Department: " << staff.getDepartment() << "\n";
            tempFile << "Position: " << staff.getPosition() << "\n";
            tempFile << "------------------------\n";
            tempFile.close();
        }

        // Delete old file
        if (remove(oldFileName.c_str()) != 0) {
            cout << "Error deleting old file. Error code: " << strerror(errno) << endl;
        } else {
            // Rename temporary file to new file
            if (rename("temp.txt", newFileName.c_str()) != 0) {
                cout << "Error renaming file. Error code: " << strerror(errno) << endl;
            } else {
                cout << "Staff profile updated successfully.\n";
                staff.printDetails();
                cout << "Press any key to return to the main menu...";
                cin.get();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}
#endif //OOP_NEW_PROJECT_UPDATESTAFF_H