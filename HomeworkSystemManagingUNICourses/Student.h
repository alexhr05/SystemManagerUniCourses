#pragma once

#include "User.h"
#include "SystemManager.h"
#include "MyString.h"

class Student : public User {
private: 
    size_t enrolledCourseCount;
public:
    Student(const MyString firstName, const MyString lastName, size_t id, const MyString password);

    void selfEnrollInCourse(SystemManager& system, const MyString courseName, const MyString password);
    void submitAssignment(SystemManager& system, const MyString courseName, const MyString assignmentName, const MyString answer);
    void viewGrades(SystemManager& system, const MyString courseName, const MyString assingmentName);
};