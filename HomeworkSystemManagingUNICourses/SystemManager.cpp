#include "SystemManager.h"
#include "MyString.h"
#include <iostream>

using namespace std;

SystemManager::SystemManager() : courses(nullptr), courseCount(0){}

SystemManager::~SystemManager() {
	delete[] courses;
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
