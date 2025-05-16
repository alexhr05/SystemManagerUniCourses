#pragma once
#include "MyString.h"
#include "Mail.h"

class User {
private:
	MyString firstName;
	MyString lastName;
    size_t userId;

    MyString password;

    Mail* inbox;
    size_t inboxSize;

    void copyInbox(const Mail* otherInbox, size_t size);
    void freeInbox();

public:
    User(const MyString& firstName, const MyString& lastName, size_t id, const MyString& password);
    User(const User& other);
    User& operator=(const User& other);
    ~User();

    const MyString& getFirstName() const;
    const MyString& getLastName() const;
    size_t getId() const;

    const MyString& getPassword() const;
    void changePassword(const MyString& newPass);

    void receiveMessage(const Mail& mail);
    
    void printInbox() const;
    void clearInbox();

};