#pragma once
#include "User.h"
#include "MyString.h"
#include "SystemManager.h"



class Teacher : public User {
private:
    size_t* courseIds;
    size_t courseCount;

public:
    Teacher();
    Teacher(const MyString firstName, const MyString lastName, size_t id, const MyString password);
    ~Teacher();
    Teacher(const Teacher& other);
    Teacher& operator=(const Teacher& other);


    void addCourse(const size_t courseId);
    // 1. Създаване на нов курс
    void createCourse(SystemManager& manager, const MyString courseName, const MyString enrollPassword);

    // 2. Създаване на задание в курс
    void createAssignment(SystemManager& manager, const MyString courseName, const MyString assignmentName);

    // 3. Записване на студент
    void enrollStudent(SystemManager& manager, const MyString courseName, size_t studentId);

    // 4. Задаване на парола за самозаписване
    void setEnrollmentPassword(SystemManager& manager, const MyString courseName, const MyString newPassword);

    // 5. Оценяване на задания
    void gradeAssignment(SystemManager& system, const MyString courseName, const MyString assignmentName, size_t studentId, double grade);

    // 6. Изпращане на съобщения до студенти в курс
    void sendMessageToCourseStudents(SystemManager& manager, const MyString courseName, const MyString message);

    //7. Преглед на отговори
    void viewAnswers(SystemManager& system, const MyString courseName, const MyString assignmentName);
    Role getRole() const override;
};