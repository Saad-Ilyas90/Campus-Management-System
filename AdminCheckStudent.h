//
// Created by basit on 12/23/2023.
//

#ifndef OOP_NEW_PROJECT_ADMINCHECKSTUDENT_H
#define OOP_NEW_PROJECT_ADMINCHECKSTUDENT_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class AdminCheckStudentMarks {
public:
    void checkStudentMarks(const string& enrollment) {
        string marksFile = enrollment + "_marks.txt";
        ifstream file(marksFile);
        if (!file) {
            throw runtime_error("Failed to open file for reading: " + marksFile);
        }

        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }

        file.close();
    }
};
void adminStudentCheck() {
    AdminCheckStudentMarks checker;
    string enrollment;
    cin.ignore();
    cout << "Enter the enrollment number of the student: ";
    getline(cin, enrollment);
    try {
        checker.checkStudentMarks(enrollment);
    } catch (const runtime_error& e) {
        cout << "An error occurred: " << e.what() << endl;
    }
}
#endif //OOP_NEW_PROJECT_ADMINCHECKSTUDENT_H
