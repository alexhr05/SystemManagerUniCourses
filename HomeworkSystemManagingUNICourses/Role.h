#pragma once

enum class Role {
    Admin,
    Teacher,
    Student
};

std::ostream& operator<<(std::ostream& os, const Role& role) {
    switch (role) {
    case Role::Admin:   os << "Admin"; break;
    case Role::Teacher: os << "Teacher"; break;
    case Role::Student: os << "Student"; break;
    default:            os << "Unknown"; break;
    }
    return os;
}