//
// Created by basit on 12/10/2023.
//

#ifndef OOP_NEW_PROJECT_UPDATESTUDENTPROFILE_H
#define OOP_NEW_PROJECT_UPDATESTUDENTPROFILE_H


#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include<filesystem>
#include"Person.h"

using namespace std;
class Student2 : public Person {
private:
    string enrollment;
    string department;
    int semester;
    string fatherName;
    char gender;
    string username;
    string password;
    string userType;

public:
    // Default constructor
    Student2() : Person("", "", "") {}
    string getEnrollment() {
        return enrollment;
    }
    string getDepartment() {
        return department;
    }
    void setEnrollment(string e) {
        enrollment = e;
    }
    void setDepartment(string d) {
        department = d;
    }
    int getSemester() {
        return semester;
    }
    void setSemester(int s) {
        semester = s;
    }
    string getFatherName() {
        return fatherName;
    }
    char getGender() {
        return gender;
    }
    void setFatherName(string fn) {
        fatherName = fn;
    }
    void setGender(char g) {
        gender = g;
    }
    void setPassword(string p) {
        password = p;
    }
    string getPassword() {
        return password;
    }
    string getUsername() {
        return username;
    }
    void setUsername(string u) {
        username = u;
    }
    string getUserType() {
        return userType;
    }
    void setUserType(string ut) {
        userType = ut;
    }
    void printDetails() const override {
        cout << "Name: " << name << endl;
        cout << "Father's Name: " << fatherName << endl;
        cout << "Email: " << email << endl;
        cout << "Gender: " << gender << endl;
        cout << "Department: " << department << endl;
        cout << "Semester: " << semester << endl;
        cout << "Enrollment: " << enrollment << endl;
        cout << "Username: " << username << endl;
        cout << "User Type: " << userType << endl;
    }
    int getLastRollNumber(string department, int semester) {
        ifstream file(department + "_semester_" + to_string(semester) + "_last_roll_number.txt");
        if (!file) {
            return 0;
        }
        int lastRollNumber;
        file >> lastRollNumber;
        file.close();
        return lastRollNumber;
    }

    void setLastRollNumber(int rollNumber, string department, int semester) {
        ofstream file(department + "_semester_" + to_string(semester) + "_last_roll_number.txt");
        file << rollNumber;
        file.close();
    }
    void renameRelatedFiles(const string& oldEnrollment, const string& newEnrollment) {
        for (const auto & entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
            string oldFileName = entry.path().filename().string();
            if (oldFileName.find(oldEnrollment) != string::npos) {
                string newFileName = oldFileName;
                size_t pos = newFileName.find(oldEnrollment);
                if (pos != string::npos) {
                    newFileName.replace(pos, oldEnrollment.length(), newEnrollment);
                    std::filesystem::rename(oldFileName, newFileName);
                }
            }
        }
    }
    void updateEnrollmentInEnrolledCourses(const string& oldEnrollment, const string& newEnrollment) {
        string enrolledCoursesFile = oldEnrollment + "_enrolledCourses.txt";
        string tempFile = "temp.txt";
        ifstream fileIn(enrolledCoursesFile);
        ofstream fileOut(tempFile);

        string line;
        while (getline(fileIn, line)) {
            size_t pos = line.find(oldEnrollment);
            if (pos != string::npos) {
                line.replace(pos, oldEnrollment.length(), newEnrollment);
            }
            fileOut << line << "\n";
        }

        fileIn.close();
        fileOut.close();

        // Delete the original file and rename the temporary file
        remove(enrolledCoursesFile.c_str());
        rename(tempFile.c_str(), enrolledCoursesFile.c_str());
    }
};


