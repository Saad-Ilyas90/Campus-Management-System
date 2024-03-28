//
// Created by basit on 12/15/2023.
//

#ifndef OOP_NEW_PROJECT_LOGINSTUDENT_H
#define OOP_NEW_PROJECT_LOGINSTUDENT_H


#include<iostream>
#include <string>
#include<fstream>
using namespace std;
class StudentLogin {
public:
    bool login(const string &enrollment, const string &username, const string &password) {
        ifstream file("student_" + enrollment + ".txt");
        if (!file.is_open()) {
            cout << "No student found with the enrollment number " << enrollment << "\n";
            return false;
        }

        string fileUsername, filePassword, line;
        string studentDetails; // String to store the student's details
        // Skip the student's details and the separator line
        for (int i = 0; i < 9; i++) {
            getline(file, line);
            studentDetails += line + "\n"; // Add the line to the student's details
        }

        getline(file, fileUsername);
        fileUsername = fileUsername.substr(fileUsername.find(": ") + 2);
        getline(file, filePassword);
        filePassword = filePassword.substr(filePassword.find(": ") + 2);

        if (username != fileUsername || password != filePassword) {
            cout << "Invalid username or password.\n";
            return false;
        }

        // Display student details
        cout << studentDetails; // Print the student's details
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
string StudentLoginn() {
    StudentLogin studentLogin;
    string enrollment, username, password;
    cin.ignore();
    // Input and validati on for enrollment
    while (true) {
        cout << "Enter your enrollment number: ";
        getline(cin, enrollment);
        if (enrollment.empty()) {
            cout << "Enrollment number cannot be empty. Please try again.\n";
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
        password = studentLogin.getPassword();
        if (password.empty()) {
            cout << "Password cannot be empty. Please try again.\n";
            continue;
        }
        // Add more validation checks if necessary
        break;
    }

    if (!studentLogin.login(enrollment, username, password)) {
        cout << "Login failed. Exiting...\n";
        return "";
    }
    return enrollment;
}
#endif //OOP_NEW_PROJECT_LOGINSTUDENT_H