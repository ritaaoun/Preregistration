#pragma once
#include "AbstractUser.hpp"
#include <string>

class AbstractMessage {
public:
	enum Type { Chat, CapacityRequest, SectionRequest, EnrollmentRequest, TYPE_END };

	virtual bool sendMessage() = 0;

protected:
	AbstractUser * m_sender;
	AbstractUser * m_recepient;
	std::string m_title;
	std::string m_content;
	Type m_type;

private:
};
