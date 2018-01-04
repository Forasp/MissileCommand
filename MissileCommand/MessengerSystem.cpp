//////////////////////////////////////////////////////////////////////////////////////
// MessengerSystem
// - The messenger system is responsible for queueing messages to appropriate
//    messengers, handing out handles to messengers, and ticking messengers.
//////////////////////////////////////////////////////////////////////////////////////

#include "MessengerSystem.h"
#include "Messenger.h"

// Queue a message to the appropriate messenger based on ID
void MessengerSystem::QueueMessage(std::string _MessengerName, std::shared_ptr<Message> _Message)
{
	GetMessenger(_MessengerName)->QueueMessage(_Message);
}

// Gets a handle to a messenger, if the messenger doesn't exist, create it.
std::shared_ptr<Messenger> MessengerSystem::GetMessenger(std::string _MessengerName)
{
	if (mAllMessengers.find(_MessengerName) == mAllMessengers.end())
	{
		mAllMessengers.emplace(_MessengerName, std::make_shared<Messenger>());
	}

	return mAllMessengers.find(_MessengerName)->second;
}

// Ticks all the messengers.
void MessengerSystem::TickMessengers()
{
	for (std::pair<std::string, std::shared_ptr<Messenger>> i : mAllMessengers)
	{
		i.second->TickMessenger();
	}
}