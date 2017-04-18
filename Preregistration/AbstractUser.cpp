#include "AbstractUser.hpp"

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

void AbstractUser::setPassword(const std::string & password)
{
	m_password = password;
}

std::string AbstractUser::getFirstName() const
{
	return m_firstName;
}

void AbstractUser::setFirstName(const std::string & firstName)
{
	m_firstName = firstName;
}

std::string AbstractUser::getMiddleName() const
{
	return m_middleName;
}

void AbstractUser::setMiddleName(const std::string & middleName)
{
	m_middleName = middleName;
}

std::string AbstractUser::getLastName() const
{
	return m_lastName;
}

void AbstractUser::setLastName(const std::string & lastName)
{
	m_lastName = lastName;
}

int AbstractUser::getStartYear() const
{
	return m_startYear;
}

void AbstractUser::setStartYear(int year)
{
	m_startYear = year;
}

Term::Term AbstractUser::getStartTerm() const
{
	return m_startTerm;
}

void AbstractUser::setStartTerm(Term::Term startTerm)
{
	m_startTerm = startTerm;
}

AbstractUser::Type AbstractUser::getType() const
{
	return m_type;
}

void AbstractUser::setType(Type type)
{
	m_type = type;
}

Department * AbstractUser::getDepartment() const
{
	return m_department;
}

void AbstractUser::setDepartment(Department * department)
{
	m_department = department;
}

std::string AbstractUser::getBirthday() const
{
	return m_birthday;
}

void AbstractUser::setBirthday(const std::string & birthday)
{
	m_birthday = birthday;
}

bool AbstractUser::updateSentMessages(AbstractMessage * message)
{
	return m_inbox.updateSentMessages(message);
}

bool AbstractUser::updateReceivedMessages(AbstractMessage * message)
{
	return m_inbox.updateReceivedMessages(message);
}

AbstractUser::AbstractUser() : m_id(0), m_username(), m_password(), m_firstName(), m_middleName(), m_lastName(),
	m_startYear(0), m_startTerm(Term::TERM_END), m_type(TYPE_END), m_department(nullptr), m_birthday(), m_inbox(0)
{
}

AbstractUser::AbstractUser(const std::string & firstName, const std::string & middleName, const std::string & lastName,
	int startYear, Term::Term startTerm, Type userType, Department * department, const std::string & birthday) :
	m_id(0), m_username(), m_password(birthday), m_firstName(firstName), m_middleName(middleName), m_lastName(lastName), m_startYear(startYear),
	m_startTerm(Term::TERM_END), m_type(TYPE_END), m_department(nullptr), m_birthday(birthday), m_inbox(0)
{
}

AbstractUser::AbstractUser(int id, const std::string & firstName, const std::string & middleName, const std::string & lastName, int startYear, Term::Term startTerm, Type userType, Department * department, const std::string & birthday)
{
}

AbstractUser::AbstractUser(const AbstractUser & other)
{
}

AbstractUser::~AbstractUser()
{
}

AbstractUser & AbstractUser::operator=(const AbstractUser & rhs)
{
	// TODO: insert return statement here
}
