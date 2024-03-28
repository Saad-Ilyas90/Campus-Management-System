//
// Created by basit on 12/10/2023.
//

#ifndef OOP_NEW_PROJECT_REMOVEFACULITY_H
#define OOP_NEW_PROJECT_REMOVEFACULITY_H
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstring>
#include <filesystem>
#include"Person.h"
using namespace std;
class Faculty1 : public Person {
private:
    string department;
    string position;
public:
    Faculty1() : Person("", "", "") {}

    string getDepartment() {
        return department;
    }
    void setDepartment(string d) {
        department = d;
    }
    void setPosition(string p) {
        position = p;
    }

    // Overriding the printDetails method from the Person class
    void printDetails() const override {
        cout << "Name: " << getName() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "Department: " << department << endl;
        cout << "Position: " << position << endl;
    }

    void removeRelatedFiles(const string& username) {
        for (const auto & entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
            string fileName = entry.path().filename().string();
            if (fileName.find(username) != string::npos) {
                std::filesystem::remove(fileName);
            }
        }
    }
};
void removeFaculty() {
    string username;
    ifstream file;
    Faculty1 faculty;
    bool found = false;
    cin.ignore();

    while (!found) {
        cout << "Enter the username of the faculty to be removed: ";
        getline(cin, username);

        if (username.empty()) {
            continue;
        }

        file.open("faculty_" + username + ".txt");

        if (!file.is_open()) {
            cout << "No faculty found with the username " << username << "\n";
        } else {
            found = true;
            cout << "Faculty found with the username " << username << "\n";

            string line;
            while (getline(file, line)) {
                size_t colonPos = line.find(": ");
                if (colonPos != string::npos) {
                    string key = line.substr(0, colonPos);
                    string value = line.substr(colonPos + 2);

                    if (key == "Name") {
                        faculty.setName(value);
                    } else if (key == "Email") {
                        faculty.setEmail(value);
                    } else if (key == "Department") {
                        faculty.setDepartment(value);
                    } else if (key == "Title") {
                        faculty.setPosition(value);
                    }
                }
            }

            break;
        }
    }

    file.close();

    if (found) {
        faculty.printDetails();
        cout << "The above faculty will be removed. Press any key to continue...";
        cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int result = remove(("faculty_" + username + ".txt").c_str());
        if (result != 0) {
            cout << "Error deleting file. Error code: " << strerror(errno) << endl;
        } else {
            cout << "Faculty removed successfully";
            faculty.removeRelatedFiles(username);
        }
    }
}
#endif //OOP_NEW_PROJECT_REMOVEFACULITY_H