#include "Admin.h"
#include "User.h"
#include "Mail.h"
#include "Role.h"
#include <ctime>


Admin::Admin(const MyString firstName, const MyString lastName, size_t userId, const MyString password) : User(firstName,lastName,userId, password) {}

void Admin::sendGlobalMessage(const MyString content, User** allUsers, size_t userCount) {
	for (size_t i = 0; i < userCount; i++) {
		if (allUsers[i]->getId() != this->getId()) {
			allUsers[i]->receiveMessage(Mail("admin",content));
		}
	}
}

Role Admin::getRole() const {
	return Role::Admin;
}
