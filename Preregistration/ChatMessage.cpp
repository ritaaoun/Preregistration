#include "ChatMessage.hpp"

ChatMessage::ChatMessage() : AbstractMessage()
{
}

ChatMessage::ChatMessage(int id, int senderId, int recipientId, const std::string & topic, const std::string & content) :
	AbstractMessage(id, senderId, recipientId, CHAT, topic, content)
{
}

ChatMessage::ChatMessage(AbstractUser * sender, AbstractUser * recipient, const std::string & topic, const std::string & content) :
	AbstractMessage(sender, recipient, CHAT, topic, content)
{
}

ChatMessage::ChatMessage(const AbstractMessage & other) :
	AbstractMessage(other)
{
}

ChatMessage::~ChatMessage()
{
}

ChatMessage & ChatMessage::operator=(const AbstractMessage & rhs)
{
	AbstractMessage::operator=(rhs);
	return *this;
}
