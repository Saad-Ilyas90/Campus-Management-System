//
// Created by basit on 12/17/2023.
//

#ifndef OOP_NEW_PROJECT_STUDENTCHECKATTENDENCE_H
#define OOP_NEW_PROJECT_STUDENTCHECKATTENDENCE_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class StudentCheckAttendance {
private:
    string studentEnrollment;
    string attendanceFile;

public:
    StudentCheckAttendance(const string& enrollment)
            : studentEnrollment(enrollment) {
        attendanceFile = studentEnrollment + "_attendance.txt";
    }

    bool isStudentEnrolled() {
        ifstream file(studentEnrollment + "_enrolledCourses.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("Enrollment Number: " + studentEnrollment) != string::npos) {
                return true;
            }
        }
        return false;
    }

    void getAttendanceReport() {
        if (!isStudentEnrolled()) {
            cout << "Student " << studentEnrollment << " is not enrolled in any course.\n";
            return;
        }

        ifstream file(attendanceFile);
        if (!file) {
            cout << "No attendance record found for student " << studentEnrollment << ".\n";
            return;
        }

        string line;
        cout << "Attendance report for student " << studentEnrollment << ":\n";
        while (getline(file, line)) {
            cout << line << "\n";
        }
    }

};
#endif //OOP_NEW_PROJECT_STUDENTCHECKATTENDENCE_H
