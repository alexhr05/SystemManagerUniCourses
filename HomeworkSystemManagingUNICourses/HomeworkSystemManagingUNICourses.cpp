// HomeworkSystemManagingUNICourses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "SystemManager.h"
#include "Admin.h"
#include "Teacher.h"
#include "Student.h"
#include "Course.h"
#include "Assignment.h"
#include "Role.h"


using namespace std;

const size_t MAX_COMMAND_LENGTH = 256;


int main() {
    SystemManager system;
    system.loadUsersFromFile();
    system.loadCoursesFromFile();
    system.loadMailsFromFile();

    User* loggedUser = nullptr;
    MyString command;
    cout << "> ";
    while (cin >> command) {
        if (command.equals( "login")) {
            size_t id;
            MyString password;
            cin >> id >> password;

            loggedUser = system.login(id, password);
            if (loggedUser) {
                cout << "Login successful!\n";
                cout << loggedUser->getFirstName().c_str() << " " << loggedUser->getLastName().c_str()
                    << " | " << loggedUser->getRole() << " | "
                    << loggedUser->getId() << "\n";
            }
            else {
                cout << "Invalid credentials.\n";
            }
        }
        else if (command.equals( "logout")) {
            if (loggedUser) {
                cout << "Logged out.\n";
                loggedUser = nullptr;
            }
            else {
                cout << "You are not logged in.\n";
            }
        }
        else if (loggedUser) {
            // Разпознаване на команди според ролята
            if (system.isAdmin(loggedUser)) {
                executeAdminCommand(system, command, loggedUser);
            }
            else if (system.isTeacher(loggedUser)) {

                /*system.executeTeacherCommand(command, loggedUser);*/
            }
            else if (system.isStudent(loggedUser)) {
                cout << "students";
                /*system.executeStudentCommand(command, loggedUser);*/
            }
        }
        else {
            cout << "Please login first.\n";
        }

        cout << "> ";
    }
    return 0;

    /*system.saveUsersToFile("users.txt");
    system.saveCoursesToFile("Courses.txt");
    system.saveMailsToFile("Mails.txt");*/
    return 0;
}
