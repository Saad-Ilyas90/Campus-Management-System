//
// Created by basit on 12/10/2023.
//

#ifndef OOP_NEW_PROJECT_ADDCOURSE_H
#define OOP_NEW_PROJECT_ADDCOURSE_H

#endif //OOP_NEW_PROJECT_ADDCOURSE_H
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include<filesystem>

using namespace std;

class Course {
private:
    string courseName;
    string courseCode;
    int creditHours;
public:
    string getCourseName() {
        return courseName;
    }

    string getCourseCode() {
        return courseCode;
    }

    int getCreditHours() {
        return creditHours;
    }

    void setCourseName(string cn) {
        courseName = cn;
    }

    void setCourseCode(string cc) {
        courseCode = cc;
    }

    void setCreditHours(int ch) {
        creditHours = ch;
    }
};

void addCourse() {
    string courseName, courseCode;
    int creditHours;

    do {
        cout << "\nEnter Course Name: ";
        if (cin.peek() == '\n') {
            cin.ignore(); // Ignore the newline character in the input buffer
        }
        getline(cin, courseName);
        if (courseName.empty() || courseName.length() < 3) {
            cout << "\nCourse name should not be empty and greater than 3." << endl;
        } else if (any_of(courseName.begin(), courseName.end(), ::isdigit)) {
            cout << "\nCourse name should not contain numbers." << endl;
        } else {
            bool hasNonAlpha = false;
            for (int i = 0; i < courseName.length(); i++) {
                if (!isalpha(courseName[i])&& courseName[i] != ' ') {
                    hasNonAlpha = true;
                    break;
                }
            }
            if (hasNonAlpha) {
                cout << "\nCourse name should not contain special characters";
            } else {
                break;
            }
        }
    } while (true);
    cin.ignore();

    do {
        cout << "Enter Course Code: ";
        getline(cin, courseCode);
        if (courseCode.empty()) {
            cout << "Course code should not be empty." << endl;
        } else {
            bool hasSpecialChar = false;
            for (int i = 0; i < courseCode.length(); i++) {
                if (!isalnum(courseCode[i])) {
                    hasSpecialChar = true;
                    break;
                }
            }
            if (hasSpecialChar) {
                cout << "Course code should not contain special characters";
            } else {
                break;
            }
        }
    } while (true);

    do {
        cout << "Enter Credit Hours: ";
        if (!(cin >> creditHours)) {
            cout << "Credit hours should be a number." << endl;
            cin.clear(); // clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
        } else if (creditHours <= 0||creditHours>3) {
            cout << "Credit hours should be a positive integer and should not be greater than 3." << endl;
        } else {
            break;
        }
    } while (true);

    Course course;
    course.setCourseName(courseName);
    course.setCourseCode(courseCode);
    course.setCreditHours(creditHours);

    string filename = "course_" + course.getCourseCode() + ".txt";

    // Check if a file with the same name already exists
    if (std::filesystem::exists(filename)) {
        cout << "\nA course with the same code already exists." << endl;
        return;
    }

    ofstream file;
    file.open(filename, ios::out);

    file << "Course Name: " << course.getCourseName() << "\n";
    file << "Course Code: " << course.getCourseCode() << "\n";
    file << "Credit Hours: " << course.getCreditHours() << "\n";
    file << "------------------------\n";

    file.close();

    cout << "\nCourse added successfully" << endl;

}