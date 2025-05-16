#pragma once
#include "MyString.h"

class Assignment {
private:
    MyString name;
    MyString* studentAnswers;
    size_t* studentIds;
    size_t answerCount;
    
public:
    Assignment();
    Assignment(const MyString& name);
    Assignment(const Assignment& other);
    Assignment& operator=(const Assignment& other);
    ~Assignment();

    void addAnswer(size_t studentId, const MyString& answer);
    void printAnswers() const;

    const MyString& getName() const;
};