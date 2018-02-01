#include "Messenger.h"
#include "Message.h"

/// <summary> 
/// Adds a listener to the Messenger. 
/// </summary>
void Messenger::AddListener(Listener* _Listener)
{
	mListeners.push_back(_Listener);
}

/// <summary> 
/// Remove a listener from the Messenger 
/// </summary>
void Messenger::RemoveListener(Listener* _Listener)
{
	unsigned int ListenerIndex = 0;
	bool ListenerFound = false;

	for (unsigned int i = 0; i < mListeners.size(); i++)
	{
		if (mListeners[i] == _Listener)
		{
			ListenerIndex = i;
			ListenerFound = true;
			break;
		}
	}

	if (ListenerFound)
	{
		mListeners.erase(mListeners.begin() + ListenerIndex);
	}
}

/// <summary> 
/// Receive a message and distribute to all listeners.
/// </summary>
void Messenger::QueueMessage(std::shared_ptr<Message> _Message)
{
	// lock the queue when pushing or popping.
	mWritingMessageLock.lock();
	mInMessageQueue.push(std::move(_Message));
	mWritingMessageLock.unlock();
}

void Messenger::TickMessenger()
{
	while (mInMessageQueue.size() > 0)
	{
		mWritingMessageLock.lock();
		mMessageQueue.push(mInMessageQueue.front());
		mInMessageQueue.pop();
		mWritingMessageLock.unlock();
	}

	while (mMessageQueue.size() > 0)
	{
		for (Listener* i : mListeners)
		{
			try
			{
				i->ReadMessage(mMessageQueue.front().get());
			}
			catch (...)
			{
				// TODO - Sinful, please fix 
			}
		}
		
		mMessageQueue.pop();
	}
}