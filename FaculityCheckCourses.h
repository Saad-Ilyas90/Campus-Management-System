//
// Created by basit on 12/17/2023.
//

#ifndef OOP_NEW_PROJECT_FACULITYCHECKCOURSES_H
#define OOP_NEW_PROJECT_FACULITYCHECKCOURSES_H
#include<iostream>
#include <string>
#include<fstream>
#include"AssignCourses.h"
using namespace std;
class FacultyCheckCourses {
private:
    string facultyName;
    AssignedCourses ac;
public:
    FacultyCheckCourses(const string &name) : facultyName(name) {
        ac.setFacultyName(name);
    }

    void checkCourses() {
        if (!ac.isValidFacultyName()) {
            cout << "Invalid faculty name." << endl;
            return;
        }

        string filename = facultyName + "_assignedCourses.txt";
        ifstream file(filename);
        if (!file) {
            cout << "No courses assigned to the faculty member " << facultyName << "\n";
            return;
        }
        if (!file.is_open()) {
            cout << "No courses found for the faculty member " << facultyName << "\n";
            return;
        }
        string line;
        cout << "Courses assigned to " << facultyName << ":";
        while (getline(file, line)) {
            if (line.find("Course Code: ") != string::npos) {
                cout << line.substr(13) << "\n"; // Print the course code
            }
        }
        file.close();
    }
};
void checkCourses(const string &name) {
    FacultyCheckCourses facultyCheckCourses(name);
    facultyCheckCourses.checkCourses();
}
#endif //OOP_NEW_PROJECT_FACULITYCHECKCOURSES_H
