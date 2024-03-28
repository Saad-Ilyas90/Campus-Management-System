//
// Created by basit on 12/23/2023.
//

#ifndef OOP_NEW_PROJECT_CHECKASSIGMENT_H
#define OOP_NEW_PROJECT_CHECKASSIGMENT_H
#include <fstream>
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

class CheckFacultyAssignment {
public:
    void checkFacultyAssignment(const string& facultyName) {
        getAssignedCourses(facultyName);
        chooseCourse();
    }

private:
    string courses[10]; // Assuming a faculty can teach a maximum of 10 courses

    void getAssignedCourses(const string& facultyName) {
        ifstream file(facultyName + "_assignedCourses.txt");
        string line;
        int i = 0;
        while (getline(file, line)) {
            if (line.find("Course Code: ") != string::npos) {
                courses[i] = line.substr(13); // Extract the course code
                i++;
            }
        }
    }

    void chooseCourse() {
        cout << "Courses assigned to faculty:\n";
        int numCourses = 0;
        for (int i = 0; i < 10 && !courses[i].empty(); i++) {
            cout << i + 1 << ". " << courses[i] << "\n";
            numCourses++;
        }
        int choice;
        cout << "Choose a course to check assignments: ";
        while(!(cin >> choice) || choice < 1 || choice > numCourses) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and " << numCourses << ": ";
        }
        checkStudentsAssignment(courses[choice - 1]);
    }

    void checkStudentsAssignment(const string& courseCode) {
        for (const auto & entry : fs::directory_iterator(fs::current_path())) {
            if (entry.path().filename().string().find("_enrolledCourses.txt") != string::npos) {
                ifstream file(entry.path());
                string line;
                while (getline(file, line)) {
                    if (line.find("Course Code: " + courseCode) != string::npos) {
                        string enrollment = entry.path().filename().string().substr(0, entry.path().filename().string().find("_enrolledCourses.txt"));
                        checkAssignment(enrollment);
                    }
                }
            }
        }
    }

    void checkAssignment(const string& enrollment) {
        char buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, MAX_PATH);
        string::size_type pos = string(buffer).find_last_of("\\/");
        string assignmentPath = string(buffer).substr(0, pos) + "/" + enrollment + "_Assignment";

        // Check if the file exists with .txt, .pdf, .docx, .doc, .pptx, .ppt extension or no extension
        for (const auto &ext : {".txt", ".pdf", ".docx", ".doc", ".pptx", ".ppt", ""}) {
            std::fstream assignmentFile;
            assignmentFile.open(assignmentPath + ext, std::ios::in);

            if (assignmentFile.is_open()) {
                cout << "Assignment for " << enrollment << ":\n";
                assignmentFile.close();

                // Open the file in its default viewer
                ShellExecute(NULL, "open", (assignmentPath + ext).c_str(), NULL, NULL, SW_SHOW);

                return;
            }
        }

        cout << "No assignment found for " << enrollment << ".\n";
    }
};

#endif //OOP_NEW_PROJECT_CHECKASSIGMENT_H