void updateStudentProfile() {
    string enrollment,newFatherName,newEmail;
    fstream file;
    Student2 student;
    bool found = false; // Flag to indicate if a student profile was found
    cin.ignore();
    while (!found) { // Loop until a valid student profile is found
        cout << "Enter the enrollment number of the student: ";
        getline(cin, enrollment);
        // If the input string is empty, continue with the next iteration of the loop
        if (enrollment.empty()) {
            continue;
        }
        file.open("student_" + enrollment + ".txt");

        if (!file.is_open()) {
            cout << "No student found with the enrollment number " << enrollment << "\n";
        } else {
            found = true; // Set the flag to true as the student profile is found
            string line;
            getline(file, line); // Skip the first line (Student 1)

            getline(file, line);
            size_t pos = line.find(": ");
            if (pos != string::npos && pos + 2 < line.size()) {
                student.setName(line.substr(pos + 2));
            }

            getline(file, line);
            pos = line.find(": ");
            if (pos != string::npos && pos + 2 < line.size()) {
                student.setFatherName(line.substr(pos + 2));
            }

            getline(file, line);
            pos = line.find(": ");
            if (pos != string::npos && pos + 2 < line.size()) {
                student.setEmail(line.substr(pos + 2));
            }

            getline(file, line);
            if (line.size() > 0) {
                student.setGender(line[0]);
            }

            getline(file, line);
            pos = line.find(": ");
            if (pos != string::npos && pos + 2 < line.size()) {
                student.setDepartment(line.substr(pos + 2));
            }

            getline(file, line);
            pos = line.find(": ");
            if (pos != string::npos && pos + 2 < line.size()) {
                student.setSemester(stoi(line.substr(pos + 2)));
            }

            getline(file, line);
            pos = line.find(": ");
            if (pos != string::npos && pos + 2 < line.size()) {
                student.setEnrollment(line.substr(pos + 2));
            }

            getline(file, line);
            pos = line.find(": ");
            if (pos != string::npos && pos + 2 < line.size()) {
                student.setPassword(line.substr(pos + 2));
            }

            getline(file, line);
            pos = line.find(": ");
            if (pos != string::npos && pos + 2 < line.size()) {
                student.setUsername(line.substr(pos + 2));
            }

// Skip the rest of the lines or extract additional fields if needed

            file.close(); // Close the file after processing
            break; // Break out of the loop since the profile is found

        }

        file.close(); // Close the file after processing or if not found
    }

    // Update student details only if a profile was found
    if (found) {
        string newName, newDepartment, newSemester, existingUserType,existinggender;

        int newSemesterInt;
        do {
            cout << "Enter new name: ";
            getline(cin, newName);
            if (newName.length() > 10 || newName.length() < 3) {
                cout << "\nName should be less than 10 characters and more than 3 characters";
            } else if (newName != "") {
                bool hasNonAlpha = false;
                for (int i = 0; i < newName.length(); i++) {
                    if (!isalpha(newName[i]) && newName[i] != ' ') {
                        hasNonAlpha = true;
                        break;
                    }
                }
                if (hasNonAlpha) {
                    cout << "Name should not contain numbers or special characters";
                } else {
                    break;
                }
            }
        } while (true);
        do {
            cout << "Enter new father's name: ";
            getline(cin, newFatherName);
            if (newFatherName.length() > 10 || newFatherName.length() < 3) {
                cout << "\nFather's name should be less than 10 characters and more than 3 characters";
            } else if (newFatherName != "") {
                bool hasNonAlpha = false;
                for (int i = 0; i < newFatherName.length(); i++) {
                    if (!isalpha(newFatherName[i]) && newFatherName[i] != ' ') {
                        hasNonAlpha = true;
                        break;
                    }
                }
                if (hasNonAlpha) {
                    cout << "Father's name should not contain numbers or special characters";
                } else {
                    break;
                }
            }
        } while (true);

        do {
            cout << "Enter new department: ";
            getline(cin, newDepartment);
            if (newDepartment.empty() || newDepartment.length() < 2) {
                cout << "Department name should not be empty and should be at least 2 characters long." << endl;
            } else {
                bool hasNonAlpha = false;
                for (int i = 0; i < newDepartment.length(); i++) {
                    if (!isalpha(newDepartment[i]) && newDepartment[i] != ' ') {
                        hasNonAlpha = true;
                        break;
                    }
                }
                if (hasNonAlpha) {
                    cout << "Department name should not contain numbers or special characters." << endl;
                } else {
                    break;
                }
            }
        } while (true);
        do {
            cout << "Enter new email: ";
            getline(cin, newEmail);
            regex email_regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
            if (!regex_match(newEmail, email_regex)) {
                cout << "Email should be valid";
            } else {
                break;
            }
        } while (true);

        while (true) {
            cout << "Enter new semester: ";
            if (!(cin >> newSemesterInt)) {
                cout << "Semester should be a positive integer." << endl;
                cin.clear(); // clear the error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
            } else if (newSemesterInt <= 0 || newSemesterInt > 8) {
                cout << "Semester should be a positive integer and less than or equal to 8." << endl;
            } else {
                break;
            }
        }
        newSemester = to_string(newSemesterInt);

        student.setName(newName);
        student.setDepartment(newDepartment);
        student.setSemester(stoi(newSemester));

        // Generate new enrollment number based on department
        // Get the last roll number for the department and semester
        int lastRollNumber = student.getLastRollNumber(student.getDepartment(), student.getSemester());

// Increment the roll number
        lastRollNumber++;

// Generate new enrollment number based on department and incremented roll number
        string newEnrollment = "01-" + student.getDepartment() + "-" + to_string(lastRollNumber);

// Set the new enrollment number
        student.setEnrollment(newEnrollment);

// Update the last roll number in the file
        student.setLastRollNumber(lastRollNumber, student.getDepartment(), student.getSemester());

        // Generate new username based on name and new enrollment
        string newUsername = student.getName() + "_" + newEnrollment;
        student.setUsername(newUsername);
        string newPassword = to_string(rand());

        student.setFatherName(newFatherName);
        student.setEmail(newEmail);
        student.setPassword(newPassword);
        char newGender;
            do {
                cout << "Enter new gender (M/F): ";
                cin >> newGender;
                if (newGender == 'M' || newGender == 'F') {
                    student.setGender(newGender);
                    break;
                } else {
                    cout << "Gender should be M(male) or F(female)";
                }
            } while (true);


        // If user type is empty, set it to 'Student'
        if (student.getUserType().empty()) {
            student.setUserType("Student");
        }

        string oldFileName = "student_" + enrollment + ".txt";
        string newFileName = "student_" + newEnrollment + ".txt";


// Write updated student details into the file
        file.open(oldFileName, ios::out | ios::trunc); // Open the file in write mode to overwrite it

// Write updated student details into the file
        file << "Student 1\n";
        file << "Name: " << student.getName() << "\n";
        file << "Father's Name: " << student.getFatherName() << "\n";
        file << "Email: " << student.getEmail() << "\n";
        file << "Gender: " << student.getGender() << "\n";
        file << "Department: " << student.getDepartment() << "\n";
        file << "Semester: " << student.getSemester() << "\n";
        file << "Enrollment: " << student.getEnrollment() << "\n";
        file << "------------------------\n";
        file << "Username: " << student.getUsername() << "\n";
        file << "Password: " << student.getPassword() << "\n";
        file << "User Type: " << student.getUserType() << "\n";
        file << "------------------------\n";

        file.close();
        // Rename the file
        if(rename(oldFileName.c_str(), newFileName.c_str()) != 0) {
            cout << "Error renaming file. Error code: " << strerror(errno) << endl;
        } else {
            cout << "\nStudent profile updated successfully" << endl;
            // Rename all related files
            student.updateEnrollmentInEnrolledCourses(enrollment, newEnrollment);
            student.renameRelatedFiles(enrollment, newEnrollment);
        }
        student.printDetails();
        cout << "Press any key to return to the main menu...";
        cin.get(); // Wait for user input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    }
}
#endif //OOP_NEW_PROJECT_UPDATESTUDENTPROFILE_H