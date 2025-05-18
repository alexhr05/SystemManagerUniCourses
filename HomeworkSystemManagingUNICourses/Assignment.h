#pragma once
#include "MyString.h"

// Assignment.h
struct GradeEntry {
    size_t studentId;
    double grade;
};


class Assignment {
private:
    GradeEntry* grades;
    size_t gradeCount;
    MyString name;
    MyString* studentAnswers;
    size_t* studentIds;
    size_t answerCount;
    
public:
    Assignment();
    Assignment(const MyString name);
    Assignment(const Assignment& other);
    Assignment& operator=(const Assignment& other);
    ~Assignment();

    void addAnswer(size_t studentId, const MyString& answer);
    void printAnswers() const;

    const MyString& getName() const;

    void addOrUpdateGrade(size_t studentId, double grade);
    double getGradeByStudentId(size_t studentId) const;
};