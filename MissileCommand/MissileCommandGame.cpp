#include "MissileCommandGame.h"
#include "MissileCommandWorld.h"
#include "Messenger.h"
#include "Message.h"
#include <memory>

std::shared_ptr<World> MissileCommandGame::GetNewWorld()
{
	return std::make_shared<MissileCommandWorld>(this);
}

void MissileCommandGame::InitializeGame(sf::RenderWindow* _RenderWindow)
{
	Game::InitializeGame(_RenderWindow);

	AttachToMessenger(GetMessenger("KeyEvents"));
	AttachToMessenger(GetMessenger("GlobalEvents"));
}