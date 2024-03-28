//
// Created by basit on 12/16/2023.
//

#ifndef OOP_NEW_PROJECT_STUDENTENROLLCOURSES_H
#define OOP_NEW_PROJECT_STUDENTENROLLCOURSES_H


#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
namespace fs = std::filesystem;
using namespace std;

class StudentEnrollCourses {
private:
    string enrollmentNumber;
    string courseCode;
    string enrolledCoursesFile;
    string courseCodes[100];
    int courseCount = 0;

public:

    int getCourseCount() {
        return courseCount;
    }

    string getCourseCode(int index) {
        return courseCodes[index];
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
    bool isCourseAlreadyEnrolled(const string& code) {
        ifstream file(enrolledCoursesFile);
        string line;
        while (getline(file, line)) {
            if (line.find("Course Code: " + code) != string::npos) {
               cout<<"Student "<<enrollmentNumber<<" is already enrolled in course "<<code<<"."<<endl;
                return true;
            }
        }
        return false;
    }

    bool isValidCourseCode() {
        string courseFile = "course_" + courseCode + ".txt";
        ifstream file(courseFile);
        return file.good();
    }
    string getAssignedFaculty() {
        string facultyName = "";
        for (const auto & entry : fs::directory_iterator(fs::current_path())) {
            if (entry.path().filename().string().find("_assignedCourses.txt") != string::npos) {
                ifstream file(entry.path());
                string line;
                bool foundFaculty = false;
                while (getline(file, line)) {
                    if (line.find("Faculty Name: ") != string::npos) {
                        size_t pos = line.find(": ");
                        if (pos != string::npos) {
                            facultyName = line.substr(pos + 2); // Extract the faculty name
                            foundFaculty = true;
                        }
                    }
                    if (foundFaculty && line.find("Course Code: " + courseCode) != string::npos) {
                        return facultyName; // Return the faculty name immediately when the course code is found
                    }
                }
            }
        }
        return ""; // Return an empty string if no faculty is found for the course
    }
    void enrollCourse() {
    if (!isValidCourseCode()) {
        cout << "Invalid course code." << endl;
        return;
    }

    if (isCourseAlreadyEnrolled(courseCode)) {
        cout << "Student " << enrollmentNumber << " is already enrolled in course " << courseCode << "." << endl;
        return;
    }

    string facultyName = getAssignedFaculty();
    if (facultyName.empty()) {
        cout << "No faculty assigned to course " << courseCode << "." << endl;
        return;
    }

    ofstream enrolledCourses(enrolledCoursesFile, ios::app);
    if (!enrolledCourses) {
        cout << "Failed to open file for writing: " << enrolledCoursesFile << endl;
        return;
    }
    enrolledCourses << "Enrollment Number: " << enrollmentNumber << "\n";
    enrolledCourses << "Course Code: " << courseCode << "\n";
    enrolledCourses << "Assigned Faculty: " << facultyName << "\n";
    enrolledCourses << "------------------------\n";

    cout << "Course enrolled successfully." << endl;
}

    void setEnrollmentNumber(const string& enrollment) {
        enrollmentNumber = enrollment;
        enrolledCoursesFile = enrollmentNumber + "_enrolledCourses.txt";
    }
    void setCourseCode(const string& code) {
        courseCode = code;
    }
};
void enrollCourses(const string& enrollment) {
    StudentEnrollCourses sec;
    sec.setEnrollmentNumber(enrollment);// Set the student name directly

    while (true) {
        try {
            int courseIndex;
            cin.ignore();
            sec.listAllCourses(); // List all courses before asking for course code

            cout << "Enter the number of the Course: ";
            cin >> courseIndex;
            if (courseIndex < 1 || courseIndex > sec.getCourseCount()) {
                cout << "Invalid input. Please try again." << endl;
                continue;
            }
            string courseCode = sec.getCourseCode(courseIndex - 1);
            sec.setCourseCode(courseCode);

            if (sec.isValidCourseCode() && !sec.isCourseAlreadyEnrolled(courseCode)) {
                sec.enrollCourse();
                break;
            } else {
                cout << "Invalid input. Please try again." << endl;
                continue;
            }
        } catch (const std::exception &e) {
            // Catch a general exception and print its message
            std::cerr << "An error occurred: " << e.what() << '\n';
            continue;
        }
    }
    system("pause");
    cout << "Press any key to continue...";
    cin.get();
}
#endif //OOP_NEW_PROJECT_STUDENTENROLLCOURSES_H