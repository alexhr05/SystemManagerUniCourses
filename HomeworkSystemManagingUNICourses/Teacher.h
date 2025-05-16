#pragma once
#include "User.h"
#include "MyString.h"
#include "SystemManager.h"



class Teacher : public User {
public:
    Teacher(const MyString firstName, const MyString lastName, size_t id, const MyString password);

    // 1. Създаване на нов курс
    void createCourse(SystemManager& manager, const MyString& courseName, const MyString& enrollPassword);

    // 2. Създаване на задание в курс
    void createAssignment(SystemManager& manager, const MyString& courseName, const MyString& assignmentName);

    // 3. Записване на студент
    void enrollStudent(SystemManager& manager, const MyString& courseName, size_t studentId);

    // 4. Задаване на парола за самозаписване
    void setEnrollPassword(SystemManager& manager, const MyString& courseName, const MyString& newPassword);

    // 5. Оценяване на задания
    void gradeAssignment(SystemManager& manager, const MyString& courseName, const MyString& assignmentName,
        size_t studentId, double grade, const MyString& feedback);

    // 6. Изпращане на съобщения до студенти в курс
    void sendMessageToCourseStudents(SystemManager& manager, const MyString& courseName, const MyString& message);
};