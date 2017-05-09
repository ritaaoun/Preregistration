#include "SqliteRepository.hpp"
#include "Professor.hpp"
#include "Student.hpp"
#include "ChatMessage.hpp"
#include "Helper.hpp"
#include <iostream>

SqliteRepository & SqliteRepository::getInstance()
{
	static SqliteRepository instance; // Guaranteed to be destroyed.
	return instance;	// Instantiated on first use.		
}

// TODO fail handling
SqliteRepository::SqliteRepository() : database()
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

	rc = sqlite3_exec(database, sql.c_str(), nullptr, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "SQL error: " << zErrMsg;
		sqlite3_free(zErrMsg);
		return false;
	}
	return true;
}

std::vector<std::vector<std::string>> SqliteRepository::query(const std::string & sql) const
{
	sqlite3_stmt *statement;
	std::vector<std::vector<std::string> > results;

	if (sqlite3_prepare_v2(database, sql.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);

			if (result == SQLITE_ROW)
			{
				std::vector<std::string> values;
				for (int col = 0; col < cols; col++)
				{
					values.push_back((char*)sqlite3_column_text(statement, col));
				}
				results.push_back(values);
			}
			else
			{
				break;
			}
		}
		sqlite3_finalize(statement);
	}
	std::string error = sqlite3_errmsg(database);
	if (error != "not an error")
	{
		std::cerr << "SqliteRepository::query: " << sql << " " << error << std::endl;
	}
	return results;
}

SqliteRepository::SqliteRepository(const SqliteRepository & rhs)
{
}

SqliteRepository::~SqliteRepository()
{
	close();
}

SqliteRepository & SqliteRepository::operator=(const SqliteRepository & rhs)
{
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
	std::string sql = "UPDATE USER SET PASSWORD = '" + user->getPassword() + "', " +
		"FIRSTNAME = '" + user->getFirstName() + "', MIDDLENAME = '" + user->getMiddleName() + "', " +
		"LASTNAME = '" + user->getLastName() + "', STARTYEAR = '" + std::to_string(user->getStartYear()) + "', " +
		"STARTTERM = '" + std::to_string(user->getStartTerm()) + "', DEPARTMENTID = '" +
		std::to_string(user->getDepartment()->getId()) + "' WHERE ID = '" + std::to_string(user->getId()) + "';";
	return execute(sql);
}

bool SqliteRepository::createUser(const AbstractUser * user) const
{
	std::string sql = "INSERT INTO USER (ID, USERNAME, PASSWORD, FIRSTNAME, MIDDLENAME, LASTNAME, STARTYEAR, "
		"STARTTERM, TYPE, DEPARTMENTID, BIRTHDAY) VALUES ('" + std::to_string(user->getId()) + "', '" + 
		user->getUsername() + "', '" + user->getPassword() + "', '" + user->getFirstName() + "', '" + 
		user->getMiddleName() + "', '" + user->getLastName() + "', '" + std::to_string(user->getStartYear()) + "', '" + 
		std::to_string(user->getStartTerm()) + "', '" + std::to_string(user->getType()) + "', '" +
		std::to_string(user->getDepartmentId()) + "', '" + user->getBirthday() + "')";
	return execute(sql);
}

std::vector<AbstractUser*> SqliteRepository::getUsers() const
{
	std::string sql = "SELECT * FROM USER";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<AbstractUser *> out;

	for (std::vector<std::vector<std::string>>::iterator it = results.begin(); it != results.end(); ++it)
	{
		std::vector<std::string> row = *it;
		int id = Helper::stringToLong(row.at(0));
		std::string username = row.at(1);
		std::string password = row.at(2);
		std::string firstname = row.at(3);
		std::string middlename = row.at(4);
		std::string lastname = row.at(5);
		int startyear = Helper::stringToLong(row.at(6));
		Term::Term startterm = static_cast<Term::Term>(Helper::stringToLong(row.at(7)));
		AbstractUser::Type type = static_cast<AbstractUser::Type>(Helper::stringToLong(row.at(8)));
		int departmentid = Helper::stringToLong(row.at(9));
		std::string birthday = row.at(10);

		if (type == AbstractUser::ADMINISTRATOR) {
			out.push_back(new Administrator(id, username, password, firstname, middlename, lastname, startyear, startterm, departmentid, birthday));
		}
		else if (type == AbstractUser::PROFESSOR) {
			out.push_back(new Professor(id, username, password, firstname, middlename, lastname, startyear, startterm, departmentid, birthday));
		}
		else if (type == AbstractUser::STUDENT) {
			out.push_back(new Student(id, username, password, firstname, middlename, lastname, startyear, startterm, departmentid, birthday));
		}
		else {
			std::cerr << "SqliteRepository::getUsers(): invalid type " << std::to_string(type) << std::endl;
		}
	}
	return out;
}

