#pragma once
#include "AbstractMessage.hpp"
#include <vector>
class Inbox {
public:
	Inbox();
	Inbox(const Inbox & other);
	virtual ~Inbox();
	Inbox & operator=(const Inbox & rhs);

	bool updateReceivedMessages(AbstractMessage * message);
	bool updateSentMessages(AbstractMessage * message);
	bool getReceivedMessages(AbstractUser * sender, AbstractMessage::Type type);
	bool getReceivedMessages(AbstractUser * sender);
	bool getSentMessages(AbstractUser * recepient, AbstractMessage::Type type);
	bool getSentMessages(AbstractUser * recepient);

protected:

private:
	std::vector<AbstractMessage> m_sentMessages;
	std::vector<AbstractMessage> m_receivedMessages;
};