#pragma once
#ifndef MAIL_H
#define MAIL_H

#include <string>
#include <ctime>
#include "MyString.h"

class Mail {
private:
    MyString senderName;
    MyString content;
    time_t timestamp;

public:
    Mail();
    Mail(const MyString& senderName, const MyString& content);

    MyString getSenderName() const;
    MyString getContent() const;
    time_t getTimestamp() const;
    MyString getFormattedTimestamp() const;
};

#endif