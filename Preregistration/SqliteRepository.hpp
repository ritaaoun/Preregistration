#pragma once
#include "AbstractRepository.hpp"

class SqliteRepository : public AbstractRepository{
public:
	SqliteRepository();
	SqliteRepository(const SqliteRepository & rhs);
	virtual ~SqliteRepository();
	SqliteRepository & operator=(const SqliteRepository & rhs);

	// Inherited via AbstractRepository
	virtual void deleteUser(const AbstractUser * user) const override;
	virtual void deleteUser(int id) const override;
	virtual void updateUser(const AbstractUser * user) const override;
	virtual void createUser(const AbstractUser * user) const override;
	virtual AbstractUser getUser(int id) const override;
	virtual std::vector<AbstractUser*> getUsers() const override;
	virtual void deleteDepartment(int id) const override;
	virtual void deleteDepartment(const Department * department) const override;
	virtual void updateDepartment(const Department * department) const override;
	virtual void createDepartment(const Department * department) const override;
	virtual Department getDepartment(int id) const override;
	virtual Department getUserDepartment(int userId) const override;
	virtual Department getUserDepartment(const User * user) const override;
	virtual std::vector<Department*> getAdminDepartments(const Administrator * admin) const override;
	virtual std::vector<Department*> getAdminDepartments(int adminId) const override;
	virtual std::vector<Department*> getDepartments() const override;
	virtual void deletePrivilege(const Administrator * admin, const Department * department) const override;
	virtual void createPrivilege(const Administrator * admin, const Department * department) const override;
	virtual void deleteMessage(const AbstractMessage * message, const AbstractUser * user) const override;
	virtual void createMessage(const AbstractMessage * message) override;
	virtual std::vector<AbstractMessage*> getSentMessages(const AbstractUser * user) const override;
	virtual std::vector<AbstractMessage*> getReceivedMessages(const AbstractUser * user) const override;
};