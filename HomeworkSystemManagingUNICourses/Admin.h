#pragma once

#include "User.h"
#include "MyString.h"

class Admin : public User {
public:
	Admin(const MyString firstName, const MyString lastName, size_t userId, const MyString password);

	void createTeacher();
	void createStudent();
	void sendGlobalMessage(const MyString content, const User** allUsers, size_t userCount);
};