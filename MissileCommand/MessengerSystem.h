#pragma once
#include <memory>
#include <map>
#include <string>

class Message;
class Messenger;

class MessengerSystem
{
public:
	void TickMessengers();
	void QueueMessage(std::string _MessengerName, std::shared_ptr<Message> _Message);

	std::shared_ptr<Messenger> GetMessenger(std::string _MessengerName);

protected:
	std::map<std::string, std::shared_ptr<Messenger>> mAllMessengers;
};
