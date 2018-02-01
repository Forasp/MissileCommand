#include "MissileCommandGame.h"
#include "MissileCommandWorld.h"
#include "MainMenuWorld.h"
#include "Messenger.h"
#include "Message.h"
#include <memory>

std::shared_ptr<World> MissileCommandGame::GetNewWorld()
{
	return std::make_shared<MainMenuWorld>(this);
}

void MissileCommandGame::InitializeGame(sf::RenderWindow* _RenderWindow)
{
	Game::InitializeGame(_RenderWindow);

	AttachToMessenger(GetMessenger("KeyEvents"));
	AttachToMessenger(GetMessenger("GlobalEvents"));
}

/// <summary> 
/// Interprets messages passed.
/// </summary>
void MissileCommandGame::ReadMessage(Message* _Message)
{
	switch (_Message->GetMessageType())
	{
	case MESSAGE_TYPE_INVALID:
		return;
		break;
	case MESSAGE_TYPE_INPUT:
		CheckControls(_Message->GetMessageDouble());
		break;
	case MESSAGE_TYPE_DOUBLE:
		/*if (_Message->GetMessageDouble() == RESTART_LEVEL)
		{
			std::shared_ptr<World> WorldCopy = mCurrentWorld;

			mCurrentWorld = GetNewWorld();
		}*/
		break;
	case MESSAGE_TYPE_STRING:

		break;
	case MESSAGE_TYPE_FULL:
		if (_Message->GetMessageString().compare("BeginGame") == 0)
		{
			std::shared_ptr<World> WorldCopy = mCurrentWorld;

			mCurrentWorld = std::make_shared<MissileCommandWorld>(this);
		}

		break;
	case MESSAGE_TYPE_QUIT:
		//std::cout << _Message->GetMessageString(); // -TODO- Implement a logging file so this can be written to it on exit.
		//EndGame(); // Quit
		break;
	default:

		break;
	}

	Game::ReadMessage(_Message);
}