std::vector<int> SqliteRepository::getUserSections(int userId) const
{
	std::string sql = "SELECT SECTIONCRN FROM USERSECTION WHERE USERID='" + std::to_string(userId) + "'";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<int> sections;

	for (std::vector<std::vector<std::string>>::iterator it = results.begin(); it != results.end(); ++it)
	{
		sections.push_back(Helper::stringToLong((*it).at(0)));
	}

	return sections;
}

bool SqliteRepository::deleteDepartment(int id) const
{
	std::string sql = "DELETE FROM DEPARTMENT WHERE ID = '" + std::to_string(id) + "'";
	return execute(sql);
}

bool SqliteRepository::deleteDepartment(const Department * department) const
{
	std::string sql = "DELETE FROM DEPARTMENT WHERE ID = '" + std::to_string(department->getId()) + "'";
	return execute(sql);
}

bool SqliteRepository::updateDepartment(const Department * department) const
{
	std::string sql = "UPDATE DEPARTMENT SET NAME = '" + department->getName() + "', CODE = '" +
		department->getCode() + "', FACULTYCODE = '" + department->getFacultyCode() + "' " +
		"WHERE ID = '" + std::to_string(department->getId()) + "';";
	return execute(sql);
}

int SqliteRepository::createDepartment(const Department * department) const
{
	std::string sql = "INSERT INTO DEPARTMENT (NAME, CODE, FACULTY) VALUES ('" + department->getName() +
		"', '" + department->getCode() + "', '" + department->getFacultyCode() + "')";
	if (execute(sql))
	{
		std::string sql = "SELECT MAX(ID) FROM MESSAGE";
		std::vector<std::vector<std::string>> results = query(sql);
		std::cout << "SqliteRepository::createDepartment: Successfully created department " << department->getCode() << std::endl;
		return Helper::stringToLong(results.at(0).at(0));
	}
	else
	{
		std::cerr << "SqliteRepository::createDepartment: Could not create department " << department->getCode() << std::endl;
		return -1;
	}
}

std::vector<int> SqliteRepository::getAdminPrivileges(int adminId) const
{
	std::string sql = "SELECT DEPARTMENTID FROM PRIVILEGE WHERE USERID='" + std::to_string(adminId) + "'";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<int> departments;

	for (std::vector<std::vector<std::string>>::iterator it = results.begin(); it != results.end(); ++it)
	{
		departments.push_back(Helper::stringToLong((*it).at(0)));
	}

	return departments;
}

std::vector<Department*> SqliteRepository::getDepartments() const
{
	std::string sql = "SELECT * FROM DEPARTMENT";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<Department *> out;

	for (std::vector<std::vector<std::string>>::iterator it = results.begin(); it != results.end(); ++it)
	{
		std::vector<std::string> row = *it;
		int id = Helper::stringToLong(row.at(0));
		std::string name = row.at(1);
		std::string code = row.at(2);
		std::string faculty = row.at(3);

		out.push_back(new Department(id, name, code, faculty));
	}
	return out;
}

std::vector<int> SqliteRepository::getDepartmentCourses(int departmentId) const
{
	std::string sql = "SELECT ID FROM COURSE WHERE DEPARTMENTID='" + std::to_string(departmentId) + "' AND ISREQUEST='0'";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<int> courses;

	for (std::vector<std::vector<std::string>>::iterator it = results.begin(); it != results.end(); ++it)
	{
		courses.push_back(Helper::stringToLong((*it).at(0)));
	}

	return courses;
}

std::vector<int> SqliteRepository::getDepartmentCourseRequests(int departmentId) const
{
	std::string sql = "SELECT ID FROM COURSE WHERE DEPARTMENTID='" + std::to_string(departmentId) + "' AND ISREQUEST='1'";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<int> courses;

	for (std::vector<std::vector<std::string>>::iterator it = results.begin(); it != results.end(); ++it)
	{
		courses.push_back(Helper::stringToLong((*it).at(0)));
	}

	return courses;
}

