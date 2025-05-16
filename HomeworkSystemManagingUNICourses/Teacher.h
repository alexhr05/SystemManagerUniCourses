#pragma once

#include "User.h"
#include "MyString.h"

class Teacher : public User {
public:
	Teacher(const MyString firstName, const MyString lastName, size_t userId, const MyString password);

	void createCourse();
	void assignHomework();
	void gradeAssignment();
};