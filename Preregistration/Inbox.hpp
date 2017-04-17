#pragma once
#include "AbstractMessage.hpp"
#include <vector>
class Inbox {
public:
	
	void updateReceivedMessages(AbstractMessage * message);
	void updateSentMessages(AbstractMessage * message);
	void getReceivedMessages(AbstractUser * sender, AbstractMessage::Type type);
	void getReceivedMessages(AbstractUser * sender);
	void getSentMessages(AbstractUser * recepient, AbstractMessage::Type type);
	void getSentMessages(AbstractUser * recepient);

private:
	int m_userId;
	void updateInbox();
	std::vector<AbstractMessage> m_sentMessages;
	std::vector<AbstractMessage> m_receivedMessages;
};