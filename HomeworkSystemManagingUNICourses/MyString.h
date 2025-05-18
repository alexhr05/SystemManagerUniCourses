#pragma once
#ifndef MYSTRING_H
#define MYSTRING_H

class MyString {
private:
	char* data;
	size_t length;
public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	size_t size() const;
	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	MyString operator+(const MyString& other) const;
	const char* c_str() const;

	bool equals(const MyString& other) const;
	MyString fromDouble(double number);

};

#endif
