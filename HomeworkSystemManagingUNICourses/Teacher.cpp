#include "Teacher.h"
#include "SystemManager.h"

Teacher::Teacher(const MyString firstName, const MyString lastName, size_t id, const MyString password)
    : User(firstName, lastName, id, password) {}

void Teacher::createCourse(SystemManager& manager, const MyString& courseName, const MyString& enrollPassword) {

}
