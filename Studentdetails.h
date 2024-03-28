    //
    // Created by basit on 12/9/2023.
    //

    #ifndef OOP_NEW_PROJECT_STUDENTDETAILS_H
    #define OOP_NEW_PROJECT_STUDENTDETAILS_H


    #include<iostream>
    #include <string>
    #include <iomanip>
    #include <regex>
    #include<fstream>
    #include <sstream>
    #include <limits>
    #include"Person.h"

    using namespace std;
    class StudentProfile: public Person {
    private:
        string Fname;
        string department;
        char gender;
        int semester;

    public:
        // Default constructor
        StudentProfile() : Person("", "", "") {}

        // Parameterized constructor

        // Setter methods
        void setName(const string& name) {
            this->name = name;
        }

        void setEmail(const string& email) {
            this->email = email;
        }

        void setID(const string& id) {
            this->id = id;
        }

        void setFName(const string& fname) {
            this->Fname = fname;
        }

        void setGender(char gender) {
            this->gender = gender;
        }

        void setDepartment(const string& department) {
            this->department = department;
        }

        void setSemester(int semester) {
            this->semester = semester;
        }

        // Getter methods
        string getName() const {
            return this->name;
        }

        string getFName() const {
            return this->Fname;
        }

        char getGender() const {
            return this->gender;
        }

        string getDepartment() const {
            return this->department;
        }

        int getSemester() const {
            return this->semester;
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

        // Implement the printDetails method
        void printDetails() const override {
            cout << "Name: " << name << endl;
            cout << "Email: " << email << endl;
            cout << "ID: " << id << endl;
            cout << "Father's Name: " << Fname << endl;
            cout << "Department: " << department << endl;
            cout << "Gender: " << gender << endl;
            cout << "Semester: " << semester << endl;
        }

        // Rest of your code
    };
    class Admin {
        public:
            void assignCredentials(string username, string password, string userType, string id) {
                // Generate the filename based on the student's ID
                string filename = "student_" + id + ".txt";
                // Open the file in append mode
                ofstream file(filename, ios::app);
                if (file.is_open()) {
                    // Write the credentials to the file
                    file << "Username: " << username << endl;
                    file << "Password: " << password << endl;
                    file << "User Type: " << userType << endl;
                    file << "------------------------\n";
                }
                file.close();
            }
        };
    void StudentDetails() {
        int numstudents;
        string name, fname, email, d;
        char gen;
        int sem;
        string enrollment;
        StudentProfile s;
        Admin admin;
        static int rollNumber = s.getLastRollNumber(d, sem);
        while (true) {
            cout << "Enter number of students to add"<<endl;
            if (cin >> numstudents) {
                if (numstudents <= 0) {
                    cout << "Number of students should be a positive integer." << endl;
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

        cin.ignore(); // Ignore the newline character left in the input buffer

        while (true) {
            cout << "Enter Semester of student"<<endl;
            if (!(cin >> sem)) {
                cout << "Semester should be a positive integer." << endl;
                cin.clear(); // clear the error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
            } else if (sem <= 0 || sem > 8) {
                cout << "Semester should be a positive integer and less than or equal to 8." << endl;
            } else {
                break;
            }
        }
        StudentProfile *students = new StudentProfile[numstudents];
        for (int i = 0; i < numstudents; i++) {
            cin.ignore();
            do {
                cout << "\nEnter Name of Student:" << " " << (i + 1) << endl;
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
                        cout << "Name should not contain numbers or special characters";
                    } else {
                        break;
                    }
                }
            } while (true);
            do {
                cout << "\nEnter Father Name of student: " << (i + 1) << endl;
                getline(cin, fname);
                if (fname.length() > 10 || fname.length() < 3) {
                    cout << "Father Name should be less than 10 characters and more than 3 characters";
                } else if (fname != "") {
                    bool hasNonAlpha = false;
                    for (int i = 0; i < fname.length(); i++) {
                        if (!isalpha(fname[i])&& fname[i] != ' ') {
                            hasNonAlpha = true;
                            break;
                        }
                    }
                    if (hasNonAlpha) {
                        cout << "Father Name should not contain numbers or special characters";
                    } else {
                        break;
                    }
                }
            } while (true);
            do {
                cout << "\nEnter Email of student: " << (i + 1) << endl;
                getline(cin, email);
                regex email_regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
                if (!regex_match(email, email_regex)) {
                    cout << "Email should be valid";
                } else {
                    break;
                }
            } while (true);
            do {
                cout << "\nEnter Gender of student : " << (i + 1) << endl;
                cin >> gen;
                if (gen != 'M' && gen != 'F') {
                    cout << "\nGender should be M(male) or F(female)";
                } else {
                    break;
                }
            } while (true);
            // Set the student's ID
            rollNumber = s.getLastRollNumber(d, sem) + 1; // Get the last roll number from the file and increment it
            string enrollment = "01-" + d + "-" + to_string(rollNumber);
            s.setLastRollNumber(rollNumber, d, sem);
    // Generate username and password
            s.setName(name);
            s.setFName(fname);
            s.setID(enrollment);
            s.setEmail(email);
            s.setGender(gen);
            s.setDepartment(d);
            s.setSemester(sem);
            students[i] = s;

            // Create a new file for each student using their ID
            ofstream file;

            string filename = "student_" + s.getID() + ".txt";
            file.open(filename, ios::out); // Open the file in write mode

            // Write student details to file
            file << "Student " << (i + 1) << "\n";
            file << "Name: " << s.getName() << "\n";
            file << "Father's Name: " << s.getFName() << "\n";
            file << "Email: " << s.getEmail() << "\n";
            file << "Gender: " << s.getGender() << "\n";
            file << "Department: " << s.getDepartment() << "\n";
            file << "Semester: " << s.getSemester() << "\n";
            file << "Enrollment: " << s.getID() << "\n";
            file << "------------------------\n";

            file.close();

// Generate username and password
            // Generate username and password
            string username = s.getName() + "_" + s.getID();
            string password = to_string(rand()); // Generate a random password

// Assign credentials to the student
            admin.assignCredentials(username, password, "Student", s.getID());
            s.printDetails();
            cout << "\nStudent " << (i + 1) << " added successfully" << endl;
            system("pause");
            cout<<"press any key to continue";

    // Assign credentials to the student

        }delete[] students;


        }
#endif //OOP_NEW_PROJECT_STUDENTDETAILS_H
