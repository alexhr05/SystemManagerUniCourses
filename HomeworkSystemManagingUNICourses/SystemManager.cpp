#include "SystemManager.h"
#include "User.h"
#include "Admin.h"
#include "MyString.h"
#include <iostream>
#include <fstream>

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

void SystemManager::loadUsersFromFile() {
	// Зареждане на потребители
	ifstream usersFile("Users.txt");
	if (usersFile.is_open()) {
		size_t count;
		usersFile >> count;
		for (size_t i = 0; i < count; ++i) {
			size_t role, id;
			MyString fName, lName, pass;
			usersFile >> role >> id >> fName >> lName >> pass;
			if (role == 0)
				addUser(new Admin(fName, lName, id, pass));
			else if (role == 1)
				addUser(new Teacher(fName, lName, id, pass));
			else if (role == 2)
				addUser(new Student(fName, lName, id, pass));
		}
		usersFile.close();
	}

	// Аналогично зареждане на courses.dat и mails.dat
}

void SystemManager::saveUserToFiles() {
	ofstream usersFile("Users.txt");
	usersFile << userCount << '\n';
	for (size_t i = 0; i < userCount; ++i) {
		usersFile <<users[i]->getId() << " "
			<< users[i]->getFirstName().c_str() << " "
			<< users[i]->getLastName().c_str() << " "
			<< users[i]->getPassword().c_str() << "\n";
	}
	usersFile.close();

	// Аналогично за courses и mails
}

MyString fromSizeT(size_t number) {
	if (number == 0) return MyString("0");

	char buffer[101];
	size_t index = 100;
	buffer[index] = '\0';

	while (number > 0) {
		buffer[--index] = '0' + (number % 10);
		number /= 10;
	}

	return MyString(buffer + index);
}

void SystemManager::saveCoursesToFile() const {
	std::ofstream file("Course.txt");
	if (!file.is_open()) {
		std::cout << "Failed to open course file for saving.\n";
		return;
	}

	file << courseCount << '\n';

	for (size_t i = 0; i < courseCount; ++i) {
		Course& c = courses[i];
		file << c.getName().c_str() << ' ' << c.getTeacherId() << ' ' << c.getStudentCount() << '\n';

		for (size_t j = 0; j < c.getStudentCount(); ++j) {
			file << c.getStudentIds(j) << ' ';
		}
		file << '\n';

		file << c.getAssignmentCount() << '\n';
		for (size_t k = 0; k < c.getAssignmentCount(); ++k) {
			Assignment* a = c.getAssignmentAt(k);
			file << a->getName().c_str() << ' ' << a->getGradeCount() << '\n';

			for (size_t l = 0; l < a->getGradeCount(); ++l) {
				const GradeEntry& entry = a->getGradeEntryAt(l);
				file << entry.studentId << ' ' << entry.answer.c_str() << ' ' << entry.grade << '\n';
			}
		}
	}

	file.close();
}

void SystemManager::loadCoursesFromFile() {
	std::ifstream file("Course.txt");
	if (!file.is_open()) return;

	file >> courseCount;
	file.ignore();

	for (size_t i = 0; i < courseCount; ++i) {
		size_t teacherId;
		MyString name, password;

		file >> teacherId;
		file.ignore();
		name.readFromStream(file);
		password.readFromStream(file);

		Course course(name,teacherId,  password);

		size_t studentCount;
		file >> studentCount;
		for (size_t j = 0; j < studentCount; ++j) {
			size_t studentId;
			file >> studentId;
			course.enrollStudent(studentId);
		}

		size_t assignmentCount;
		file >> assignmentCount;
		file.ignore();

		for (size_t j = 0; j < assignmentCount; ++j) {
			MyString aName;
			aName.readFromStream(file);

			Assignment assignment(aName);

			size_t answerCount;
			file >> answerCount;
			file.ignore();

			for (size_t k = 0; k < answerCount; ++k) {
				size_t studentId;
				MyString answer;
				file >> studentId;
				file.ignore();
				answer.readFromStream(file);
				assignment.addAnswer(studentId, answer);
			}

			course.addAssignment(aName);
		}

		courses[i] = course;
	}

	file.close();
}


void SystemManager::saveMailsToFile() const {
	ofstream file("mails.txt");
	if (!file.is_open()) return;

	for (size_t i = 0; i < userCount; ++i) {
		User* user = users[i];
		file << user->getId() << '\n';
		file << user->getInboxCount() << '\n';
		for (size_t j = 0; j < user->getInboxCount(); j++) {
			Mail& mail = user->getInbox(j);
			file << mail.getSenderName().c_str() << '\n';
			file << mail.getContent().c_str() << '\n';
		}
	}

	file.close();
}

void SystemManager::loadMailsFromFile() {
	ifstream file("mails.txt");
	if (!file.is_open()) return;

	while (!file.eof()) {
		size_t id, count;
		file >> id >> count;
		file.ignore();

		User* user = getUserById(id);
		if (!user) continue;

		for (size_t i = 0; i < count; ++i) {
			MyString sender, message;
			sender.readFromStream(file);
			message.readFromStream(file);
			user->receiveMessage(Mail(sender, message));
		}
	}

	file.close();
}

User* SystemManager::login(size_t id, const MyString& password) {
	for (size_t i = 0; i < userCount; i++) {
		if (users[i]->getId() == id && users[i]->getPassword().equals(password)) {
			return users[i];
		}
	}
	return nullptr;
}

