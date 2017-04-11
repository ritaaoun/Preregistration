#pragma once
#include "AbstractUser.hpp"
#include "Department.hpp"
#include "Administrator.hpp"
#include "Department.hpp"
#include "AbstractMessage.hpp"
#include <vector>

class AbstractRepository
{
public:

	virtual void deleteUser(const AbstractUser * user) const = 0;
	virtual void deleteUser(int id) const = 0;
	virtual void updateUser(const AbstractUser * user) const = 0;
	virtual void createUser(const AbstractUser * user) const = 0;
	virtual AbstractUser getUser(int id) const = 0;
	virtual std::vector<AbstractUser *> getUsers() const = 0;

	virtual void deleteDepartment(int id) const = 0;
	virtual void deleteDepartment(const Department * department) const = 0;
	virtual void updateDepartment(const Department * department) const = 0;
	virtual void createDepartment(const Department * department) const = 0;
	virtual Department getDepartment(int id) const = 0;
	virtual Department getUserDepartment(int userId) const = 0;
	virtual Department getUserDepartment(const User * user) const = 0;
	virtual std::vector<Department *> getAdminDepartments(const Administrator * admin) const = 0;
	virtual std::vector<Department *> getAdminDepartments(int adminId) const = 0;
	virtual std::vector<Department *> getDepartments() const = 0;

	virtual void deletePrivilege(const Administrator * admin, const Department * department) const = 0;
	virtual void createPrivilege(const Administrator * admin, const Department * department) const = 0;

	virtual void deleteMessage(const AbstractMessage * message, const  AbstractUser * user) const = 0;
	virtual void createMessage(const AbstractMessage * message) = 0;
	virtual std::vector<AbstractMessage *> getSentMessages(const AbstractUser * user) const = 0;
	virtual std::vector<AbstractMessage *> getReceivedMessages(const AbstractUser * user) const = 0;

};