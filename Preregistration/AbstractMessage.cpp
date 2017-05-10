#include "AbstractMessage.hpp"
#include "Server.hpp"

int AbstractMessage::getId() const
{
	return m_id;
}

AbstractUser * AbstractMessage::getSender()
{
	if (m_sender == nullptr) {
		m_sender = Server::getInstance().data.getUser(m_senderId);
	}
	return m_sender;
}

AbstractUser * AbstractMessage::getRecipient()
{
	if (m_recipient == nullptr) {
		m_recipient = Server::getInstance().data.getUser(m_recipientId);
	}
	return m_recipient;
}

int AbstractMessage::getSenderId() const
{
	return m_senderId;
}

int AbstractMessage::getRecipientId() const
{
	return m_recipientId;
}

std::string AbstractMessage::getTopic() const
{
	return m_topic;
}

void AbstractMessage::setTopic(const std::string & topic)
{
	m_topic = topic;
}

std::string AbstractMessage::getContent() const
{
	return m_content;
}

void AbstractMessage::setContent(const std::string & content)
{
	m_content = content;
}

AbstractMessage::Type AbstractMessage::getType() const
{
	return m_type;
}

AbstractMessage::AbstractMessage() : m_id(), m_senderId(), m_sender(), m_recipientId(), m_recipient(), m_type(), m_topic(), m_content()
{
}

AbstractMessage::AbstractMessage(AbstractUser * sender, AbstractUser * recipient, Type type, const std::string & topic, const std::string & content) :
	m_senderId(sender->getId()), m_sender(sender), m_recipientId(recipient->getId()), m_recipient(recipient), m_type(type), m_topic(topic), m_content(content)
{
	m_id = Server::getInstance().repository->createMessage(this);
	Server::getInstance().repository->createMessage(this);
}

AbstractMessage::AbstractMessage(int id, int senderId, int recipientId, Type type, const std::string & topic, const std::string & content) :
	m_id(id), m_senderId(senderId), m_sender(nullptr), m_recipientId(recipientId), m_recipient(nullptr), m_type(type), m_topic(topic), m_content(content)
{
}

AbstractMessage::AbstractMessage(const AbstractMessage & other) :
	m_id(other.m_id), m_sender(other.m_sender), m_recipient(other.m_recipient), m_type(other.m_type), m_topic(other.m_topic), m_content(other.m_topic)
{
}

AbstractMessage::~AbstractMessage()
{
}

AbstractMessage & AbstractMessage::operator=(const AbstractMessage & rhs)
{
	m_id = rhs.m_id;
	m_sender = rhs.m_sender;
	m_recipient = rhs.m_recipient;
	m_type = rhs.m_type;
	m_topic = rhs.m_topic;
	m_content = rhs.m_content;
	return *this;
}
