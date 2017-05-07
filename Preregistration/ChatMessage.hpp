#pragma once
#include "AbstractMessage.hpp"
class ChatMessage : public AbstractMessage {
public:
	ChatMessage(int id, int senderId, int recipientId, const std::string & topic, const std::string & content);
	ChatMessage(AbstractUser * sender, AbstractUser * recipient, const std::string & topic, const std::string & content);

protected:
	ChatMessage();
	ChatMessage(const AbstractMessage & other);
	~ChatMessage();
	ChatMessage & operator=(const AbstractMessage & rhs);
};