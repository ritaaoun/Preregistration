#pragma once
#include <string>

class AbstractUser;

class AbstractMessage {
public:
	enum Type { CHAT, CAPACITYREQUEST, SECTIONREQUEST, ENROLLMENTREQUEST, TYPE_END };

	int getId() const;
	AbstractUser * getSender();
	AbstractUser * getRecipient();
	int getSenderId() const;
	int getRecipientId() const;

	std::string getTopic() const;
	void setTopic(const std::string & title);

	std::string getContent() const;
	void setContent(const std::string & content);

	Type getType() const;

	virtual ~AbstractMessage();

protected:
	AbstractMessage();
	AbstractMessage(AbstractUser * sender, AbstractUser * recipient, Type type, const std::string & topic, const std::string & content);
	AbstractMessage(int id, int senderId, int recipientId, Type type, const std::string & topic, const std::string & content);
	AbstractMessage(const AbstractMessage & other);
	AbstractMessage & operator=(const AbstractMessage & rhs);

private:
	int m_id;
	int m_senderId;
	AbstractUser * m_sender;
	int m_recipientId;
	AbstractUser * m_recipient;
	Type m_type;
	std::string m_topic;
	std::string m_content;
};
