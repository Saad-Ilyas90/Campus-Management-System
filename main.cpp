    #include <iostream>
    #include <windows.h>
    #include <conio.h>
    #include <string>
    #include"Studentdetails.h"
    #include"FacultyMember.h"
    #include "StaffMember.h"
    #include "AddCourse.h"
    #include"CheckStudentProfile.h"
    #include"FacuityMemberCheck.h"
    #include"RemoveStudent.h"
    #include"StaffMemeberCheck.h"
    #include"RemoveFaculity.h"
    #include"RemoveStaff.h"
    #include"RemoveCourse.h"
    #include"UpdateStudentProfile.h"
    #include"UpdateFaculity.h"
    #include"UpdateStaff.h"
    #include"UpdateCourse.h"
    #include"AssignCourses.h"
    #include"LoginStudent.h"
    #include"StudentUpdateUsernamePassword.h"
    #include"StudentEnrollCourses.h"
    #include"UploadAssigment.h"
    #include"UploadQuiz.h"
    #include"StudentCheckAttendence.h"
    #include"StudentCheckGpa.h"
    #include"FaculityLogin.h"
    #include"FaculityUpdateUsernamePassword.h"
    #include"FaculityCheckCourses.h"
    #include"FaculityCheckStudent.h"
    #include"GivesMarks.h"
    #include"CheckQuiz.h"
    #include"CheckAssigment.h"
    #include"AdminCheckStudent.h"


    #define FOREGROUND_BLUE      0x0001 // text color contains blue.
    #define FOREGROUND_GREEN     0x0002 // text color contains green.
    #define FOREGROUND_RED       0x0004 // text color contains red.
    #define FOREGROUND_INTENSITY 0x0008 // text color is intensified.
    using namespace std;
    class Login{
    private:
        string username;
        string password;
    public:
        //  method to check admin login
        bool checkAdminLogin(string username, string password) {
            ifstream file("admin_credentials.txt");
            string fileUsername, filePassword;
            if (file.is_open()) {
                getline(file, fileUsername);
                getline(file, filePassword);
            }
            file.close();
            return (username == fileUsername && password == filePassword);
        }
        string getPassword() {
            string password;
            char ch;
            while ((ch = _getch()) != '\r') { // '\r' is the Enter key
                if (ch == '\b') { // '\b' is the Backspace key
                    if (!password.empty()) {
                        cout << "\b \b"; // erase the last '*'
                        password.pop_back();
                    }
                } else {
                    cout << '*';
                    password.push_back(ch);
                }
            }
            cout << endl;
            return password;
        }
    };
    void printCenteredSlowly(string text, int delay) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int consoleWidth;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Set the text color to red
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

        // Retrieve the console width inside the function
        if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            // An error occurred
            cout << text << endl;
        } else {
            consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left;
            int padding = (consoleWidth - text.length()) / 2;
            string paddedText = string(padding, ' ') + text;
            for (char c : paddedText) {
                cout << c;
                Sleep(delay);
            }
            cout << endl;
        }
        // Reset the text color to white
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    void printCentered(const std::string& text, char borderChar = '*') {
        using namespace std;
        int length = text.length();
        int boxWidth = max(30, length + 4); // Set a minimum box width
        string border(boxWidth, borderChar);

        // Retrieve the console width
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int consoleWidth;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            // An error occurred
            consoleWidth = boxWidth; // Use the box width as a fallback
        } else {
            consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left;
        }

        // Calculate the padding needed to center the box within the console
        int consolePadding = max(0, (consoleWidth - boxWidth) / 2);

        // Print the box with the text centered within it
        cout << string(consolePadding, ' ') << border << endl;
        int padding = (boxWidth - length - 4) / 2;
        cout << string(consolePadding, ' ') << borderChar << setw(padding) << " " << text << setw(boxWidth - padding - length - 2) << " " << borderChar << endl;
        cout << string(consolePadding, ' ') << border << endl;
    }
    int main() {
        int choice,choice2,choice4=0;
        Login admin;
        string username, password;
        printCenteredSlowly(" Welcome to Campus Management System", 100);
        system("cls");
        while(true) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printCentered("Press 1 to login as Admin");
            printCentered("Press 2 to login as Student");
            printCentered("Press 3 to login as Faculty Member");
            printCentered("Press 0 to exit");
            cout<<"Enter your choice: ";
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); // clear the error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
                cout << "\nInvalid input. Please enter a number." << endl;
                continue;
            }
            if(choice==0){
                system("cls");
                cout<<"Exiting"<<endl;
                break;
            }
            else
            if (choice == 1) {
                system("cls");
                cout << "Admin" << endl;
                int loginAttempts = 0;
                bool loginSuccess = false;
                do {
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    password = admin.getPassword();
                    if (admin.checkAdminLogin(username, password)) {
                        cout << "Access granted." << endl;
                        loginSuccess = true;
                        break;
                    } else {
                        cout << "Access denied." << endl;
                        loginAttempts++;
                        if (loginAttempts >= 3) {
                            cout << "Maximum login attempts reached." << endl;
                            break;
                        }
                    }
                } while (true);
                if (!loginSuccess) {
                    cout << "Exiting due to failed login attempts." << endl;
                    system("pause");
                    return 0;
                }
                while(true) {
                    system("cls");
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    // Set the color for the menu options and the prompt
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printCentered("Press 1 to add student");
                    printCentered("Press 2 to add faculty member");
                    printCentered("Press 3 to add staff member");
                    printCentered("Press 4 to add course");
                    printCentered("Press 5 to check student profile");
                    printCentered("Press 6 to check faculty member profile");
                    printCentered("Press 7 to check staff member profile");
                    printCentered("Press 8 to remove student");
                    printCentered("Press 9 to remove faculty member");
                    printCentered("Press 10 to remove staff member");
                    printCentered("Press 11 to remove course");
                    printCentered("Press 12 to update student profile");
                    printCentered("Press 13 to update faculty member profile");
                    printCentered("Press 14 to update staff member profile");
                    printCentered("Press 15 to update course");
                    printCentered("Press 16 to assign courses");
                    printCentered("Press 17 to check student");
                    printCentered("Press 18 to logout");
                    printCentered("Press 0 to exit");
                    cout<<"Enter your choice: ";
                    cin >> choice2;
                    if (cin.fail()) {
                        cout << "\nInvalid input. Please enter a number." << endl;
                        cin.clear(); // clear the error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
                        continue;
                    }
                    if(choice2==0){
                        system("cls");
                        cout<<"Exiting"<<endl;
                        break;
                    }
                    else
                    if (choice2 == 1) {
                        {
                            system("cls");
                            StudentDetails();
                        }
                    }
                    else if (choice2 == 2)
                    {
                        system("cls");
                        FacultyDetails();
                    }
                    else if (choice2 == 3) {
                        system("cls");
                        StaffDetails();
                    } else if (choice2 == 4) {
                        system("cls");
                        addCourse();
                        system("pause");
                    } else if (choice2 == 5) {
                        system("cls");
                        checkStudentProfile();
                    } else if (choice2 == 6) {
                        system("cls");
                        checkFacultyMemberProfile();
                    } else if (choice2 == 7) {
                        system("cls");
                        checkStaffMemberProfile();
                    } else if (choice2 == 8) {
                        system("cls");
                        removeStudent();
                    } else if (choice2 == 9) {
                        system("cls");
                         removeFaculty();
                    } else if (choice2 == 10) {
                        system("cls");
                        removeStaff();
                    } else if (choice2 == 11) {
                        system("cls");
                        removeCourse();
                    } else if (choice2 == 12) {
                        system("cls");
                        updateStudentProfile();
                    } else if (choice2 == 13) {
                        system("cls");
                        updateFacultyProfile();
                    } else if (choice2 == 14) {
                        system("cls");
                        updateStaffProfile();
                    } else if (choice2 == 15) {
                        system("cls");
                        updateCourse();
                        system("pause");
                    }
                    else if (choice2 == 16) {
                        system("cls");
                        assignCourses();
                        system("pause");
                    }
                    else if (choice2 == 17) {
                        system("cls");
                        adminStudentCheck();
                        system("pause");
                    }
                    else if (choice2 == 18) {
                        system("cls");
                        break; // Reset choice to non-zero value
                    } else {
                        cout << "Invalid Choice" << endl;
                    }
                }
            }
            else if (choice==2) {
        system("cls");
        string enrollment = StudentLoginn();
        if (enrollment.empty()) {
            cout << "Login failed. Please try again." << endl;
            continue;
        }
        system("pause");
        cin.get();
        int choice3 = 0;
        while(true)
        {
            system("cls");
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
// Set the color for the menu options and the prompt to yellow
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            printCentered("Press 1 to update your username and password");
            printCentered("Press 2 to enroll courses");
            printCentered("Press 3 to upload assignment");
            printCentered("Press 4 to upload quiz");
            printCentered("Press 5 to check GPA");
            printCentered("Press 6 to check attendance and marks");
            printCentered("Press 7 to logout");
            printCentered("Press 0 to exit");
            cout<<"Enter your choice: ";
            cin >> choice3;
            if (cin.fail()) {
                cout << "\nInvalid input. Please enter a number." << endl;
                cin.clear(); // clear the error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
                continue;
            }
            if(choice3==0){
                system("cls");
                cout<<"Exiting"<<endl;
                break;
            }
            else
            if(choice3==1){
                system("cls");
                updateStudentUsernamePassword(enrollment);

            }
            else if(choice3==2){
                system("cls");
                enrollCourses(enrollment);
            }
            else if(choice3==3){
                system("cls");
                UploadAssignment uploader;
                uploader.uploadFile(enrollment);
            }
            else if(choice3==4){
                system("cls");
                UploadQuiz uploader;
                uploader.uploadQuiz(enrollment);
            }
            else if(choice3==5){
                system("cls");
                StudentCheckGPA checker;
                checker.setEnrollmentNumber(enrollment);
                checker.printCourseResults();
                system("pause");
            }
            else if(choice3==6){
                system("cls");
                StudentCheckAttendance checker(enrollment);
                checker.getAttendanceReport();
                system("pause");
            }
            else if(choice3==7){
                system("cls");
                break;
            }
            else{
                cout<<"Invalid Choice"<<endl;
            }
        }
    }
            else if (choice==3) {
                system("cls");
                cout<<"Faculty Member"<<endl;
                string facultyName = FacultyLoginn();
                if (facultyName.empty()) {
                    cout << "Login failed. Please try again." << endl;
                    continue;

                }system("pause");
                cin.get();
                while(true)
                {
                    system("cls");
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
// Set the color for the menu options and the prompt to silver
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    printCentered("Press 1 to update your username and password");
                    printCentered("Press 2 to check courses");
                    printCentered("Press 3 to mark student");
                    printCentered("Press 4 to give marks to student or modify marks");
                    printCentered("Press 5 to check quiz");
                    printCentered("Press 6 to check assignment");
                    printCentered("Press 7 to logout");
                    printCentered("Press 0 to exit");
                    cout<<"Enter your choice: ";
                    cin>>choice4;
                    if (cin.fail()) {
                        cout << "\nInvalid input. Please enter a number." << endl;
                        cin.clear(); // clear the error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the rest of the line
                        continue;
                    }
                    if(choice4==0){
                        system("cls");
                        cout<<"Exiting"<<endl;
                        break;
                    }
                    else
                    if(choice4==1){
                        system("cls");
                        updateFacultyUsernamePassword(facultyName);
                    }
                    else if(choice4==2){
                        system("cls");
                        checkCourses(facultyName);
                        system("pause");
                    }
                    else if(choice4==3){
                        system("cls");
                        FacultyCheckStudent checker(facultyName);
                        FacultyCheckStudentFunction(checker);
                        system("pause");

                    }
                    else if(choice4==4){
                        system("cls");
                        giveMarksToStudent(facultyName);
                        system("pause");

                    }
                    else if(choice4==5){
                        system("cls");
                        CheckFacultyQuiz checker;
                        checker.checkFacultyQuiz(facultyName);
                        system("pause");

                    }
                    else if(choice4==6){
                        system("cls");
                        CheckFacultyAssignment checker;
                        checker.checkFacultyAssignment(facultyName);
                        system("pause");

                    }
                    else if(choice4==7){
                        system("cls");
                        break;
                    }
                    else{
                        cout<<"Invalid Choice"<<endl;


                    }
                }
            }
            else {
                cout<<"Invalid Choice"<<endl;
            }

        }

        return 0;

    }
