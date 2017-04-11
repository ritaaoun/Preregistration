#include "SqliteRepository.hpp"

SqliteRepository::SqliteRepository()
{
}

SqliteRepository::SqliteRepository(const SqliteRepository & rhs)
{
}

SqliteRepository::~SqliteRepository()
{
}

SqliteRepository & SqliteRepository::operator=(const SqliteRepository & rhs)
{
	// TODO: insert return statement here
}

void SqliteRepository::deleteUser(const AbstractUser * user) const
{
}

void SqliteRepository::deleteUser(int id) const
{
}

void SqliteRepository::updateUser(const AbstractUser * user) const
{
}

void SqliteRepository::createUser(const AbstractUser * user) const
{
}

AbstractUser SqliteRepository::getUser(int id) const
{
	return AbstractUser();
}

std::vector<AbstractUser*> SqliteRepository::getUsers() const
{
	return std::vector<AbstractUser*>();
}

void SqliteRepository::deleteDepartment(int id) const
{
}

void SqliteRepository::deleteDepartment(const Department * department) const
{
}

void SqliteRepository::updateDepartment(const Department * department) const
{
}

void SqliteRepository::createDepartment(const Department * department) const
{
}

Department SqliteRepository::getDepartment(int id) const
{
	return Department();
}

Department SqliteRepository::getUserDepartment(int userId) const
{
	return Department();
}

Department SqliteRepository::getUserDepartment(const User * user) const
{
	return Department();
}

std::vector<Department*> SqliteRepository::getAdminDepartments(const Administrator * admin) const
{
	return std::vector<Department*>();
}

std::vector<Department*> SqliteRepository::getAdminDepartments(int adminId) const
{
	return std::vector<Department*>();
}

std::vector<Department*> SqliteRepository::getDepartments() const
{
	return std::vector<Department*>();
}

void SqliteRepository::deletePrivilege(const Administrator * admin, const Department * department) const
{
}

void SqliteRepository::createPrivilege(const Administrator * admin, const Department * department) const
{
}

void SqliteRepository::deleteMessage(const AbstractMessage * message, const AbstractUser * user) const
{
}

void SqliteRepository::createMessage(const AbstractMessage * message)
{
}

std::vector<AbstractMessage*> SqliteRepository::getSentMessages(const AbstractUser * user) const
{
	return std::vector<AbstractMessage*>();
}

std::vector<AbstractMessage*> SqliteRepository::getReceivedMessages(const AbstractUser * user) const
{
	return std::vector<AbstractMessage*>();
}
