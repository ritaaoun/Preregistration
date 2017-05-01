#pragma once
#include "AbstractUser.hpp"
#include "Department.hpp"
#include "Administrator.hpp"
#include "Department.hpp"
#include "AbstractMessage.hpp"
#include <vector>
#include <string>

class AbstractRepository
{
public:
	
	virtual bool deleteUser(const AbstractUser * user) const = 0;
	virtual bool deleteUser(int id) const = 0;
	virtual bool updateUser(const AbstractUser * user) const = 0;
	virtual bool createUser(const AbstractUser * user) const = 0;
	virtual AbstractUser * getUser(int id) const = 0;
	virtual std::vector<AbstractUser *> * getUsers() const = 0;

	virtual bool deleteDepartment(int id) const = 0;
	virtual bool deleteDepartment(const Department * department) const = 0;
	virtual bool updateDepartment(const Department * department) const = 0;
	virtual bool createDepartment(const Department * department) const = 0;
	virtual Department * getDepartment(int id) const = 0;
	virtual Department * getUserDepartment(int userId) const = 0;
	virtual Department * getUserDepartment(const AbstractUser * user) const = 0;
	virtual std::vector<Department *> * getAdminDepartments(const Administrator * admin) const = 0;
	virtual std::vector<Department *> * getAdminDepartments(int adminId) const = 0;
	virtual std::vector<Department *> * getDepartments() const = 0;

	virtual bool deletePrivilege(const Administrator * admin, const Department * department) const = 0;
	virtual bool createPrivilege(const Administrator * admin, const Department * department) const = 0;

	virtual bool deleteMessage(const AbstractMessage * message, const  AbstractUser * user) const = 0;
	virtual bool createMessage(const AbstractMessage * message) = 0;
	virtual std::vector<AbstractMessage *> * getSentMessages(const AbstractUser * user) const = 0;
	virtual std::vector<AbstractMessage *> * getReceivedMessages(const AbstractUser * user) const = 0;

	virtual int getNewUserId(std::string year) const = 0;
	virtual std::string getNewUsername(std::string username) const = 0;
	virtual int getNewDepartmentId() const = 0;
};