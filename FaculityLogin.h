//
// Created by basit on 12/17/2023.
//

#ifndef OOP_NEW_PROJECT_FACULITYLOGIN_H
#define OOP_NEW_PROJECT_FACULITYLOGIN_H

#include<iostream>
#include <string>
#include<fstream>
#include"LoginStudent.h"
using namespace std;

class FacultyLogin {
public:
 bool login(const string &name, const string &username, const string &password) {
    ifstream file("faculty_" + name + ".txt");
    if (!file.is_open()) {
        cout << "No faculty member found with the name " << name << "\n";
        return false;
    }

    string fileUsername, filePassword, line;
    string facultyDetails; // String to store the faculty member's details
    // Skip the faculty member's details and the separator line
    for (int i = 0; i < 7; i++) {
        getline(file, line);
        facultyDetails += line + "\n"; // Add the line to the faculty member's details
    }

    getline(file, fileUsername);
    fileUsername = fileUsername.substr(fileUsername.find(": ") + 2);
    getline(file, filePassword);
    filePassword = filePassword.substr(filePassword.find(": ") + 2);

    if (username != fileUsername || password != filePassword) {
        cout << "Invalid username or password.\n";
        return false;
    }

    // Display faculty member details
    cout << facultyDetails; // Print the faculty member's details
    return true;
}

   string getPassword() {
        string password;
        char ch;
        cout << "Enter your password: ";
        while ((ch = _getch()) != '\r') { // '\r' is the Enter key
            if (ch == '\b') { // '\b' is the Backspace key
                if (!password.empty()) {
                    cout << "\b \b"; // erase the last '*'
                    password.pop_back();
                }
            } else {
                cout << '*';
                password.push_back(ch);
            }
        }
        cout << endl;
        return password;
    }

};
string FacultyLoginn() {
    FacultyLogin facultyLogin;
    string name, username, password;
    cin.ignore();
    // Input and validation for name
    while (true) {
        cout << "Enter your name: ";
        getline(cin, name);
        if (name.empty()) {
            cout << "Name cannot be empty. Please try again.\n";
            continue;
        }
        // Add more validation checks if necessary
        break;
    }
    cin.ignore();
    // Input and validation for username
    while (true) {
        cout << "Enter your username: ";
        getline(cin, username);
        if (username.empty()) {
            cout << "Username cannot be empty. Please try again.\n";
            continue;
        }
        // Add more validation checks if necessary
        break;
    }

    // Input and validation for password
    while (true) {
        password = facultyLogin.getPassword();
        if (password.empty()) {
            cout << "Password cannot be empty. Please try again.\n";
            continue;
        }
        // Add more validation checks if necessary
        break;
    }

    if (!facultyLogin.login(name, username, password)) {
        cout << "Login failed. Exiting...\n";
        return ""; // Return an empty string if the login fails
    }
    return name;
}
#endif //OOP_NEW_PROJECT_FACULITYLOGIN_H
