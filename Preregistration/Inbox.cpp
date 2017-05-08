#include "Inbox.hpp"

Inbox::Inbox() : m_sentMessages(), m_receivedMessages()
{
}

Inbox::Inbox(const Inbox & other)
{
}

Inbox::~Inbox()
{
}

Inbox & Inbox::operator=(const Inbox & rhs)
{
	// TODO: insert return statement here
	return *this;
}

bool Inbox::updateReceivedMessages(AbstractMessage * message)
{
	return false;
}

bool Inbox::updateSentMessages(AbstractMessage * message)
{
	return false;
}

bool Inbox::getReceivedMessages(AbstractUser * sender, AbstractMessage::Type type)
{
	return false;
}

bool Inbox::getReceivedMessages(AbstractUser * sender)
{
	return false;
}

bool Inbox::getSentMessages(AbstractUser * recepient, AbstractMessage::Type type)
{
	return false;
}

bool Inbox::getSentMessages(AbstractUser * recepient)
{
	return false;
}