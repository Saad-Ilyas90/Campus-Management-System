//
// Created by basit on 12/23/2023.
//

#ifndef OOP_NEW_PROJECT_CHECKQUIZ_H
#define OOP_NEW_PROJECT_CHECKQUIZ_H
#include <fstream>
#include <iostream>
#include <windows.h>
#include <filesystem>
#include <shellapi.h>
namespace fs = std::filesystem;

using namespace std;

class CheckFacultyQuiz {
public:
    void checkFacultyQuiz(const string& facultyName) {
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
        cout << "Choose a course to check quizzes: ";
        while(!(cin >> choice) || choice < 1 || choice > numCourses) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and " << numCourses << ": ";
        }
        checkStudentsQuiz(courses[choice - 1]);
    }

    void checkStudentsQuiz(const string& courseCode) {
        for (const auto & entry : fs::directory_iterator(fs::current_path())) {
            if (entry.path().filename().string().find("_enrolledCourses.txt") != string::npos) {
                ifstream file(entry.path());
                string line;
                while (getline(file, line)) {
                    if (line.find("Course Code: " + courseCode) != string::npos) {
                        string enrollment = entry.path().filename().string().substr(0, entry.path().filename().string().find("_enrolledCourses.txt"));
                        checkQuiz(enrollment);
                    }
                }
            }
        }
    }

    void checkQuiz(const string& enrollment) {
        char buffer[MAX_PATH];
        GetModuleFileName(NULL, buffer, MAX_PATH);
        string::size_type pos = string(buffer).find_last_of("\\/");
        string quizPath = string(buffer).substr(0, pos) + "/" + enrollment + "_Quiz";

        // Check if the file exists with .txt, .pdf, .docx, .doc, .pptx, .ppt extension or no extension
        for (const auto &ext : {".txt", ".pdf", ".docx", ".doc", ".pptx", ".ppt", ""}) {
            std::fstream quizFile;
            quizFile.open(quizPath + ext, std::ios::in);

            if (quizFile.is_open()) {
                cout << "Quiz for " << enrollment << ":\n";
                quizFile.close();

                // Open the file in its default viewer
                ShellExecute(NULL, "open", (quizPath + ext).c_str(), NULL, NULL, SW_SHOW);

                return;
            }
        }

        cout << "No quiz found for " << enrollment << ".\n";
    }
};

#endif //OOP_NEW_PROJECT_CHECKQUIZ_H