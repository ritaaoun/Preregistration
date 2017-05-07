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
	virtual bool updateUser(AbstractUser * user) const = 0;
	virtual bool createUser(const AbstractUser * user) const = 0;
	virtual std::vector<AbstractUser *> getUsers() const = 0;
	virtual std::vector<int> getUserSections(int userId) const = 0;

	virtual bool deleteDepartment(int id) const = 0;
	virtual bool deleteDepartment(const Department * department) const = 0;
	virtual bool updateDepartment(const Department * department) const = 0;
	virtual int createDepartment(const Department * department) const = 0;
	virtual std::vector<int> getAdminDepartments(int adminId) const = 0;
	virtual std::vector<int> getDepartmentCourses(int departmentId) const = 0;
	virtual std::vector<int> getDepartmentCourseRequests(int departmentId) const = 0;
	virtual std::vector<Department *> getDepartments() const = 0;

	virtual bool deletePrivilege(const Administrator * admin, const Department * department) const = 0;
	virtual bool createPrivilege(const Administrator * admin, const Department * department) const = 0;

	virtual int createMessage(AbstractMessage * message) = 0;
	virtual std::vector<AbstractMessage *> getMessages() const = 0;
};