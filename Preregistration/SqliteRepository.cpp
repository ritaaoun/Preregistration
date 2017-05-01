#include "SqliteRepository.hpp"
#include <iostream>

SqliteRepository & SqliteRepository::getInstance()
{
	static SqliteRepository instance; // Guaranteed to be destroyed.
	return instance;	// Instantiated on first use.		
}

SqliteRepository::SqliteRepository()
{
	open();
}

bool SqliteRepository::open()
{
	if (sqlite3_open("registration.db", &database) == SQLITE_OK)
		return true;
	return false;
}

void SqliteRepository::close()
{
	sqlite3_close(database);
}

bool SqliteRepository::execute(const std::string & sql) const
{
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_exec(database, sql.c_str() , nullptr, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error: " << zErrMsg;
		sqlite3_free(zErrMsg);
		return false;
	}
	return true;
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
	return *this;
}

bool SqliteRepository::deleteUser(const AbstractUser * user) const
{
	std::string sql = "DELETE FROM USER WHERE ID = " + std::to_string(user->getId()) + ";";
	return execute(sql);
}

bool SqliteRepository::deleteUser(int id) const
{
	std::string sql = "DELETE FROM USER WHERE ID = " + std::to_string(id) + ";";
	return execute(sql);
}

bool SqliteRepository::updateUser(AbstractUser * user) const
{
	return true;
}

bool SqliteRepository::createUser(const AbstractUser * user) const
{
	return true;
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
	std::string sql = "DELETE FROM DEPARTMENT WHERE ID = " + std::to_string(id) + ";";
	return execute(sql);
}

bool SqliteRepository::deleteDepartment(const Department * department) const
{
	std::string sql = "DELETE FROM DEPARTMENT WHERE ID = " + std::to_string(department->getId()) + ";";
	return execute(sql);
}

bool SqliteRepository::updateDepartment(const Department * department) const
{
	return true;
}

bool SqliteRepository::createDepartment(const Department * department) const
{
	return true;
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
	return true;
}

bool SqliteRepository::createPrivilege(const Administrator * admin, const Department * department) const
{
	return true;
}

bool SqliteRepository::deleteMessage(const AbstractMessage * message, const AbstractUser * user) const
{
	return true;
}

bool SqliteRepository::createMessage(const AbstractMessage * message)
{
	return true;
}

std::vector<AbstractMessage*>*  SqliteRepository::getSentMessages(const AbstractUser * user) const
{
	return new std::vector<AbstractMessage*>();
}

std::vector<AbstractMessage*>*  SqliteRepository::getReceivedMessages(const AbstractUser * user) const
{
	return new std::vector<AbstractMessage*>();
}

int SqliteRepository::getNewId(std::string year) const
{
	return 0;
}

std::string SqliteRepository::getNewUsername(std::string username) const
{
	return "";
}