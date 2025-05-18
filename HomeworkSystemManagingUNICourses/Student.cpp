#include "Student.h"
#include "Course.h"
#include "MyString.h"
#include "Assignment.h"
#include <iostream>
#include "MyString.cpp"

using namespace std;

Student::Student(const MyString firstName, const MyString lastName, size_t id, const MyString password): User(firstName, lastName, id, password), enrolledCourseCount(0){}


void Student::selfEnrollInCourse(SystemManager& system, const MyString courseName, const MyString password) {
    Course* course = system.findCourseByName(courseName);
    if (!course) {
        cout << "Course not found.\n";
        return;
    }

    if (!course->getEnrollmentPassword().equals(password)) {
        cout << "Incorrect password.\n";
        return;
    }

    if (course->isStudentEnrolled(this->getId())) {
        cout << "Already enrolled in this course.\n";
        return;
    }

    course->enrollStudent(this->getId());
    cout << "Self-enrollment successful.\n";
    enrolledCourseCount++;
}

void Student::submitAssignment(SystemManager& system, const MyString courseName, const MyString assignmentName, const MyString answer) {
    Course* course = system.findCourseByName(courseName);
    if (!course) {
        cout << "Course not found.\n";
        return;
    }

    if (!course->isStudentEnrolled(this->getId())) {
        cout << "You are not enrolled in this course.\n";
        return;
    }

    Assignment* assignment = course->getAssignmentByName(assignmentName);
    if (!assignment) {
        cout << "Assignment not found.\n";
        return;
    }

    assignment->addAnswer(this->getId(), answer);
    cout << "Answer submitted successfully.\n";
}

void Student::viewGrades(SystemManager& system, const MyString courseName, const MyString assingmentName){
    bool hasGrades = false;

    for (size_t i = 0; i < enrolledCourseCount; i++) {
        Course* course = system.findCourseByName(courseName);
        if (!course) continue;

        std::cout << "Course: " << course->getName().c_str() << '\n';

        const Assignment* assignments = course->getAssignmentByName(assingmentName);
        size_t assignmentCount = course->getAssignmentCount();

        for (size_t j = 0; j < assignmentCount; ++j) {
            const MyString& assignmentName = assignments[j].getName();
            MyString grade = grade.fromDouble(assignments[j].getGradeByStudentId(this->getId()));

            cout << "  Assignment: " << assignmentName.c_str() << " | Grade: " << (grade.size() > 0 ? grade.c_str() : "Not graded") << '\n';

            hasGrades = true;
        }
    }

    if (!hasGrades) {
        cout << "No grades available.\n";
    }
}