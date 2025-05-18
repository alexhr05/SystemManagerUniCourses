#include "Course.h"

#include <iostream>

using namespace std;

Course::Course() : name(""), teacherId(0), enrollPassword(""), studentIds(nullptr), studentCount(0) {}

Course::Course(const MyString name, size_t teacherId, const MyString password)
    : name(name), teacherId(teacherId), enrollPassword(password), studentIds(nullptr), studentCount(0) {
}

Course::Course(const Course& other) {
    *this = other;
}

Course& Course::operator=(const Course& other) {
    if (this != &other) {
        delete[] studentIds;

        this->name = other.name;
        this->teacherId = other.teacherId;
        this->enrollPassword = other.enrollPassword;

        studentCount = other.studentCount;
        studentIds = new size_t[studentCount];
        for (size_t i = 0; i < studentCount; i++) {
            studentIds[i] = other.studentIds[i];
        }
            
    }
    return *this;
}

Course::~Course() {
    delete[] studentIds;
}

void Course::enrollStudent(size_t studentId) {
    for (size_t i = 0; i < this->studentCount; i++) {
        if (studentIds[i] == studentId) {
            return;
        }
    }

    size_t* newList = new size_t[studentCount + 1];
    for (size_t i = 0; i < this->studentCount; i++) {
        newList[i] = studentIds[i];
    }

    newList[studentCount++] = studentId;

    delete[] studentIds;
    studentIds = newList;
}

void Course::printStudents() const {
    cout << "Students in " << name.c_str() << ":\n";
    for (size_t i = 0; i < studentCount; ++i)
        cout << " - Student ID: " << studentIds[i] << '\n';
}

const MyString& Course::getName() const {
    return name;
}
const MyString& Course::getPassword() const {
    return enrollPassword;
}

size_t Course::getTeacherId() const {
    return teacherId;
}

void Course::setPassword(const MyString newPassword) {
    enrollPassword = newPassword;
}

MyString Course::getEnrollmentPassword() const {
    return enrollPassword;
}

void Course::addAssignment(const MyString assignmentName) {
    Assignment* newAssignments = new Assignment[assignmentCount + 1];
    for (size_t i = 0; i < assignmentCount; i++)
    {
        newAssignments[i] = assignments[i];
    }
    newAssignments[assignmentCount] = Assignment(assignmentName);

    delete[] assignments;
    assignments = newAssignments;
    assignmentCount++;
}


Assignment* Course::getAssignmentByName(const MyString name) {
    for (size_t i = 0; i < assignmentCount; i++)
    {
        if(assignments[i].getName().equals(name)) {
            return &assignments[i];
        }
    }
}

size_t* Course::getStudentIds() const {
    return studentIds;
}

size_t Course::getStudentCount() const {
    return studentCount;
}