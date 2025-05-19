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
	size_t nextUserId = 1;
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
	User** getUsers() const;

	void loadUsersFromFile();
	void saveUserToFiles();

	void saveCoursesToFile() const;
	void loadCoursesFromFile();

	void saveMailsToFile() const;
	void loadMailsFromFile();

	User* login(size_t id, const MyString& password);
	bool addTeacher(const MyString firstName, const MyString lastName, const MyString password);
	bool addStudent(const MyString firstName, const MyString lastName, const MyString password);
	size_t generateNextUserId();
	size_t generateNextCourseId();


	bool isAdmin(User* user);
	bool isTeacher(User* user);
	bool isStudent(User* user);

	void executeAdminCommand(SystemManager& system, const MyString& command, User* user);
	void executeTeacherCommand(SystemManager& system, const MyString& command, Teacher* teacher);
	void executeStudentCommand(SystemManager& system, const MyString& command, Student* student);

};

