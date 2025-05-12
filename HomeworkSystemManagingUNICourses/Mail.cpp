#include "Mail.h"
#include <iomanip>
#include <sstream>
#include "MyString.h"
#include <iostream>

using namespace std;

Mail::Mail() : senderName(""), content(""), timestamp(time(nullptr)) {}

Mail::Mail(const MyString& senderName, const MyString& content)
    : senderName(senderName), content(content), timestamp(time(nullptr)) {
}

MyString Mail::getSenderName() const {
    return senderName;
}

MyString Mail::getContent() const {
    return content;
}

time_t Mail::getTimestamp() const {
    return timestamp;
}

MyString Mail::getFormattedTimestamp() const {
    tm* localTime = std::localtime(&timestamp);
    ostringstream oss;
    oss << put_time(localTime, "%H:%M %d.%m.%Y");
    return oss.str();
}