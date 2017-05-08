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

	std::vector<AbstractMessage*> getReceivedMessages() const;
	std::vector<AbstractMessage*> getSentMessages() const;

protected:

private:
	std::vector<AbstractMessage*> m_sentMessages;
	std::vector<AbstractMessage*> m_receivedMessages;
};