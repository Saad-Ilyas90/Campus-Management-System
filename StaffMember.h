//
// Created by basit on 12/9/2023.
//

#ifndef OOP_NEW_PROJECT_STAFFMEMBER_H
#define OOP_NEW_PROJECT_STAFFMEMBER_H

#endif //OOP_NEW_PROJECT_STAFFMEMBER_H
#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include"Person.h"

using namespace std;
class StaffMember : public Person {
private:
    string department;
    string position;
    string Phonno;
public:
    // Default constructor
    StaffMember() : Person("", "", "") {}
    string getDepartment() const {
        return department;
    }

    void setDepartment(const string& department) {
        this->department = department;
    }

    string getPosition() const {
        return position;
    }

    void setPosition(const string& position) {
        this->position = position;
    }

    string getPhonno() const {
        return Phonno;
    }

    void setPhonno(const string& Phonno) {
        this->Phonno = Phonno;
    }

    // Provide implementation for the pure virtual function from the Person class
    void printDetails() const override {
        cout << "Name: " << getName() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "ID: " << getID() << endl;
        cout << "Department: " << getDepartment() << endl;
        cout << "Position: " << getPosition() << endl;
        cout << "Phone Number: " << getPhonno() << endl;
    }
};
void StaffDetails() {
    string name, fname, d, position;
    string Phonno;
    int numStaff;
    StaffMember s;
    while(true) {
        cout << "Enter number of Staff Member to add" << endl;
        if (cin >> numStaff) {
            if (numStaff <= 0) {
                cout << "Number of Staff Member should be a positive integer." << endl;
            } else {
                break;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); // clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
        }
    }
    cin.ignore();
    while (true) {
        cout << "Enter department of students"<<endl;
        getline(cin, d);
        if (d.empty() || d.length() < 2) {
            cout << "Department name should not be empty and should be at least 2 characters long." << endl;
        } else {
            bool hasNonAlpha = false;
            for (int i = 0; i < d.length(); i++) {
                if (!isalpha(d[i]) && d[i] != ' ') {
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
    }
    StaffMember *staffMembers = new StaffMember[numStaff];
    for (int i = 0; i < numStaff; i++) {
        cin.ignore();
        do {
            cout << "\nEnter Name of Staff Member:" << " " << (i + 1) << endl;
            getline(cin, name);
            if (name.length() > 10 || name.length() < 3) {
                cout << "\nName should be less than 10 characters and more than 3 characters";
            } else if (name != "") {
                bool hasNonAlpha = false;
                for (int i = 0; i < name.length(); i++) {
                    if (!isalpha(name[i])&& name[i] != ' ') {
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
        do {
            cout << "\nEnter Father Name of Staff Member: " << (i + 1) << endl;
            getline(cin, fname);
            if (fname.length() > 10 || fname.length() < 3) {
                cout << "Father Name should be less than 10 characters and more than 3 characters";
            } else if (fname != "") {
                bool hasNonAlpha = false;
                for (int i = 0; i < fname.length(); i++) {
                    if (!isalpha(fname[i])&& fname[i] != ' ') {
                        hasNonAlpha = true;
                        break;
                    }
                }
                if (hasNonAlpha) {
                    cout << "Father Name should not contain numbers or special characters";
                } else {
                    break;
                }
            }
        } while (true);
        do {
            cout << "\nEnter Phonenumber of Staff Member: " << (i + 1)<<endl;// Declare Phonno as string
            getline(cin, Phonno);
            if (Phonno.length() == 11 && all_of(Phonno.begin(), Phonno.end(), ::isdigit)) { // Check if the phone number is 11 digits long and all characters are digits
                break;
            } else {
                cout << "Phonenumber should be an 11 digit number and should only contain digits." << endl;
            }
        } while (true);// Set the phone number
        do {
            cout << "\nEnter Position of Staff Member: " << (i + 1) << endl;
            getline(cin, position);
            if (position.empty()) {
                cout << "\nPosition should not be empty";
            } else {
                break;
            }
        } while (true);
        s.setName(name);
        s.setFName(fname);
        s.setPhonno(Phonno);
        s.setDepartment(d);
        s.setPosition(position);
        staffMembers[i] = s;

        // Create a new file for each staff member using their name
        // Create a new file for each staff member using their name
        ofstream file;
        string baseFilename = "staff_" + s.getName();
        string filename = baseFilename + ".txt";
        int count = 1;

        // Check if a file with the same name already exists
        while (fs::exists(filename)) {
            // If it does, append a number to the end of the staff member's name and check again
            filename = baseFilename + to_string(count++) + ".txt";
        }

        file.open(filename, ios::out); // Open the file in write mode

        // Write staff member details to file
        file << "Staff Member " << (i + 1) << "\n";
        file << "Name: " << s.getName() << "\n";
        file << "Father's Name: " << s.getFName() << "\n";
        file << "Phonno: " << s.getPhonno() << "\n";
        file << "Department: " << s.getDepartment() << "\n";
        file << "Position: " << s.getPosition() << "\n";
        file << "------------------------\n";

        file.close();
        s.printDetails();
        cout << "\nStaff Member " << (i + 1) << " added successfully" << endl;
        system("pause");
    }
    delete[] staffMembers;

}
