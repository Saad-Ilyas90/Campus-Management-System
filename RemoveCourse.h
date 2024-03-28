//
// Created by basit on 12/10/2023.
//

#ifndef OOP_NEW_PROJECT_REMOVECOURSE_H
#define OOP_NEW_PROJECT_REMOVECOURSE_H

#endif //OOP_NEW_PROJECT_REMOVECOURSE_H
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstring>

using namespace std;

class Course1 {
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

void removeCourse() {
    string courseCode;
    ifstream file;
    Course1 course;
    bool found = false; // Flag to indicate if a course was found
    cin.ignore();

    while (!found) { // Loop until a valid course is found
        cout << "Enter the code of the course to be removed: ";
        getline(cin, courseCode);

        // If the input string is empty, continue with the next iteration of the loop
        if (courseCode.empty()) {
            continue;
        }

        file.open("course_" + courseCode + ".txt");

        if (!file.is_open()) {
            cout << "No course found with the code " << courseCode << "\n";
        } else {
            found = true; // Set the flag to true as the course is found
            string line;
            getline(file, line);
            course.setCourseName(line.substr(line.find(": ") + 2));
            getline(file, line);
            course.setCourseCode(line.substr(line.find(": ") + 2));
            getline(file, line);
            course.setCreditHours(stoi(line.substr(line.find(": ") + 2)));
            // Skip the rest of the lines or extract additional fields if needed

            break; // Break out of the loop since the profile is found
        }

        file.close(); // Close the file after processing or if not found
    }

    // Display course details only if a profile was found
    if (found) {
        cout << "Course Name: " << course.getCourseName() << "\n";
        cout << "Course Code: " << course.getCourseCode() << "\n";
        cout << "Credit Hours: " << course.getCreditHours() << "\n";
        file.close();
        // Display any additional fields you have in the course profile
        cout << "The above course will be removed. Press any key to continue...";
        cin.get(); // Wait for user input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        // Remove the course file
        int result = remove(("course_" + courseCode + ".txt").c_str());
        if (result != 0) {
            cout << "Error deleting file. Error code: " << strerror(errno) << endl;
        } else {
            cout << "Course removed successfully";
        }
    }
}