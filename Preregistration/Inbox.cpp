#include "Inbox.hpp"

Inbox::Inbox() : m_sentMessages(), m_receivedMessages()
{
}

Inbox::Inbox(const Inbox & other) :
	m_receivedMessages(other.m_receivedMessages), m_sentMessages(other.m_sentMessages)
{
}

Inbox::~Inbox()
{
}

Inbox & Inbox::operator=(const Inbox & rhs)
{
	m_receivedMessages = rhs.m_receivedMessages;
	m_sentMessages = rhs.m_sentMessages;
	return *this;
}

bool Inbox::updateReceivedMessages(AbstractMessage * message)
{
	m_receivedMessages.push_back(message);
	return true;
}

bool Inbox::updateSentMessages(AbstractMessage * message)
{
	m_sentMessages.push_back(message);
	return true;
}

std::vector<AbstractMessage*> Inbox::getReceivedMessages() const
{
	return m_receivedMessages;
}

std::vector<AbstractMessage*> Inbox::getSentMessages() const
{
	return m_sentMessages;
}