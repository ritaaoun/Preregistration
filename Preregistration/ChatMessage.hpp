#pragma once
#include "AbstractMessage.hpp"
class ChatMessage : public AbstractMessage {
	// Inherited via AbstractMessage
	virtual bool sendMessage() override;
};