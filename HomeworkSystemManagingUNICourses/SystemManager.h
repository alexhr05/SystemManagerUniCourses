#pragma once
#pragma once
#include "Course.h"
#include "User.h"
#include "Teacher.h"
#include "Student.h"
#include "MyString.h"

class SystemManager {
private:
	Course* courses;
	size_t courseCount;

public:
	SystemManager();
	~SystemManager();

	void AddCourse(const Course& course);
	void printAllCourses() const;
	Course* findCourseByName(const MyString name);

};