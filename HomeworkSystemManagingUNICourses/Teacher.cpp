#include "Teacher.h"
#include "Course.h"
#include "Role.h"
#include "Assignment.h"
#include "SystemManager.h"
#include <iostream>
#include "MyString.cpp"

using namespace std;

Teacher::Teacher(const MyString firstName, const MyString lastName, size_t id, const MyString password)
    : User(firstName, lastName, id, password), courseIds(nullptr), courseCount(0) {}

Teacher::Teacher(const Teacher& other)
    : User(other), courseCount(other.courseCount) {
    courseIds = new size_t[courseCount];
    for (size_t i = 0; i < courseCount; i++)
        courseIds[i] = other.courseIds[i];
}

Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        User::operator=(other);

        delete[] courseIds;
        courseCount = other.courseCount;
        courseIds = new size_t[courseCount];
        for (size_t i = 0; i < courseCount; i++)
            courseIds[i] = other.courseIds[i];
    }
    return *this;
}

Teacher::~Teacher() {
    delete[] courseIds;
}



void Teacher::addCourse(const size_t courseId) {
    size_t* newIds = new size_t[courseCount + 1];
    for (size_t i = 0; i < courseCount; i++)
    {
        newIds[i] = courseIds[i];
    }
    newIds[courseCount++] = courseId;
    delete[] courseIds;
    courseIds = newIds;
}

void Teacher::createCourse(SystemManager& system, const MyString name, const MyString enrollPassword) {
    system.AddCourse(Course(name, this->getId(), enrollPassword));
}

void Teacher::createAssignment(SystemManager& system, const MyString courseName, const MyString assignmentName) {
    Course* course = system.findCourseByName(courseName);
    if (!course || course->getTeacherId() != this->getId()) {
        cout << "Course not found or unauthorized access.\n";
        return;
    }

    course->addAssignment(assignmentName);
}

void Teacher::enrollStudent(SystemManager& system, const MyString courseName, size_t studentId) {
    Course* course = system.findCourseByName(courseName);
    if (!course || course->getTeacherId() != this->getId()) {
        std::cout << "Access denied to this course.\n";
        return;
    }

    course->enrollStudent(studentId);
    std::cout << "Student with ID " << studentId << " added to course " << course->getName().c_str() << ".\n";
}

void Teacher::setEnrollmentPassword(SystemManager& system, const MyString courseName, const MyString password) {
    Course* course = system.findCourseByName(courseName);
    if (!course || course->getTeacherId() != this->getId()) {
        std::cout << "Cannot set password for this course.\n";
        return;
    }

    course->setPassword(password);
    cout << "Password set for course " << course->getName().c_str() << ".\n";
}


void Teacher::gradeAssignment(SystemManager& system, const MyString courseName, const MyString assignmentName, size_t studentId, double grade) {
    Course* course = system.findCourseByName(courseName);
    if (!course || course->getTeacherId() != this->getId()) {
        cout << "Access denied.\n";
        return;
    }

    Assignment* assignment = course->getAssignmentByName(assignmentName);
    if (!assignment) {
        cout << "Assignment not found.\n";
        return;
    }

    if (!course->isStudentEnrolled(studentId)) {
        cout << "Student is not enrolled in this course.\n";
        return;
    }

    
    assignment->addOrUpdateGrade(studentId, grade);

    
    User* student = system.getUserById(studentId);
    if (!student) {
        cout << "Student not found.\n";
        return;
    }

    MyString gradeStr = gradeStr.fromDouble(grade); 
    MyString message = MyString("Your assignment '") + assignmentName + "' was graded: " + gradeStr;

    Mail mail(this->getFirstName(), message);
    student->receiveMessage(mail);

    cout << "Grade sent to student ID " << studentId << ".\n";
}


void Teacher::sendMessageToCourseStudents(SystemManager& system, const MyString courseName, const MyString message) {
    Course* course = system.findCourseByName(courseName);
    if (!course || course->getTeacherId() != this->getId()) {
        cout << "Unauthorized\n";
        return;
    }

    size_t* students = course->getStudentIds();
    size_t count = course->getStudentCount();
    for (size_t i = 0; i < count; ++i) {
        User* student = system.getUserById(students[i]);
        if (student) {
            student->receiveMessage(Mail(this->getFirstName(), message));
        }
    }
}


void Teacher::viewAnswers(SystemManager& system, const MyString courseName, const MyString assignmentName) {
    Course* course = system.findCourseByName(courseName);
    if (!course) {
        cout << "Course not found.\n";
        return;
    }

    // Проверка дали преподавателят води този курс
    if (course->getTeacherId() != this->getId()) {
        cout << "You are not the instructor of this course.\n";
        return;
    }

    const Assignment* assignment = course->getAssignmentByName(assignmentName);
    if (!assignment) {
        cout << "Assignment not found.\n";
        return;
    }

    cout << "Answers for assignment: " << assignmentName.c_str() << '\n';
    assignment->printAnswers();
}

Role Teacher::getRole() const {
    return Role::Teacher;
}