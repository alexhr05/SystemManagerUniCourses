#include "Assignment.h"
#include "MyString.h"
#include <iostream>

Assignment::Assignment() : studentAnswers(nullptr), studentIds(nullptr), answerCount(0) , grades(nullptr), gradeCount(0) {}

Assignment::Assignment(const MyString name) : name(name), studentAnswers(nullptr), studentIds(nullptr), answerCount(0) , grades(nullptr) , gradeCount(0){}

Assignment::Assignment(const Assignment& other) {
    name = other.name;
    answerCount = other.answerCount;
    gradeCount = other.gradeCount;

    studentAnswers = new MyString[answerCount];
    studentIds = new size_t[answerCount];
    for (size_t i = 0; i < answerCount; i++) {
        studentAnswers[i] = other.studentAnswers[i];
        studentIds[i] = other.studentIds[i];
    }

    grades = new GradeEntry[gradeCount];
    for (size_t i = 0; i < gradeCount; ++i)
        grades[i] = other.grades[i];
}

Assignment& Assignment::operator=(const Assignment& other) {
    if (this != &other) {
        delete[] studentAnswers;
        delete[] studentIds;
        delete[] grades;
        name = other.name;
        answerCount = other.answerCount;
        gradeCount = other.gradeCount;

        studentAnswers = new MyString[answerCount];
        studentIds = new size_t[answerCount];
        for (size_t i = 0; i < answerCount; i++) {
            studentAnswers[i] = other.studentAnswers[i];
            studentIds[i] = other.studentIds[i];
        }

        grades = new GradeEntry[gradeCount];
        for (size_t i = 0; i < gradeCount; ++i)
            grades[i] = other.grades[i];
    }
    return *this;
}

Assignment::~Assignment() {
    delete[] studentIds;
    delete[] grades;
    studentAnswers = nullptr;
    studentIds = nullptr;
    answerCount = 0;
}



void Assignment::addAnswer(size_t studentId, const MyString& answer) {
    MyString* newAnswers = new MyString[answerCount + 1];
    size_t* newIds = new size_t[answerCount + 1];
    GradeEntry* newGrade = new GradeEntry[]

    for (size_t i = 0; i < answerCount; i++) {
        newAnswers[i] = studentAnswers[i];
        newIds[i] = studentIds[i];
    }

    newAnswers[answerCount] = answer;
    newIds[answerCount] = studentId;

    delete[] studentAnswers;
    delete[] studentIds;

    studentAnswers = newAnswers;
    studentIds = newIds;
    answerCount++;
}



void Assignment::printAnswers() const {
    for (size_t i = 0; i < answerCount; i++) {
        std::cout << "Student ID: " << studentIds[i] << "; Answer: " << studentAnswers[i].c_str() << std::endl;
    }
}

const MyString& Assignment::getName() const {
    return name;
}

size_t Assignment::getGradeCount() {
    return gradeCount;
}

void Assignment::addOrUpdateGrade(size_t studentId, double grade) {
    for (size_t i = 0; i < gradeCount; i++) {
        if (grades[i].studentId == studentId) {
            grades[i].grade = grade;
            return;
        }
    }

    GradeEntry* newGrades = new GradeEntry[gradeCount + 1];
    for (size_t i = 0; i < gradeCount; i++)
        newGrades[i] = grades[i];
    newGrades[gradeCount].studentId = studentId;
    newGrades[gradeCount].grade = grade;

    delete[] grades;
    grades = newGrades;
    gradeCount++;
}

double Assignment::getGradeByStudentId(size_t studentId) const {
    for (size_t i = 0; i < gradeCount;i++) {
        if (grades[i].studentId == studentId)
            return grades[i].grade;
    }
    return -1;// Няма намерен резултат
}

size_t Assignment::getAnswerCount() {
    return answerCount;
}

GradeEntry& Assignment::getGradeEntryAt(size_t index) {
    if (index >= gradeCount) {
        std::cerr << "Invalid index in getGradeEntryAt\n";
        exit(1);
    }
    return grades[index];
}
