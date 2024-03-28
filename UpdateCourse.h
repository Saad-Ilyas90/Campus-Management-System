//
// Created by basit on 12/13/2023.
//

#ifndef OOP_NEW_PROJECT_UPDATECOURSE_H
#define OOP_NEW_PROJECT_UPDATECOURSE_H


#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include<filesystem>
using namespace std;
class Course2 {
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
void updateCourse() {
    string courseCode;
    fstream file;
    Course2 course;
    string newCourseCode;
    bool found = false; // Flag to indicate if a course file was found
    cin.ignore();

    while (!found) { // Loop until a valid course file is found
        cout << "Enter the course code: ";
        getline(cin, courseCode);

        // If the input string is empty, continue with the next iteration of the loop
        if (courseCode.empty()) {
            continue;
        }

        file.open("course_" + courseCode + ".txt");

        if (!file.is_open()) {
            cout << "No course found with the code " << courseCode << "\n";
        } else {
            found = true; // Set the flag to true as the course file is found
            string line;
            getline(file, line);
            course.setCourseName(line.substr(line.find(": ") + 2));
            getline(file, line);
            course.setCourseCode(line.substr(line.find(": ") + 2));
            getline(file, line);
            course.setCreditHours(stoi(line.substr(line.find(": ") + 2)));
            // Skip the rest of the lines or extract additional fields if needed

            file.close(); // Close the file after processing
            break; // Break out of the loop since the course file is found
        }

        file.close(); // Close the file after processing or if not found
    }

    // Update course details only if a course file was found
    if (found) {
        string newCourseName;
        int newCreditHours;

        do {
            cout << "Enter new course code: ";
            getline(cin, newCourseCode);
            if (newCourseCode.empty()) {
                cout << "Course code should not be empty." << endl;
            } else {
                bool hasSpecialChar = false;
                for (int i = 0; i < newCourseCode.length(); i++) {
                    if (!isalnum(newCourseCode[i])) {
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
        course.setCourseCode(newCourseCode);
        do {
            cout << "Enter new course name: ";
            getline(cin, newCourseName);
            if (newCourseName.empty() || newCourseName.length() < 3) {
                cout << "\nCourse name should not be empty and greater than 3." << endl;
            } else if (any_of(newCourseName.begin(), newCourseName.end(), ::isdigit)) {
                cout << "\nCourse name should not contain numbers." << endl;
            } else {
                bool hasNonAlpha = false;
                for (int i = 0; i < newCourseName.length(); i++) {
                    if (!isalpha(newCourseName[i])&& newCourseName[i] != ' ') {
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
        course.setCourseCode(newCourseCode);
        do {
            cout << "Enter new credit hours: ";
            if (!(cin >> newCreditHours)) {
                cout << "Credit hours should be a number." << endl;
                cin.clear(); // clear the error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
            } else if (newCreditHours <= 0 || newCreditHours > 3) {
                cout << "Credit hours should be a positive integer and should not be greater than 3." << endl;
            } else {
                break;
            }
        } while (true);

        course.setCourseName(newCourseName);
        course.setCreditHours(newCreditHours);
        if (std::filesystem::exists("course_" + newCourseCode + ".txt")) {
            cout << "\nA course with the same code already exists." << endl;
            return;
        }
        string oldFileName = "course_" + courseCode + ".txt";
        string newFileName = "course_" + course.getCourseCode() + ".txt";

        file.open(oldFileName, ios::out | ios::trunc); // Open the file in write mode to overwrite it

        file << "Course Name: " << course.getCourseName() << "\n";
        file << "Course Code: " << course.getCourseCode() << "\n";
        file << "Credit Hours: " << course.getCreditHours() << "\n";
        file << "------------------------\n";
        file.close();

        if (rename(oldFileName.c_str(), newFileName.c_str()) != 0) {
            cout << "Error renaming file. Error code: " << strerror(errno) << endl;
        } else {
            cout << "\nCourse updated successfully" << endl;
        }
    }
}
#endif //OOP_NEW_PROJECT_UPDATECOURSE_H