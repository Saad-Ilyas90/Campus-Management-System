//
// Created by basit on 12/14/2023.
//

#ifndef OOP_NEW_PROJECT_ASSIGNCOURSES_H
#define OOP_NEW_PROJECT_ASSIGNCOURSES_H


#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

class AssignedCourses {
private:
    string facultyName;
    string courseCode;
    string facultyFile;
    string courseFile;
    string assignedCoursesFile;
    string courseCodes[100];
    int courseCount = 0;

public:

    int getCourseCount() {
        return courseCount;
    }

    string getCourseCode(int index) {
        return courseCodes[index];
    }
    bool isCourseAlreadyAssigned(const string& code) {
        for (const auto & entry : fs::directory_iterator(fs::current_path())) {
            // Only consider files that follow the pattern "FacultyName_assignedCourses.txt"
            if (entry.path().filename().string().find("_assignedCourses.txt") != string::npos) {
                ifstream file(entry.path());
                string line;
                while (getline(file, line)) {
                    if (line.find("Course Code: " + code) != string::npos) {
                        cout << "Course " << code << " is already assigned." << endl;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool isValidFacultyName() {
        ifstream file(facultyFile);
        return file.good();
    }

    bool isValidCourseCode() {
        ifstream file(courseFile);
        return file.good();
    }

    void setFacultyName(const string& name) {
        facultyName = name;
        facultyFile = "faculty_" + facultyName + ".txt";
    }

    void setCourseCode(const string& code) {
        courseCode = code;
        courseFile = "course_" + courseCode + ".txt";
    }
    void listAllCourses() {
        cout << "Available courses: " << endl;
        int index = 1;
        for (const auto & entry : fs::directory_iterator(fs::current_path())) {
            if (entry.path().filename().string().find("course_") != string::npos) {
                string courseName = entry.path().filename().string();
                courseName = courseName.substr(7, courseName.size() - 11); // Remove "course_" and ".txt"
                courseCodes[courseCount++] = courseName;
                cout << index++ << ". " << courseName << endl;
            }
        }
    }


    void assignCourse() {
        if (!isValidFacultyName()) {
            cout << "Invalid faculty name." << endl;
            return;
        }

        if (!isValidCourseCode()) {
            cout << "Invalid course code." << endl;
            return;
        }

        if (isCourseAlreadyAssigned(courseCode)) {
            cout << "Course " << courseCode << " is already assigned to another faculty." << endl;
            return;
        }

        assignedCoursesFile = facultyName + "_assignedCourses.txt";
        ofstream assignedCourses(assignedCoursesFile, ios::app);
        if (!assignedCourses) {
            cout << "Failed to open file for writing: " << assignedCoursesFile << endl;
            return;
        }
        assignedCourses << "Faculty Name: " << facultyName << "\n";
        assignedCourses << "Course Code: " << courseCode << "\n";
        assignedCourses << "------------------------\n";

        cout << "Course assigned successfully." << endl;
    }
};
void assignCourses()
{
    AssignedCourses ac;
    string facultyName;
    int courseIndex;
    while (true) {
        cin.ignore();
        cout << "Enter Faculty Name: ";
        getline(cin, facultyName);
        ac.setFacultyName(facultyName);

        ac.listAllCourses(); // List all courses before asking for course code

        cout << "Enter the number of the Course: ";
        cin >> courseIndex;
        if (courseIndex < 1 || courseIndex > ac.getCourseCount()) {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }
        string courseCode = ac.getCourseCode(courseIndex - 1);
        ac.setCourseCode(courseCode);

        if (ac.isValidFacultyName() && ac.isValidCourseCode() && !ac.isCourseAlreadyAssigned(courseCode)) {
            ac.assignCourse();
            break;
        } else {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }
    }
    cout << "Press any key to continue...";
    cin.get();  // This line will cause the program to wait for a key press
}
#endif //OOP_NEW_PROJECT_ASSIGNCOURSES_H