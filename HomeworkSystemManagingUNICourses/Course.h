#pragma once
#include "MyString.h"

class Course {
    MyString name;
    MyString enrollPassword;
    size_t teacherId; // ID на преподавателя, който води курса

    size_t* studentIds;   // Масив от ID на записаните студенти
    size_t studentCount;

public:
    Course();
    Course(const MyString name, size_t teacherId, const MyString password);
    Course(const Course& other);
    Course& operator=(const Course& other);
    ~Course();

    const MyString& getName() const;
    const MyString& getPassword() const;
    size_t getTeacherId() const;
    
    void setPassword(const MyString newPassword);
    void enrollStudent(size_t studentId);
    void printStudents() const;
};