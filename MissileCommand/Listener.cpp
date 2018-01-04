#include "Listener.h"
#include "Messenger.h"

Listener::~Listener()
{
	for (std::shared_ptr<Messenger> it : mAttachedMessengers)
	{
		if (it != nullptr)
		{
			it->RemoveListener(this);
		}
	}
}

void Listener::AttachToMessenger(std::shared_ptr<Messenger> _Messenger)
{
	_Messenger->AddListener(this);
	mAttachedMessengers.push_back(_Messenger);
}