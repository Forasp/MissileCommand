#include "GameThreadUnsafeScope.h"
#include "Game.h"
#include "Message.h"

void GameThreadUnsafeScope::Lock(Game* _Game)
{
	if (_Game)
	{
		mGamePointer = _Game;
		mGamePointer->LockAllThreads();
	}
}

void GameThreadUnsafeScope::Unlock()
{
	mGamePointer->UnlockAllThreads();
}