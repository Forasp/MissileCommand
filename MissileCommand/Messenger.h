#pragma once
#include "Listener.h"
#include <vector>
#include <memory>
#include <queue>
#include <mutex>

class Message;

class Messenger
{
public:
	virtual void TickMessenger();
	virtual void AddListener(Listener* _Listener);
	virtual void RemoveListener(Listener* _Listener);
	virtual void QueueMessage(std::shared_ptr<Message> _Message);
protected:
	std::vector<Listener*> mListeners;
	std::queue<std::shared_ptr<Message>> mMessageQueue;
	std::mutex mWritingMessageLock;
};