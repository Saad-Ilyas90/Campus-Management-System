//
// Created by basit on 12/12/2023.
//

#ifndef OOP_NEW_PROJECT_UPDATEFACULITY_H
#define OOP_NEW_PROJECT_UPDATEFACULITY_H

#endif //OOP_NEW_PROJECT_UPDATEFACULITY_H
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include<cstring>
#include"Person.h"
using namespace std;
class Faculty : public Person {
private:
    string department;
    string position;
    string username;
    string password;
    string userType;
    string fathersName;
    string id;


public:
    // Add constructors that initialize the base class
    Faculty() : Person("", "", "") {}

    // Getter and setter methods for the new attributes
    string getDepartment() const { return department; }
    void setDepartment(const string& department) { this->department = department; }

    string getPosition() const { return position; }
    void setPosition(const string& position) { this->position = position; }

    string getUsername() const { return username; }
    void setUsername(const string& username) { this->username = username; }

    string getPassword() const { return password; }
    void setPassword(const string& password) { this->password = password; }

    string getUserType() const { return userType; }
    void setUserType(const string& userType) { this->userType = userType; }
    string getFathersName() const {
        return fathersName;
    }
    void setFathersName(const string& fathersName) {
        this->fathersName = fathersName;
    }
    string getId() const {
        return id;
    }
    void setId(const string& id) {
        this->id = id;
    }
    // Provide implementation for the pure virtual function from the Person class
    void printDetails() const override {
        cout << "Name: " << getName() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "Department: " << getDepartment() << endl;
        cout << "Position: " << getPosition() << endl;
        cout << "User Type: " << getUserType() << endl;
    }
    void renameRelatedFiles(const string& oldName, const string& newName) {
        for (const auto & entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
            string oldFileName = entry.path().filename().string();
            if (oldFileName.find(oldName) != string::npos) {
                string newFileName = oldFileName;
                size_t pos = newFileName.find(oldName);
                if (pos != string::npos) {
                    newFileName.replace(pos, oldName.length(), newName);
                    std::filesystem::rename(oldFileName, newFileName);
                }
            }
        }
    }
};
void updateFacultyProfile() {
    string name, newEmail,newFathersName;
    fstream file;
    Faculty faculty;
    bool found = false; // Flag to indicate if a faculty profile was found
    cin.ignore();

    while (!found) { // Loop until a valid faculty profile is found
        cout << "Enter the name of the faculty member: ";
        getline(cin, name);

        // If the input string is empty, continue with the next iteration of the loop
        if (name.empty()) {
            continue;
        }

        file.open("faculty_" + name + ".txt");

        if (!file.is_open()) {
            cout << "No faculty member found with the name " << name << "\n";
        } else {
            found = true; // Set the flag to true as the faculty profile is found
            string line;
            getline(file, line); // Skip the first line (Faculty 1)
            getline(file, line);
            faculty.setName(line.substr(line.find(": ") + 2));
            getline(file, line);
            faculty.setFathersName(line.substr(line.find(": ") + 2));
            getline(file, line);
            faculty.setEmail(line.substr(line.find(": ") + 2));
            getline(file, line);
            faculty.setDepartment(line.substr(line.find(": ") + 2));
            getline(file, line);
            faculty.setPosition(line.substr(line.find(": ") + 2));
            getline(file, line); // Skip the line with "------------------------"
            getline(file, line);
            faculty.setUsername(line.substr(line.find(": ") + 2));
            getline(file, line);
            faculty.setPassword(line.substr(line.find(": ") + 2));
            getline(file, line);
            faculty.setUserType(line.substr(line.find(": ") + 2));
            // Skip the rest of the lines or extract additional fields if needed

            file.close(); // Close the file after processing
            break; // Break out of the loop since the profile is found
        }

        file.close(); // Close the file after processing or if not found
    }

    // Update faculty details only if a profile was found
    if (found) {
        string newName, newDepartment, newPosition, existingUserType;

        do {
            cout << "Enter new name: ";
            getline(cin, newName);
            if (newName.length() > 10 || newName.length() < 3) {
                cout << "\nName should be less than 10 characters and more than 3 characters";
            } else if (newName != "") {
                bool hasNonAlpha = false;
                for (int i = 0; i < newName.length(); i++) {
                    if (!isalpha(newName[i]) && newName[i] != ' ') {
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
            }while (true);
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
        faculty.setFathersName(newFathersName);
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
        do {
            cout << "Enter new Title: ";
            getline(cin, newPosition);
            if (newPosition.empty()) {
                cout << "\nTitle should not be empty";
            } else {
                bool hasNonAlpha = false;
                for (int i = 0; i < newPosition.length(); i++) {
                    if (!isalpha(newPosition[i])&& newPosition[i] != ' ') {
                        hasNonAlpha = true;
                        break;
                    }
                }
                if (hasNonAlpha) {
                    cout << "Title should not contain numbers or special characters";
                } else {
                    break;
                }
            }
        } while (true);
        do {
            cout << "Enter new email: ";
            getline(cin, newEmail);
            regex email_regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
            if (!regex_match(newEmail, email_regex)) {
                cout << "Email should be valid";
            } else {
                break;
            }
        } while (true);
        // Generate new ID for the faculty member
        string newId = "faculty_" + to_string(rand());

        faculty.setId(newId);

// Generate new name
        string baseName = newName;
        string finalName = baseName;
        int count = 1;

// Check if a file with the same name already exists
        while (fs::exists("faculty_" + finalName + ".txt")) {
            // If it does, append a number to the end of the base name and check again
            finalName = baseName + to_string(count++);
        }

        faculty.setName(finalName); // Set the final name to the faculty object

        faculty.setDepartment(newDepartment);
        faculty.setPosition(newPosition);
        faculty.setEmail(newEmail);

// Generate new username based on name and new position
        string newUsername = faculty.getName() + "_" + faculty.getPosition();
        faculty.setUsername(newUsername);
        string newPassword = to_string(rand());
        faculty.setPassword(newPassword);

// Generate new random password
        string oldFileName = "faculty_" + name + ".txt";
        string newFileName = "faculty_" + faculty.getName() + ".txt";

        file.open(oldFileName, ios::out | ios::trunc); // Open the file in write mode to overwrite it


        file << "Faculty 1\n"; // Corrected faculty number
        file << "Name: " << faculty.getName() << "\n";
        file << "Father's Name: " << faculty.getFathersName() << "\n";
        file << "Email: " << faculty.getEmail() << "\n";
        file << "Department: " << faculty.getDepartment() << "\n";
        file << "Position: " << faculty.getPosition() << "\n";
        file << "------------------------\n";
        file << "Username: " << faculty.getUsername() << "\n"; // Write the new username
        file << "Password: " << faculty.getPassword() << "\n"; // Write the new password
        file << "User Type: " << faculty.getUserType() << "\n"; // Write the user type
        file << "------------------------\n";
        file.close();
        // Rename the file
        // Rename the faculty profile file
        if (rename(oldFileName.c_str(), newFileName.c_str()) != 0) {
            cout << "Error renaming file. Error code: " << strerror(errno) << endl;
        } else {
            cout << "Faculty profile updated and file renamed successfully.\n";
            // Rename all related files
            faculty.renameRelatedFiles(name, newName);
        }
      faculty.printDetails();
        cout << "Press any key to return to the main menu...";
        cin.get(); // Wait for user input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    }
}