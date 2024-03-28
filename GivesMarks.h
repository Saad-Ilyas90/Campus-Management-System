//
// Created by basit on 12/17/2023.
//

#ifndef OOP_NEW_PROJECT_GIVESMARKS_H
#define OOP_NEW_PROJECT_GIVESMARKS_H
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include<regex>
namespace fs = std::filesystem;
using namespace std;
class GiveMarks {
private:
    string facultyName;
    string courseCode;
    string studentEnrollment;
    string marksFile;
    string courses[10]; // Assuming a faculty can teach a maximum of 10 courses
    string students[50]; // Assuming a course can have a maximum of 100 students

public:
    GiveMarks(const string &name) {
        facultyName = name;
    }

    void setCourseCode(const string &code) {
        if (code.empty() || code.length() != 4) { // Assuming a valid course code is 4 characters long
            throw invalid_argument("Invalid course code.");
        }
        courseCode = code;
    }

    void setStudentEnrollment(const string &enrollment) {
        if (enrollment.empty()) { // Check if the enrollment number is empty
            throw invalid_argument("Invalid student enrollment number.");
        }
        studentEnrollment = enrollment;
        marksFile = studentEnrollment + "_marks.txt";
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

    void getAssignedCourses() {
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

    void getEnrolledStudents() {
        int i = 0;
        for (const auto &entry: fs::directory_iterator(fs::current_path())) {
            if (entry.path().filename().string().find("_enrolledCourses.txt") != string::npos) {
                ifstream file(entry.path());
                string line;
                while (getline(file, line)) {
                    if (line.find("Course Code: " + courseCode) != string::npos) {
                        string studentEnrollment = entry.path().filename().string();
                        studentEnrollment = studentEnrollment.substr(0, studentEnrollment.find(
                                "_")); // Extract the enrollment number
                        students[i] = studentEnrollment;
                        i++;
                    }
                }
            }
        }
    }
    void chooseCourse() {
        getAssignedCourses();
        cout << "Courses assigned to " << facultyName << ":\n";
        int numCourses = 0;
        for (int i = 0; i < 10 && !courses[i].empty(); i++) {
            cout << i + 1 << ". " << courses[i] << "\n";
            numCourses++;
        }
        int choice;
        cout << "Choose a course to give marks: ";
        while(!(cin >> choice) || choice < 1 || choice > numCourses) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and " << numCourses << ": ";
        }
        try {
            setCourseCode(courses[choice - 1]);
        } catch (const invalid_argument& e) {
            cout << "An error occurred: " << e.what() << endl;
            return;
        }
        getEnrolledStudents();
        // Check if there are any students enrolled in the chosen course
        bool isAnyStudentEnrolled = false;
        for (int i = 0; i < 50 && !students[i].empty(); i++) {
            isAnyStudentEnrolled = true;
            break;
        }
        if (!isAnyStudentEnrolled) {
            throw runtime_error("No student is enrolled in the course " + courseCode);
        }
    }

    void chooseStudent() {
        cout << "Students enrolled in " << courseCode << ":\n";
        int numStudents = 0;
        for (int i = 0; i < 100 && !students[i].empty(); i++) {
            cout << i + 1 << ". " << students[i] << "\n";
            numStudents++;
        }
        int choice;
        cout << "Choose a student to give marks: ";
        while(!(cin >> choice) || choice < 1 || choice > numStudents) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and " << numStudents << ": ";
        }
        try {
            setStudentEnrollment(students[choice - 1]);
        } catch (const invalid_argument& e) {
            cout << "An error occurred: " << e.what() << endl;
            return;
        }
    }
    void giveMarks() {
        try {
            if (!isStudentEnrolled()) {
                cout << "Student " << studentEnrollment << " is not enrolled in course " << courseCode << ".\n";
                return;
            }

            if (!fs::exists(marksFile)) {
                ofstream createFile(marksFile);
                createFile.close();
            }

            ifstream file(marksFile);
            if (!file) {
                throw runtime_error("Failed to open file for reading: " + marksFile);
            }

            ofstream tempFile("temp.txt");
            if (!tempFile) {
                throw runtime_error("Failed to open temporary file for writing.");
            }

            string line;
            bool marksExist = false;
            while (getline(file, line)) {
                if (line.find("Course: " + courseCode) != string::npos) {
                    marksExist = true;
                    char choice;
                    do {
                        cout << "Marks for course " << courseCode << " already exist. Do you want to modify them? (y/n): ";
                        cin >> choice;
                        if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
                            cout << "Invalid input. Please enter 'y' or 'n'.\n";
                            continue;
                        }
                        break;
                    } while (true);

                    if (choice == 'y' || choice == 'Y') {
                        int newMarks;
                        do {
                            cout << "Enter new marks for student " << studentEnrollment << " in course " << courseCode<< ": ";
                            cin >> newMarks;
                            if (newMarks < 0 || newMarks > 100) {
                                cout << "Marks should be between 0 and 100. Please try again.\n";
                                continue;
                            }
                            tempFile << "Course: " + courseCode + ", Marks: " + to_string(newMarks) << "\n";
                            break;
                        } while (true);
                    } else {
                        tempFile << line << "\n";
                    }
                } else {
                    tempFile << line << "\n";
                }
            }

            if (!marksExist) {
                int newMarks;
                do {
                    cout << "Enter marks for student " << studentEnrollment << " in course " << courseCode << ": ";
                    cin >> newMarks;
                    if (newMarks < 0 || newMarks > 100) {
                        cout << "Marks should be between 0 and 100. Please try again.\n";
                        continue;
                    }
                    tempFile << "Course: " + courseCode + ", Marks: " + to_string(newMarks) << "\n";
                    break;
                } while (true);
            }

            file.close();
            tempFile.close();

            // Replace the original file with the temporary file
            fs::rename("temp.txt", marksFile);

            cout << "Marks given successfully.\n";

            // Recalculate and update the GPA
            calculateGPA();

        } catch (const exception &e) {
            cout << "An error occurred: " << e.what() << endl;
        }
    }
    void calculateGPA() {
        ifstream file(marksFile);
        if (!file) {
            cout << "No marks record found for student " << studentEnrollment << ".\n";
            return;
        }
        int totalCreditHours = 0;
        double totalGradePoints = 0;
        string line;
        ofstream tempFile("temp.txt");
        while (getline(file, line)) {
            if (line.find("Course: ") != string::npos) {
                string courseCode = line.substr(8, 4); // Extract the course code
                int marks = stoi(line.substr(line.find("Marks: ") + 7)); // Extract the marks

                // Read the credit hours from the course file
                ifstream courseFile("course_" + courseCode + ".txt");
                string courseLine;
                int creditHours = 0;
                while (getline(courseFile, courseLine)) {
                    if (courseLine.find("Credit Hours: ") != string::npos) {
                        creditHours = stoi(courseLine.substr(14)); // Extract the credit hours
                        break;
                    }
                }
                courseFile.close();

                double gradePoints;
                if (marks >= 85) {
                    gradePoints = 4.0;
                } else if (marks >= 80) {
                    gradePoints = 3.6;
                } else if (marks >= 75) {
                    gradePoints = 3.3;
                } else if (marks >= 71) {
                    gradePoints = 3;
                } else if (marks >= 68) {
                    gradePoints = 2.67;
                } else if (marks >= 64) {
                    gradePoints = 2.33;
                } else if (marks >= 60) {
                    gradePoints = 2;
                } else if (marks >= 57) {
                    gradePoints = 1.67;
                } else if(marks >= 53)  {
                    gradePoints = 1.33;
                } else if (marks >= 50) {
                    gradePoints = 1;
                } else  {
                    gradePoints = 0;
                }
                totalCreditHours += creditHours;
                totalGradePoints += gradePoints * creditHours;
                double gpa = gradePoints;
                tempFile << line.substr(0, line.find(", GPA: ")) << ", GPA: " << gpa << "\n";
            } else {
                tempFile << line << "\n";
            }
        }
        file.close();
        tempFile.close();
        // Replace the original file with the temporary file
        fs::rename("temp.txt", marksFile);

        if (totalCreditHours > 0) {
            double averageGPA = totalGradePoints / totalCreditHours;
            writeGPA(averageGPA);
        }
    }

    void writeGPA(double totalGPA) {
        ifstream fileIn(marksFile);
        if (!fileIn) {
            cout << "Failed to open file for reading: " << marksFile << "\n";
            return;
        }

        ofstream fileOut("temp.txt");
        if (!fileOut) {
            cout << "Failed to open temporary file for writing.\n";
            return;
        }

        string line;
        while (getline(fileIn, line)) {
            if (line.find("Total GPA: ") == string::npos) {
                fileOut << line << "\n";
            }
        }

        fileIn.close();
        fileOut.close();

        // Replace the original file with the temporary file
        fs::rename("temp.txt", marksFile);

        ofstream file(marksFile, ios::app); // Open the file in append mode
        if (!file) {
            cout << "Failed to open file for writing: " << marksFile << "\n";
            return;
        }
        file << "Total GPA: " << totalGPA << "\n";
        cout << "GPA written successfully.\n";
        file.close();
    }
};
void giveMarksToStudent(const string& facultyName) {
    GiveMarks gm(facultyName);
    try {
        gm.chooseCourse();
    } catch (const runtime_error& e) {
        cout << "An error occurred: " << e.what() << endl;
        return;
    }
    while (true) {
        gm.chooseStudent();
        gm.giveMarks();

        char choice;
        cout << "Do you want to give marks to another student? (y/n): ";
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
            break;
        }
    }
}
#endif //OOP_NEW_PROJECT_GIVESMARKS_H
