cmake_minimum_required(VERSION 3.26)
project(OOP_NEW_PROJECT)

set(CMAKE_CXX_STANDARD 23)

add_executable(OOP_NEW_PROJECT main.cpp
        Studentdetails.h
        FacultyMember.h
        StaffMember.h
        AddCourse.h
        CheckStudentProfile.h
        FacuityMemberCheck.h
        RemoveStudent.h
        StaffMemeberCheck.h
        RemoveFaculity.h
        RemoveStaff.h
        RemoveCourse.h
        UpdateStudentProfile.h
        UpdateFaculity.h
        UpdateStaff.h
        UpdateCourse.h
        AssignCourses.h
        LoginStudent.h
        StudentUpdateUsernamePassword.h
        StudentEnrollCourses.h
        UploadAssigment.h
        UploadQuiz.h
        FaculityLogin.h
        FaculityUpdateUsernamePassword.h
        FaculityCheckCourses.h
        FaculityCheckStudent.h
        StudentCheckAttendence.h
        GivesMarks.h
        StudentCheckGpa.h
        Person.h
        CheckQuiz.h
        CheckAssigment.h
        AdminCheckStudent.h
)
