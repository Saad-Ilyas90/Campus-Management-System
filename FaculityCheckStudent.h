//
// Created by basit on 12/17/2023.
//

#ifndef OOP_NEW_PROJECT_FACULITYCHECKSTUDENT_H
#define OOP_NEW_PROJECT_FACULITYCHECKSTUDENT_H


#include <iostream>
#include <fstream>
using namespace std;

class FacultyCheckStudent {
private:
    string facultyName;
    string courseCode;
    string studentEnrollment;
    string attendanceFile;

public:
    void setStudentEnrollment(const string& enrollment) {
        studentEnrollment = enrollment;
    }

    FacultyCheckStudent(const string& faculty)
            : facultyName(faculty) {
        // Read course code from a file
        ifstream file(facultyName + "_assignedCourses.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("Course Code: ") != string::npos) {
                courseCode = line.substr(13); // Extract the course code
            }
        }
        file.close();
    }



 string getStudentName(const string& enrollment) {
    ifstream file("student_" + enrollment + ".txt");
    string line;
    while (getline(file, line)) {
        if (line.find("Name: ") != string::npos) {
            return line.substr(6); // Extract the student name
        }
    }
    return "";
}
    bool isStudentEnrolled() {
        ifstream file(studentEnrollment + "_enrolledCourses.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("Course Code: " + courseCode) != string::npos) {
                return true;
            }
        }
        return false;
    }


    void markAttendance(bool isPresent, int hours) {
        attendanceFile = studentEnrollment + "_attendance.txt";

        ofstream file(attendanceFile, ios::app);
        if (!file) {
            cout << "Failed to open file for writing: " << attendanceFile << "\n";
            return;
        }

        file << "Course Code: " << courseCode << "\n";
        file << "Attendance: " << (isPresent ? "Present" : "Absent") << "\n";
        file << "Hours: " << hours << "\n";
        file << "------------------------\n";

        cout << "Attendance marked successfully for student " << studentEnrollment << " in course " << courseCode << ".\n";
    }

   void saveAttendanceReport() {
    ifstream file(attendanceFile);
    if (!file) {
        cout << "No attendance record found for student " << studentEnrollment << ".\n";
        return;
    }

    string line;
    cout << "Attendance report for student " << studentEnrollment << " in course " << courseCode << ":\n";
    while (getline(file, line)) {
        if (line.find("Course Code: " + courseCode) != string::npos) {
            cout << line << "\n"; // Course Code
            getline(file, line);
            cout << line << "\n"; // Attendance
            getline(file, line);
            cout << line << "\n"; // Hours
            getline(file, line);
            cout << line << "\n"; // ------------------------
        }
    }
}
};
void FacultyCheckStudentFunction(FacultyCheckStudent& checker){
    string isPresentStr;
    bool isPresent;
    int hours;
    for (const auto & entry : fs::directory_iterator(fs::current_path())) {
        if (entry.path().filename().string().find("_enrolledCourses.txt") != string::npos) {
            string studentEnrollment = entry.path().filename().string();
            studentEnrollment = studentEnrollment.substr(0, studentEnrollment.find("_")); // Extract the enrollment number
            checker.setStudentEnrollment(studentEnrollment); // Set the student enrollment number

            if (checker.isStudentEnrolled()) {
                string studentName = checker.getStudentName(studentEnrollment);
                do {
                    cout << "Is student " << studentName << " (" << studentEnrollment << ") present? (yes/no): ";
                    cin >> isPresentStr;
                    if (isPresentStr != "yes" && isPresentStr != "no") {
                        cout << "Invalid input. Please enter 'yes' or 'no'." << endl;
                    }
                } while (isPresentStr != "yes" && isPresentStr != "no");
                isPresent = (isPresentStr == "yes");
                do {
                    cout << "How many hours was the student present/absent? ";
                    cin >> hours;
                    if (cin.fail() || hours < 1 || hours > 3) {
                        cout << "Invalid input. Please enter a number between 1 and 3." << endl;
                        cin.clear(); // clear the error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
                    }
                } while (cin.fail() || hours < 1 || hours > 3);
                checker.markAttendance(isPresent, hours); // Pass both isPresent and hours arguments
                checker.saveAttendanceReport();
            }
        }
    }
}
#endif //OOP_NEW_PROJECT_FACULITYCHECKSTUDENT_H
