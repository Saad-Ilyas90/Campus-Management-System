//
// Created by basit on 12/9/2023.
//

#ifndef OOP_NEW_PROJECT_FACULTYMEMBER_H
#define OOP_NEW_PROJECT_FACULTYMEMBER_H
#include <iostream>
#include <string>
#include <fstream>
#include<filesystem>
#include"Person.h"
namespace fs = std::filesystem;
using namespace std;
class FacultyMember : public Person {
private:
    string title;
    string department;

public:
    // Default constructor
    FacultyMember() : Person("", "", "") {}

    // Getter and setter for title
    string getTitle() const {
        return title;
    }

    void setTitle(const string& title) {
        this->title = title;
    }

    // Getter and setter for department
    string getDepartment() const {
        return department;
    }

    void setDepartment(const string& department) {
        this->department = department;
    }

    // Setter and getter methods
    void setName(const string& name) {
        Person::setName(name);
    }

    void setFName(const string& fname) {
        Person::setFName(fname);
    }

    void setEmail(const string& email) {
        Person::setEmail(email);
    }

    string getFName() const {
        return Person::getFName();
    }

    // Override the printDetails method
    void printDetails() const override {
        cout << "Name: " << getName() << endl;
        cout << "Father's Name: " << getFName() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "Title: " << title << endl;
        cout << "Department: " << department << endl;
    }
};


class Adminn {
public:
    void assignFacultyCredentials(FacultyMember f, string filename) {
        // Open the file in append mode
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            // Generate username and password
            string username = f.getName() + "_" + f.getTitle();
            string password = to_string(rand()); // Generate a random password

            // Write the credentials to the file
            file << "Username: " << username << endl;
            file << "Password: " << password << endl;
            file << "User Type: Faculty Member" << endl;
            file << "------------------------\n";
        }
        file.close();
    }
};
void FacultyDetails() {
    Adminn admin;
    string name, fname, email, d, title;
    int numFaculty;
    FacultyMember f;
    while(true) {
        cout << "Enter number of faculty members to add" << endl;
        if (cin >> numFaculty) {
            if (numFaculty <= 0) {
                cout << "Number of Faculty should be a positive integer." << endl;
            } else {
                break;
            }
        } else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); // clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
        }
    }
    cin.ignore();
    while (true) {
        cout << "Enter department of students"<<endl;
        getline(cin, d);
        if (d.empty() || d.length() < 2) {
            cout << "Department name should not be empty and should be at least 2 characters long." << endl;
        } else {
            bool hasNonAlpha = false;
            for (int i = 0; i < d.length(); i++) {
                if (!isalpha(d[i]) && d[i] != ' ') {
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
    }
    FacultyMember *facultyMembers = new FacultyMember[numFaculty];
    for (int i = 0; i < numFaculty; i++) {
        cin.ignore();
                    do{
                        cout << "\nEnter Name of Faculty Member:" << " " << (i + 1) << endl;
                        getline(cin, name);
                        if (name.length() > 10 || name.length() < 3) {
                            cout << "\nName should be less than 10 characters and more than 3 characters";
                        } else if (name != "") {
                            bool hasNonAlpha = false;
                            for (int i = 0; i < name.length(); i++) {
                                if (!isalpha(name[i])&& name[i] != ' ') {
                                    hasNonAlpha = true;
                                    break;
                                }
                            }
                            if (hasNonAlpha) {
                                cout << "\nName should not contain numbers or special characters";
                            } else {
                                break;
                            }
                        } else {
                            cout << "\nName should not be empty";
                        }
                    } while (true);

                    do{
                        cout << "\nEnter Father's Name of Faculty Member:" << " " << (i + 1) << endl;
                        getline(cin, fname);
                        if (fname.length() > 10 || fname.length() < 3) {
                            cout << "\nFather's Name should be less than 10 characters and more than 3 characters";
                        } else if (fname != "") {
                            bool hasNonAlpha = false;
                            for (int i = 0; i < fname.length(); i++) {
                                if (!isalpha(fname[i])&& fname[i] != ' ') {
                                    hasNonAlpha = true;
                                    break;
                                }
                            }
                            if (hasNonAlpha) {
                                cout << "\nFather's Name should not contain numbers or special characters";
                            } else {
                                break;
                            }
                        } else {
                            cout << "\nFather's Name should not be empty";
                        }
                    } while (true);

            do {
                cout << "\nEnter Email of Faculty Member: " << (i + 1) << endl;
                getline(cin, email);
                regex email_regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
                if (!regex_match(email, email_regex)) {
                    cout << "Email should be valid";
                } else {
                    break;
                }
            } while (true);
            do {
                cout << "\nEnter Title of Faculty Member: " << (i + 1) << endl;
                getline(cin, title);
                if (title.empty()) {
                    cout << "\nTitle should not be empty";
                } else {
                    bool hasNonAlpha = false;
                    for (int i = 0; i < title.length(); i++) {
                        if (!isalpha(title[i])) {
                            hasNonAlpha = true;
                            break;
                        }
                    }
                    if (hasNonAlpha) {
                        cout << "Title should not contain numbers or special characters";
                    } else {
                        break;
                    }
                }
            } while (true);
            f.setName(name);
            f.setFName(fname);
            f.setEmail(email);
            f.setDepartment(d);
            f.setTitle(title);
            facultyMembers[i] = f;

            // Create a new file for each faculty member using their name
        // Create a new file for each faculty member using their name
        ofstream file;
        string baseFilename = "faculty_" + f.getName();
        string filename = baseFilename + ".txt";
        int count = 1;

// Check if a file with the same name already exists
        while (fs::exists(filename)) {
            // If it does, append a number to the end of the faculty member's name and check again
            filename = baseFilename + to_string(count++) + ".txt";
        }

        file.open(filename, ios::out); // Open the file in write mode

// Write faculty member details to file
        file << "Faculty Member " << "\n";
        file << "Name: " << f.getName() << "\n";
        file << "Father's Name: " << f.getFName() << "\n";
        file << "Email: " << f.getEmail() << "\n";
        file << "Department: " << f.getDepartment() << "\n";
        file << "Title: " << f.getTitle() << "\n";
        file << "------------------------\n";

        file.close();
            cout << "\nFaculty Member " << (i + 1) << " added successfully" << endl;

// Assign credentials to the faculty member
            admin.assignFacultyCredentials(f,filename);
            f.printDetails();
            system("pause");
            cout << "press any key to continue";
            // Generate username and password

        }

    delete[] facultyMembers;

}


#endif //OOP_NEW_PROJECT_FACULTYMEMBER_H