bool SystemManager::addTeacher(const MyString firstName, const MyString lastName, const MyString password) {
	size_t newId = generateNextUserId();
	Teacher* teacher = new Teacher(firstName, lastName, newId, password );
	addUser(teacher);
	cout << "Added teacher " << firstName.c_str() << " " << lastName.c_str() << " with ID " << newId << "!\n";
	return true;
}

bool SystemManager::addStudent(const MyString firstName, const MyString lastName, const MyString password) {
	size_t newId = generateNextUserId();
	Student* student = new Student(firstName, lastName, newId, password );
	addUser(student);
	cout << "Added student " << firstName.c_str() << " " << lastName.c_str() << " with ID " << newId << "!\n";
	return true;
}

size_t SystemManager::generateNextUserId() {
	return nextUserId++;
}

size_t SystemManager::generateNextCourseId(){
	return nextCourseId++; 
}

bool SystemManager::isAdmin(User* user) {
	return user && user->getRole() == Role::Admin;
}

bool SystemManager::isTeacher(User* user) {
	return user && user->getRole() == Role::Teacher;
}

bool SystemManager::isStudent(User* user) {
	return user && user->getRole() == Role::Student;
}


void SystemManager::executeAdminCommand(SystemManager& system, const MyString& command, User* user) {
	if (!user || !system.isAdmin(user)) {
		cout << "Access denied.\n";
		return;
	}

	if (command.equals("add_teacher")) {
		MyString firstName, lastName, password;
		cin >> firstName >> lastName >> password;

		size_t newId = system.generateNextUserId();
		Teacher* teacher = new Teacher(firstName, lastName, newId, password);
		system.addTeacher(firstName, lastName, password);

		cout << "Added teacher " << firstName.c_str() << " " << lastName.c_str()
			<< " with ID " << newId << "!\n";

	}
	else if (command.equals("add_student")) {
		MyString firstName, lastName, password;
		cin >> firstName >> lastName >> password;

		size_t newId = system.generateNextUserId();
		Student* student = new Student(firstName, lastName, newId,password);
		system.addStudent(firstName, lastName, password);

		cout << "Added student " << firstName.c_str() << " " << lastName.c_str()
			<< " with ID " << newId << "!\n";

	}
	else if (command.equals("message_all")) {
		MyString message;
		cin >> message;
		User** users = system.getUsers();
		for (size_t i = 0; i < system.getUserCount(); ++i) {
			if (users[i]->getId() != user->getId()) {
				Mail mail(user->getFirstName(), message);
				users[i]->receiveMessage(mail);
			}
		}

		cout << "Message sent to all users.\n";

	}
	else {
		cout << "Unknown admin command.\n";
	}
}

void SystemManager::executeTeacherCommand(SystemManager& system,const MyString& command, Teacher* teacher) {
	if (!teacher) {
		cout << "Access denied.\n";
		return;
	}

	if (command.equals( "create_course")) {
		MyString courseName, password;
		cin >> courseName >> password;
		Course newCourse(courseName, teacher->getId(), password);
		
		system.AddCourse(newCourse);
		cout << "Course \"" << courseName.c_str()<<endl;
	}
	else if (command.equals( "add_to_course")) {
		MyString courseName;
		size_t studentId;
		cin >> courseName >> studentId;

		Course* course = system.findCourseByName(courseName);
		if (!course || course->getTeacherId() != teacher->getId()) {
			cout << "Course not found or permission denied.\n";
			return;
		}

		course->enrollStudent(studentId);
		User* student = system.getUserById(studentId);
		if (student) {
			Mail mail(teacher->getFirstName(), MyString(teacher->getFirstName() + " " + teacher->getLastName() + " added you to " + courseName));
			student->receiveMessage(mail);
		}
		cout << "Student added to course.\n";
		

	}
	else if (command.equals( "send_message")) {
		size_t studentId;
		cin >> studentId;
		MyString message;
		cin >> message;

		User* student = system.getUserById(studentId);
		if (student) {
			Mail mail(teacher->getFirstName(), message);
			student->receiveMessage(mail);
			cout << "Message sent to student.\n";
		}
		else {
			cout << "Student not found.\n";
		}

	}
	else {
		cout << "Unknown teacher command.\n";
	}
}

void SystemManager::executeStudentCommand(SystemManager& system, const MyString& command, Student* student) {
	if (!student) {
		cout << "Access denied.\n";
		return;
	}

	if (command.equals( "mailbox")) {
		student->printInbox();

	}
	else if (command.equals( "view_grades")) {
		MyString courseName, assignmentName;
		cout << "Write courseName and assignment name";
		cin >> courseName >> assignmentName;
		student->viewGrades(system, courseName, assignmentName);  // използва SystemManager за достъп до курсове и оценки

	}
	else if (command.equals( "submit_assignment")) {
		MyString courseName, assignmentName, answer;
		cin >> courseName >> assignmentName;
		cin >> answer;

		Course* course = system.findCourseByName(courseName);
		if (!course || !course->isStudentEnrolled(student->getId())) {
			cout << "You are not enrolled in this course.\n";
			return;
		}

		Assignment* assignment = course->getAssignmentByName(assignmentName);
		if (!assignment) {
			cout << "Assignment not found.\n";
			return;
		}

		assignment->addAnswer(student->getId(), answer);
		cout << "Assignment submitted.\n";

	}
	else {
		cout << "Unknown student command.\n";
	}
}


User** SystemManager::getUsers() const {
	return users;
}
