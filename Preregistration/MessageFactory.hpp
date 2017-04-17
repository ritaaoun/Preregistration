#pragma once
#include "AbstractMessage.hpp"
class MessageFactory {
public:
	static AbstractMessage * createMessage(AbstractMessage::Type type);
};