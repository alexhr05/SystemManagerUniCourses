#pragma once

#include "User.h"
#include "MyString.h"

class Student : public User {
public:
	Student(const MyString firstName, const MyString lastName, size_t userId, const MyString password);

	void enrollInCourse();
	void submitAssignment();
	void viewGrades();
};