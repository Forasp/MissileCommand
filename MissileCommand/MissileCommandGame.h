#pragma once
#include "Game.h"

class MissileCommandGame : public Game
{
public:
	MissileCommandGame(sf::RenderWindow* _RenderWindow) : Game()
	{
		InitializeGame(_RenderWindow);
	}
	std::shared_ptr<World> GetNewWorld();

	void ReadMessage(Message* _Message);

protected:
	void InitializeGame(sf::RenderWindow* _RenderWindow);
};