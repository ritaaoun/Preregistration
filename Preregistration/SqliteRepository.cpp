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

bool SqliteRepository::deleteUser(const AbstractUser * user) const
{
}

bool SqliteRepository::deleteUser(int id) const
{
}

bool SqliteRepository::updateUser(const AbstractUser * user) const
{
}

bool SqliteRepository::createUser(const AbstractUser * user) const
{
}

AbstractUser* SqliteRepository::getUser(int id) const
{
	return new Administrator();
}

std::vector<AbstractUser*>* SqliteRepository::getUsers() const
{
	return new std::vector<AbstractUser*>();
}

bool SqliteRepository::deleteDepartment(int id) const
{
}

bool SqliteRepository::deleteDepartment(const Department * department) const
{
}

bool SqliteRepository::updateDepartment(const Department * department) const
{
}

bool SqliteRepository::createDepartment(const Department * department) const
{
}

Department* SqliteRepository::getDepartment(int id) const
{
	return new Department();
}

Department* SqliteRepository::getUserDepartment(int userId) const
{
	return new Department();
}

Department* SqliteRepository::getUserDepartment(const AbstractUser * user) const
{
	return new Department();
}

std::vector<Department*>* SqliteRepository::getAdminDepartments(const Administrator * admin) const
{
	return new std::vector<Department*>();
}

std::vector<Department*>* SqliteRepository::getAdminDepartments(int adminId) const
{
	return new std::vector<Department*>();
}

std::vector<Department*>* SqliteRepository::getDepartments() const
{
	return new std::vector<Department*>();
}

bool SqliteRepository::deletePrivilege(const Administrator * admin, const Department * department) const
{
}

bool SqliteRepository::createPrivilege(const Administrator * admin, const Department * department) const
{
}

bool SqliteRepository::deleteMessage(const AbstractMessage * message, const AbstractUser * user) const
{
}

bool SqliteRepository::createMessage(const AbstractMessage * message)
{
}

std::vector<AbstractMessage*>*  SqliteRepository::getSentMessages(const AbstractUser * user) const
{
	return new std::vector<AbstractMessage*>();
}

std::vector<AbstractMessage*>*  SqliteRepository::getReceivedMessages(const AbstractUser * user) const
{
	return new std::vector<AbstractMessage*>();
}

int SqliteRepository::getLastId(std::string year) const
{
	return 0;
}

std::string SqliteRepository::getLastUsername(std::string username) const
{
	return "";
}