bool SqliteRepository::deletePrivilege(const Administrator * admin, const Department * department) const
{
	std::string sql = "DELETE FROM PRIVILEGE WHERE USERID = '" + std::to_string(admin->getId()) + "'"
		"AND DEPARTMENTID = '" + std::to_string(department->getId()) + "'";
	return execute(sql);
}

bool SqliteRepository::createPrivilege(const Administrator * admin, const Department * department) const
{
	std::string sql = "INSERT INTO PRIVILEGE (USERID, DEPARTMENTID) VALUES ('" + std::to_string(admin->getId()) +
		"', '" + std::to_string(department->getId()) + "')";
	return execute(sql);
}

int SqliteRepository::createMessage(AbstractMessage * message)
{
	std::string sql = "INSERT INTO MESSAGE (SENDERID, RECIPIENTID, TYPE, TOPIC, CONTENT) VALUES ('" +
		std::to_string(message->getSenderId()) + "', '" + std::to_string(message->getRecipientId()) + "', '" +
		std::to_string(message->getType()) + "', '" + message->getTopic() + "', '" + message->getContent() + "')";
	
	if (execute(sql))
	{
		std::string sql = "SELECT MAX(ID) FROM MESSAGE";
		std::vector<std::vector<std::string>> results = query(sql);
		
		return Helper::stringToLong(results.at(0).at(0));
	}
	else
	{
		return -1;
	}
}

std::vector<AbstractMessage*> SqliteRepository::getMessages() const
{
	std::string sql = "SELECT * FROM MESSAGE";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<AbstractMessage *> out;

	if (!results.empty())
	{
		for (std::vector<std::vector<std::string>>::iterator it = results.end() - 1; it != results.begin() - 1; --it)
		{
			std::vector<std::string> row = *it;
			int id = Helper::stringToLong(row.at(0));
			int senderId = Helper::stringToLong(row.at(1));
			int recipientId = Helper::stringToLong(row.at(2));
			AbstractMessage::Type type = static_cast<AbstractMessage::Type>(Helper::stringToLong(row.at(3)));
			std::string topic = row.at(4);
			std::string content = row.at(5);

			if (type == AbstractMessage::CHAT) {
				out.push_back(new ChatMessage(id, senderId, recipientId, topic, content));
			}
			else {
				std::cerr << "SqliteRepository::getMessages(): invalid type " << std::to_string(type) << std::endl;
			}
		}
	}
	return out;
}

bool SqliteRepository::deleteSection(int crn) const
{
	std::string sql = "DELETE FROM SECTION WHERE CRN = '" + std::to_string(crn) + "'";
	return execute(sql);
}

bool SqliteRepository::deleteSection(const Section * section) const
{
	return deleteSection(section->getCrn());
}

bool SqliteRepository::updateSection(const Section * section) const
{
	std::string sql = "UPDATE SECTION SET CAPACITY = '" + std::to_string(section->getSectionCapacity()) + "', ISCONFIRMED = '" +
		std::to_string(section->getStatus()) + "'";
	return execute(sql);
}

int SqliteRepository::createSection(const Section * section) const
{
	std::string sql = "INSERT INTO SECTION (COURSEID, NUMBER, CAPACITY, PROFESSORID, ISCONFIRMED) VALUES ( '" +
		std::to_string(section->getCourseId()) + "', '" + std::to_string(section->getSectionNumber()) + "', '" + 
		std::to_string(section->getSectionCapacity()) + "', '" + std::to_string(section->getProfessorId()) + "', '" +
		std::to_string(section->getStatus()) + "'";
	return execute(sql);
}

std::vector<Section*> SqliteRepository::getSections() const
{
	std::string sql = "SELECT * FROM SECTION";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<Section *> out;

	for (std::vector<std::vector<std::string>>::iterator it = results.begin(); it != results.end(); ++it)
	{
		std::vector<std::string> row = *it;
		int crn = Helper::stringToLong(row.at(0));
		int courseId = Helper::stringToLong(row.at(1));
		int number = Helper::stringToLong(row.at(2));
		int capacity = Helper::stringToLong(row.at(3));
		int professorId = Helper::stringToLong(row.at(4));
		bool isConfirmed = Helper::stringToLong(row.at(5)) == 1;
		Section::Status status;
		if (isConfirmed) {
			status = Section::DEFINITE;
		}
		else {
			status = Section::TENTATIVE;
		}

		out.push_back(new Section(crn, courseId, number, capacity, professorId, status));
	}
	return out;
}

