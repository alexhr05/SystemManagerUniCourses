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
	size_t nextCourseId = 1;

	User** users;
	size_t userCount;

	void addUser(User* user); 

	friend class Admin;  
	


public:
	SystemManager();
	SystemManager(const SystemManager& other);
	SystemManager& operator=(const SystemManager& other);
	~SystemManager();

	void AddCourse(const Course& course);
	void printAllCourses() const;
	Course* findCourseByName(const MyString name);

	size_t generateCourseId();

	User* getUserById(size_t id) const;
	size_t getUserCount() const;


	void loadFromFiles();
	void saveToFiles();

	void saveCoursesToFile() const;
	void loadCoursesFromFile();

	void saveMailsToFile() const;
	void loadMailsFromFile();

};

