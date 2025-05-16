#include "MyString.h"
#include <iostream>

MyString::MyString() : length(0) {
    this->data = new char[1];
    this->data[0] = '\0';
}

MyString::MyString(const char* str) {
    this->length = strlen(str);
    this->data = new char[length + 1];
    strcpy_s(data, length + 1, str);
}

MyString::MyString(const MyString& other) {
    this->length = other.length;
    this->data = new char[length + 1];
    strcpy_s(this->data, length + 1, other.data);
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] this->data;
        this->length = other.length;
        this->data = new char[length + 1];
        strcpy_s(this->data, length + 1, other.data);
    }
    return *this;
}

MyString::~MyString() {
    delete[] this->data;
}

size_t MyString::size() const {
    return this->length;
}

char& MyString::operator[](size_t index) {
    return this->data[index];
}

const char& MyString::operator[](size_t index) const {
    return this->data[index];
}

MyString MyString::operator+(const MyString& other) const {
    MyString result;
    delete[] result.data;
    result.length = length + other.length;
    result.data = new char[result.length + 1];

    strcpy_s(result.data, this->length+1, this->data);
    strcat(result.data, other.data);

    return result;
}

const char* MyString::c_str() const {
    return this->data;
}