Constraint * SqliteRepository::getSectionConstraint(int sectionCrn) const
{
	std::string sql = "SELECT * FROM CONSTRAINTSECTION WHERE SECTIONID = '" + std::to_string(sectionCrn) + "'";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<Section *> out;

	if (results.size() > 0) {
		//int crn = Helper::stringToLong(results.at(0).at(0));
		bool hasComputer = Helper::stringToLong(results.at(0).at(1)) == 1;
		bool hasSpeakers = Helper::stringToLong(results.at(0).at(2)) == 1;
		bool hasHighEnergyParticleAccelerator = Helper::stringToLong(results.at(0).at(3)) == 1;

		return new Constraint(hasComputer, hasSpeakers, hasHighEnergyParticleAccelerator);
	}
	else {
		return nullptr;
	}
}

std::vector<TimeSlot *> SqliteRepository::getSectionTimeSlots(int sectionCrn) const
{
	std::string sql = "SELECT * FROM TIMESLOTSECTION WHERE SECTIONID = '" + std::to_string(sectionCrn) + "'";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<TimeSlot *> out;

	for (std::vector<std::vector<std::string>>::const_iterator it = results.begin(); it != results.end(); ++it) {
		//int id = Helper::stringToLong(results.at(0).at(0));
		//int sectionID = Helper::stringToLong(results.at(0).at(1));
		TimeSlot::Day day = static_cast<TimeSlot::Day>(Helper::stringToLong(results.at(0).at(2)));
		int startHour = Helper::stringToLong(results.at(0).at(3));
		int startMinute = Helper::stringToLong(results.at(0).at(4));
		int endHour = Helper::stringToLong(results.at(0).at(5));
		int endMinute = Helper::stringToLong(results.at(0).at(6));

		out.push_back(new TimeSlot(day, startHour, startMinute, endHour, endMinute));
	}
	return out;
}

std::vector<Room*> SqliteRepository::getRooms() const
{
	std::string sql = "SELECT * FROM ROOM";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<Room *> out;

	for (std::vector<std::vector<std::string>>::iterator it = results.begin(); it != results.end(); ++it)
	{
		std::vector<std::string> row = *it;
		int id = Helper::stringToLong(row.at(0));
		std::string buildingCode = row.at(1);
		int number = Helper::stringToLong(row.at(2));
		int capacity = Helper::stringToLong(row.at(3));

		out.push_back(new Room(id, buildingCode, number, capacity));
	}
	return out;
}

int SqliteRepository::getSectionRoomId(int sectionCrn) const
{
	return 0;
}

Constraint * SqliteRepository::getRoomConstraint(int roomId) const
{
	std::string sql = "SELECT * FROM CONSTRAINTROOM WHERE ROOMID = '" + std::to_string(roomId) + "'";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<Section *> out;

	if (results.size() > 0) {
		//int crn = Helper::stringToLong(results.at(0).at(0));
		bool hasComputer = Helper::stringToLong(results.at(0).at(1)) == 1;
		bool hasSpeakers = Helper::stringToLong(results.at(0).at(2)) == 1;
		bool hasHighEnergyParticleAccelerator = Helper::stringToLong(results.at(0).at(3)) == 1;

		return new Constraint(hasComputer, hasSpeakers, hasHighEnergyParticleAccelerator);
	}
	else {
		return nullptr;
	}
}

std::vector<int> SqliteRepository::getRoomSectionIds(int roomId) const
{
	std::string sql = "SELECT SECTIONCRN FROM ROOMSECTION WHERE ROOMID='" + std::to_string(roomId) + "'";
	std::vector<std::vector<std::string>> results = query(sql);
	std::vector<int> sections;

	for (std::vector<std::vector<std::string>>::iterator it = results.begin(); it != results.end(); ++it)
	{
		sections.push_back(Helper::stringToLong((*it).at(0)));
	}

	return sections;
}
