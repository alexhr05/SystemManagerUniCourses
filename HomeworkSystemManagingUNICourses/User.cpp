#include "User.h"
#include "Mail.h"
#include <iostream>

User::User(const MyString firstName, const MyString lastName, size_t id, const MyString password)
    : firstName(firstName), lastName(lastName), userId(id), password(password), inbox(nullptr), inboxSize(0) {
}

User::User(const User& other)
    : firstName(other.firstName), lastName(other.lastName), userId(other.userId), password(other.password), inbox(nullptr), inboxSize(0)
{
    copyInbox(other.inbox, other.inboxSize);
}

User& User::operator=(const User& other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        userId = other.userId;
        password = other.password;

        freeInbox();
        copyInbox(other.inbox, other.inboxSize);
    }
    return *this;
}

User::~User() {
    freeInbox();
}

void User::copyInbox(const Mail* otherInbox, size_t size) {
    if (size == 0 || otherInbox == nullptr) return;

    inbox = new Mail[size];
    for (size_t i = 0; i < size; ++i) {
        inbox[i] = otherInbox[i];
    }
    inboxSize = size;
}

void User::freeInbox() {
    delete[] inbox;
    inbox = nullptr;
    inboxSize = 0;
}

const MyString& User::getFirstName() const {
    return firstName;
}

const MyString& User::getLastName() const {
    return lastName;
}

size_t User::getId() const {
    return userId;
}

const MyString& User::getPassword() const {
    return password;
}

void User::changePassword(const MyString& newPass) {
    password = newPass;
}

void User::receiveMessage(const Mail& mail) {
    Mail* newInbox = new Mail[inboxSize + 1];
    for (size_t i = 0; i < inboxSize; i++) {
        newInbox[i] = inbox[i];
    }
    newInbox[inboxSize] = mail;

    delete[] inbox;
    inbox = newInbox;
    inboxSize++;
}

void User::printInbox() const {
    if (inboxSize == 0) {
        std::cout << "No messages to show!\n";
        return;
    }

    for (size_t i = 0; i < inboxSize; ++i) {
        std::cout << inbox[i].getFormattedTimestamp().c_str()
            << ", sent by " << inbox[i].getSenderName().c_str()
            << ": " << inbox[i].getContent().c_str() << '\n';
    }
}

void User::clearInbox() {
    freeInbox();
}