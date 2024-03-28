//
// Created by basit on 12/16/2023.
//

#ifndef OOP_NEW_PROJECT_STUDENTUPDATEUSERNAMEPASSWORD_H
#define OOP_NEW_PROJECT_STUDENTUPDATEUSERNAMEPASSWORD_H
#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
class StudentUpdateUsernamePassword {
public:
    void update(const string &enrollment, const string &newUsername, const string &newPassword) {
        ifstream file("student_" + enrollment + ".txt");
        if (!file.is_open()) {
            cout << "No student found with the enrollment number " << enrollment << "\n";
            return;
        }
        string line, updatedContents;
        while (getline(file, line)) {
            if (line.find("Username: ") != string::npos) {
                line = "Username: " + newUsername;
            } else if (line.find("Password: ") != string::npos) {
                line = "Password: " + newPassword;
            }
            updatedContents += line + "\n";
        }
        file.close();

        ofstream fileOut("student_" + enrollment + ".txt");
        fileOut << updatedContents;
        fileOut.close();
    }
    string getPassword() {
        string password;
        char ch;
        cout << "Enter your new password: ";
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

void updateStudentUsernamePassword(const string &enrollment) {
    StudentUpdateUsernamePassword studentUpdateUsernamePassword;
    string newUsername;
    string newPassword;
    cin.ignore();
    do {
        cout << "Enter the new username: ";
        getline(cin, newUsername);
        if (newUsername.length() < 3 || newUsername.empty()) {
            cout << "Username should be at least 3 characters long and should not be empty. Please try again.\n";
        }
    } while (newUsername.length() < 3 || newUsername.empty());

    do {
        newPassword = studentUpdateUsernamePassword.getPassword();
        if (newPassword.length() < 3 || newPassword.empty()) {
            cout << "Password should be at least 3 characters long and should not be empty. Please try again.\n";
        }
    } while (newPassword.length() < 3 || newPassword.empty());

    studentUpdateUsernamePassword.update(enrollment, newUsername, newPassword);
    cout << "Username and password updated successfully.\n";
    system("pause");
    cout<<"press any key to continue";
}
#endif //OOP_NEW_PROJECT_STUDENTUPDATEUSERNAMEPASSWORD_H