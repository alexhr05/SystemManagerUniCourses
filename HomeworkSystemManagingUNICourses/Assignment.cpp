#include "Assignment.h"
#include "MyString.h"
#include <iostream>

Assignment::Assignment() : studentAnswers(nullptr), studentIds(nullptr), answerCount(0) {}

Assignment::Assignment(const MyString name) : name(name), studentAnswers(nullptr), studentIds(nullptr), answerCount(0) {}

Assignment::Assignment(const Assignment& other) {
    name = other.name;
    answerCount = other.answerCount;

    studentAnswers = new MyString[answerCount];
    studentIds = new size_t[answerCount];
    for (size_t i = 0; i < answerCount; i++) {
        studentAnswers[i] = other.studentAnswers[i];
        studentIds[i] = other.studentIds[i];
    }
}

Assignment& Assignment::operator=(const Assignment& other) {
    if (this != &other) {
        delete[] studentAnswers;
        delete[] studentIds;
        name = other.name;
        answerCount = other.answerCount;

        studentAnswers = new MyString[answerCount];
        studentIds = new size_t[answerCount];
        for (size_t i = 0; i < answerCount; i++) {
            studentAnswers[i] = other.studentAnswers[i];
            studentIds[i] = other.studentIds[i];
        }
    }
    return *this;
}

Assignment::~Assignment() {
    delete[] studentAnswers;
    delete[] studentIds;
    studentAnswers = nullptr;
    studentIds = nullptr;
    answerCount = 0;
}


void Assignment::addAnswer(size_t studentId, const MyString& answer) {
    MyString* newAnswers = new MyString[answerCount + 1];
    size_t* newIds = new size_t[answerCount + 1];

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
