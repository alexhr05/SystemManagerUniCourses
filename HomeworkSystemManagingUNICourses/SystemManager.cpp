#include "SystemManager.h"
#include "User.h"
#include "MyString.h"
#include <iostream>

using namespace std;

SystemManager::SystemManager() : courses(nullptr), courseCount(0), users(nullptr), userCount(0) {}


SystemManager::~SystemManager() {
	delete[] courses;
}

SystemManager::SystemManager(const SystemManager& other) : courses(nullptr), courseCount(0), users(nullptr), userCount(0) {
	*this = other;
}

SystemManager& SystemManager::operator=(const SystemManager& other) {
	if (this != &other) {
		delete[] courses;
		for (size_t i = 0; i < userCount; i++) {
			delete users[i];
		}
		delete[] users;

		// Копиране на курсове
		courseCount = other.courseCount;
		courses = new Course[courseCount];
		for (size_t i = 0; i < courseCount; i++) {
			courses[i] = other.courses[i];
		}

		// Копиране на потребители (дълбоко копие)
		userCount = other.userCount;
		users = new User * [userCount];
		for (size_t i = 0; i < userCount; i++) {
			users[i] = other.users[i]; 
		}
	}
	return *this;
}

void SystemManager::addUser(User* user) {
	User** newUsers = new User* [userCount + 1];
	for (size_t i = 0; i < userCount; i++) {
		newUsers[i] = users[i];
	}
	newUsers[userCount] = user;
	delete[] users;
	users = newUsers;
	userCount++;
}

User* SystemManager::getUserById(size_t id) const {
	for (size_t i = 0; i < userCount; ++i) {
		if (users[i]->getId() == id) {
			return users[i];
		}
	}
	return nullptr;
}


void SystemManager::AddCourse(const Course& course) {
	Course* newCourses = new Course[courseCount + 1];
	for (size_t i = 0; i < courseCount; i++)
	{
		newCourses[i] = courses[i];
	}
	newCourses[courseCount] = course;
	delete[] courses;
	courses = newCourses;

	courseCount++;
}

void SystemManager::printAllCourses() const {
	for (size_t i = 0; i < courseCount; i++)
	{
		cout << "Course: " << courses[i].getName().c_str() << endl;
	}
}

Course* SystemManager::findCourseByName(const MyString name) {
	for (size_t i = 0; i < courseCount; i++)
	{
		if (courses->getName().equals(name)) {
			return &courses[i];
		}
	}
}

size_t SystemManager::generateCourseId() {
	return nextCourseId++;
}
