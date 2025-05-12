#pragma once
#include "MyString.h"
#include "Mail.h"

class User {
private:
	MyString name;
	MyString family;
	unsigned int userId;

	Mail* inbox;
	size_t inboxSize;
	size_t inboxCapacity;

public:
	User(const MyString& name, const MyString& family, unsigned int id);
	~User();

	void getUserId() const;

	void receiveMail(const Mail& mail);
	void showInbox() const;
	void clearInbox();


};