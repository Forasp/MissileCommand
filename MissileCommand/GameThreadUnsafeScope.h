#pragma once

class Game;

class GameThreadUnsafeScope
{
public:
	GameThreadUnsafeScope(Game* _Game)
	{
		Lock(_Game);
	}
	~GameThreadUnsafeScope()
	{
		Unlock();
	}
private:
	void Lock(Game* _Game);
	void Unlock();
	Game* mGamePointer;
};