#ifndef OOP_NEW_PROJECT_UPLOADASSIGMENT_H
#define OOP_NEW_PROJECT_UPLOADASSIGMENT_H

#include <windows.h>
#include <commdlg.h>
#include <fstream>
using namespace std;

#include <windows.h>
#include <commdlg.h>
#include <fstream>

using namespace std;

class UploadAssignment {
public:
    void uploadFile(const string& enrollment) {
        string courses[10]; // Assuming a student can enroll in a maximum of 10 courses
        int numCourses = 0;

        // Read the file to get all the enrolled courses
        ifstream file(enrollment + "_enrolledCourses.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("Course Code: ") != string::npos) {
                courses[numCourses] = line.substr(13); // Extract the course code
                numCourses++;
            }
        }

        // Display all the enrolled courses and ask the student to select one
        cout << "Courses enrolled by student:\n";
        for (int i = 0; i < numCourses; i++) {
            cout << i + 1 << ". " << courses[i] << "\n";
        }
        int choice;
        cout << "Choose a course to upload assignment: ";
        while(!(cin >> choice) || choice < 1 || choice > numCourses) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and " << numCourses << ": ";
        }
        string courseCode = courses[choice - 1];

        // Upload the assignment for the selected course
        OPENFILENAME ofn;
        char fileName[MAX_PATH] = "";
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = NULL;
        ofn.lpstrFilter = "All Files\0*.*\0\0";
        ofn.lpstrFile = fileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
        ofn.lpstrDefExt = "";
        if (GetOpenFileName(&ofn))
        {
            ifstream srcFile(fileName, ios::binary);
            char buffer[MAX_PATH];
            GetModuleFileName(NULL, buffer, MAX_PATH);
            string::size_type pos = string(buffer).find_last_of("\\/");
            string assignmentPath = string(buffer).substr(0, pos) + "/" + enrollment + "_" + courseCode + "_Assignment"; // changed filename construction
            ofstream dstFile(assignmentPath, ios::binary);

            cout << "Uploading";
            for(int i = 0; i < 5; i++) {
                cout << ".";
                Sleep(500); // delay for 500 milliseconds
            }
            cout << "\n";

            dstFile << srcFile.rdbuf();

            srcFile.close();
            dstFile.close();

            cout << "Assignment uploaded successfully." << endl;
            system("pause");
        }
        else
        {
            cout << "No file selected." << endl;
        }
    }
};
#endif //OOP_NEW_PROJECT_UPLOADASSIGMENT_H