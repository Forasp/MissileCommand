#pragma once
#include <vector>
#include <memory>

class Message;
class Messenger;

class Listener
{
public:
	void AttachToMessenger(std::shared_ptr<Messenger> _Messenger);
	virtual void ReadMessage(Message* _Message) = 0;
protected:
	~Listener();
	std::vector<std::shared_ptr<Messenger>> mAttachedMessengers;
};