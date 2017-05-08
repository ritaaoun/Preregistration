#pragma once
#include "AbstractRepository.hpp"
#include <string>
#include "sqlite3.h"

class SqliteRepository : public AbstractRepository{
public:
	static SqliteRepository & getInstance();

	// Inherited via AbstractRepository
	virtual bool deleteUser(const AbstractUser * user) const override;
	virtual bool deleteUser(int id) const override;
	virtual bool updateUser(AbstractUser * user) const override;
	virtual bool createUser(const AbstractUser * user) const override;
	virtual std::vector<AbstractUser*> getUsers() const override;
	virtual std::vector<int> getUserSections(int userId) const override;

	virtual bool deleteDepartment(int id) const override;
	virtual bool deleteDepartment(const Department * department) const override;
	virtual bool updateDepartment(const Department * department) const override;
	virtual int createDepartment(const Department * department) const override;
	virtual std::vector<int> getAdminPrivileges(int adminId) const override;
	virtual std::vector<Department*> getDepartments() const override;
	virtual std::vector<int> getDepartmentCourses(int departmentId) const override;
	virtual std::vector<int> getDepartmentCourseRequests(int departmentId) const override;

	virtual bool deletePrivilege(const Administrator * admin, const Department * department) const override;
	virtual bool createPrivilege(const Administrator * admin, const Department * department) const override;

	virtual int createMessage(AbstractMessage * message) override;
	virtual std::vector<AbstractMessage *> getMessages() const override;

private :
	SqliteRepository();
	SqliteRepository(const SqliteRepository & rhs);
	virtual ~SqliteRepository();
	SqliteRepository & operator=(const SqliteRepository & rhs);
	sqlite3 *database;
	bool open();
	void close();
	bool execute(const std::string & sql) const;
	std::vector< std::vector < std::string > > query(const std::string & sql) const;
};