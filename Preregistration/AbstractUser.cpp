#include "AbstractUser.hpp"
#include "Server.hpp"

int AbstractUser::getId() const
{
	return m_id;
}

std::string AbstractUser::getUsername() const
{
	return m_username;
}

bool AbstractUser::checkPassword(const std::string & password) const
{
	return m_password == password;
}

std::string AbstractUser::getPassword() const
{
	return m_password;
}
 
void AbstractUser::setPassword(const std::string & password)
{
	m_password = password;
	Server::getInstance().repository->updateUser(this);
}

void AbstractUser::resetPassword()
{
	m_password = m_birthday;
	Server::getInstance().repository->updateUser(this);
}

std::string AbstractUser::getFirstName() const
{
	return m_firstName;
}

void AbstractUser::setFirstName(const std::string & firstName)
{
	m_firstName = firstName;
	Server::getInstance().repository->updateUser(this);
}

std::string AbstractUser::getMiddleName() const
{
	return m_middleName;
}

void AbstractUser::setMiddleName(const std::string & middleName)
{
	m_middleName = middleName;
	Server::getInstance().repository->updateUser(this);
}

std::string AbstractUser::getLastName() const
{
	return m_lastName;
}

void AbstractUser::setLastName(const std::string & lastName)
{
	m_lastName = lastName;
	Server::getInstance().repository->updateUser(this);
}

int AbstractUser::getStartYear() const
{
	return m_startYear;
}

void AbstractUser::setStartYear(int year)
{
	m_startYear = year;
	Server::getInstance().repository->updateUser(this);
}

Term::Term AbstractUser::getStartTerm() const
{
	return m_startTerm;
}

void AbstractUser::setStartTerm(Term::Term startTerm)
{
	m_startTerm = startTerm;
	Server::getInstance().repository->updateUser(this);
}

AbstractUser::Type AbstractUser::getType() const
{
	return m_type;
}

void AbstractUser::setType(Type type)
{
	m_type = type;
	Server::getInstance().repository->updateUser(this);
}

Department * AbstractUser::getDepartment()
{
	if (m_department == nullptr) {
		m_department = Server::getInstance().data.getDepartment(m_departmentId);
	}
	return m_department;
}

int AbstractUser::getDepartmentId() const
{
	return m_departmentId;
}

void AbstractUser::setDepartmentId(int departmentId)
{
	m_departmentId = departmentId;
	m_department = nullptr;
	Server::getInstance().repository->updateUser(this);
}

std::string AbstractUser::getBirthday() const
{
	return m_birthday;
}

void AbstractUser::setBirthday(const std::string & birthday)
{
	m_birthday = birthday;
	Server::getInstance().repository->updateUser(this);
}

std::vector<AbstractMessage*> AbstractUser::getSentMessages()
{
	return m_inbox.getSentMessages();
}

std::vector<AbstractMessage*> AbstractUser::getReceivedMessages()
{
	return m_inbox.getReceivedMessages();
}

bool AbstractUser::updateSentMessages(AbstractMessage * message)
{
	return m_inbox.updateSentMessages(message);
}

bool AbstractUser::updateReceivedMessages(AbstractMessage * message)
{
	return m_inbox.updateReceivedMessages(message);
}

AbstractUser::AbstractUser() : m_id(), m_username(), m_password(), m_firstName(), m_middleName(), m_lastName(),
	m_startYear(0), m_startTerm(Term::TERM_END), m_type(TYPE_END), m_department(nullptr), m_birthday(), m_inbox()
{
}

AbstractUser::AbstractUser(const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, Type userType, int departmentId, const std::string & birthday) :
	m_id(Server::getInstance().data.getNewUserId(startYear)), m_password(birthday), m_firstName(firstName),
	m_middleName(middleName), m_lastName(lastName), m_startYear(startYear),	m_startTerm(startTerm), m_type(userType), 
	m_departmentId(departmentId), m_department(nullptr), m_birthday(birthday), m_inbox()
{
	std::string username;
	username.push_back(tolower(firstName[0]));
	username.push_back(tolower(middleName[0]));
	username.push_back(tolower(lastName[0]));
	m_username = Server::getInstance().data.getNewUsername(username);

	Server::getInstance().repository->createUser(this);
}

AbstractUser::AbstractUser(int id, const std::string & username, const std::string & password, const std::string & firstName,
	const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm, Type userType,
	int departmentId, const std::string & birthday) :
	m_id(id), m_username(username), m_password(password), m_firstName(firstName), m_middleName(middleName),
	m_lastName(lastName), m_startYear(startYear), m_startTerm(startTerm), m_type(userType), m_departmentId(departmentId),
	m_department(nullptr), m_birthday(birthday), m_inbox()
{
}

AbstractUser::AbstractUser(const AbstractUser & other) :
	m_id(other.m_id), m_username(other.m_username), m_password(other.m_password), m_firstName(other.m_firstName),
	m_middleName(other.m_middleName), m_lastName(other.m_lastName), m_startYear(other.m_startYear),
	m_startTerm(other.m_startTerm), m_type(other.m_type), m_departmentId(other.m_departmentId),
	m_department(other.m_department), m_birthday(other.m_birthday), m_inbox(other.m_inbox)
{
}

AbstractUser::~AbstractUser()
{
}

AbstractUser & AbstractUser::operator=(const AbstractUser & rhs)
{
	m_id = rhs.m_id;
	m_username = rhs.m_username;
	m_password = rhs.m_password;
	m_firstName = rhs.m_firstName;
	m_middleName = rhs.m_middleName;
	m_lastName = rhs.m_lastName;
	m_startYear = rhs.m_startYear;
	m_startTerm = rhs.m_startTerm;
	m_type = rhs.m_type;
	m_departmentId = rhs.m_departmentId;
	m_department = rhs.m_department;
	m_birthday = rhs.m_birthday;
	m_inbox = rhs.m_inbox;
	return *this;
}
