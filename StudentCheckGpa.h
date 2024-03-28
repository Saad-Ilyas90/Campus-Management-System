//
// Created by basit on 12/17/2023.
//

#ifndef OOP_NEW_PROJECT_STUDENTCHECKGPA_H
#define OOP_NEW_PROJECT_STUDENTCHECKGPA_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Courses {
    string courseCode;
    int marks;
    double gpa;

};

class StudentCheckGPA {
private:
    string enrollmentNumber;
    string gpaFile;
    Courses courses[10]; // Assuming a student can enroll in a maximum of 10 courses
    int courseCount;
    double totalGPA; // Declare totalGPA as a member variable

public:
    void setEnrollmentNumber(const string& enrollment) {
        enrollmentNumber = enrollment;
        gpaFile = enrollmentNumber + "_marks.txt";
        courseCount = 0;
        totalGPA = 0.0; // Initialize totalGPA to 0.0
    }


    void getEnrolledCourses() {
        ifstream file(enrollmentNumber + "_enrolledCourses.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("Course Code: ") != string::npos) {
                courses[courseCount].courseCode = line.substr(13); // Extract the course code
                courses[courseCount].marks = -1; // Initialize marks to -1 indicating not assigned
                courses[courseCount].gpa = -1.0; // Initialize gpa to -1.0 indicating not assigned
                courseCount++;
            }
        }
    }
    void getCourseMarksAndGPA() {
        ifstream file(gpaFile);
        string line;
        while (getline(file, line)) {
            if (line.find("Course: ") != string::npos) {
                string courseCode = line.substr(8, 4); // Extract the course code
                int marks = stoi(line.substr(line.find("Marks: ") + 7)); // Extract the marks
                double gpa = stod(line.substr(line.find("GPA: ") + 5)); // Extract the GPA
                for (int i = 0; i < courseCount; i++) {
                    if (courses[i].courseCode == courseCode) {
                        courses[i].marks = marks;
                        courses[i].gpa = gpa;
                        break;
                    }
                }
            } else if (line.find("Total GPA: ") != string::npos) {
                totalGPA = stod(line.substr(11)); // Extract the total GPA
            }
        }
    }
    void printCourseResults() {
        getEnrolledCourses();
        getCourseMarksAndGPA();
        for (int i = 0; i < courseCount; i++) {
            cout << "Course: " << courses[i].courseCode;
            if (courses[i].marks >= 0) {
                cout << ", Marks: " << courses[i].marks;
            } else {
                cout << ", Marks: Not assigned";
            }
            if (courses[i].gpa >= 0) {
                cout << ", GPA: " << courses[i].gpa;
            } else {
                cout << ", GPA: Not calculated";
            }
            cout << "\n";
        }
        cout << "Total GPA: " << totalGPA << "\n";
    }
};


#endif //OOP_NEW_PROJECT_STUDENTCHECKGPA_H