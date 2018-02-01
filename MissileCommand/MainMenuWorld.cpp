#include "MainMenuWorld.h"

#include "Game.h"
#include "GameObject.h"
#include "Controller.h"
#include "Messenger.h"
#include "Message.h"
#include "GameThreadUnsafeScope.h"
#include "ButtonObject.h"
#include "MainMenuBackgroundObject.h"

void MainMenuWorld::Initialize()
{
	// Construct our world here.
	mBackground = std::make_shared<MainMenuBackgroundObject>(MainMenuBackgroundObject(mGame));

	std::shared_ptr<ButtonObject> StartButton = std::make_shared<ButtonObject>(mGame, "StartButton", "Resources\\Start_button.png");
	StartButton->SetPosition(sf::VideoMode::getDesktopMode().width / 5 * 4, sf::VideoMode::getDesktopMode().height / 10 * 8.5);
	StartButton->SetSize(sf::VideoMode::getDesktopMode().width / 4, sf::VideoMode::getDesktopMode().width / 15);

	mButtonsMutex.lock();
	mButtons.push_back(StartButton);
	mButtonsMutex.unlock();

	std::shared_ptr<ButtonObject> QuitButton = std::make_shared<ButtonObject>(mGame, "QuitButton", "Resources\\Xbutton1.png");
	QuitButton->SetPosition(sf::VideoMode::getDesktopMode().width * 0.95, sf::VideoMode::getDesktopMode().height * 0.05);
	QuitButton->SetSize(sf::VideoMode::getDesktopMode().width * 0.05, sf::VideoMode::getDesktopMode().width * 0.05);

	mButtonsMutex.lock();
	mButtons.push_back(QuitButton);
	mButtonsMutex.unlock();

	// Position assets

	//mTurret->SetPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 10 * 9);
	//mTurret->SetSize(sf::VideoMode::getDesktopMode().width / 15, sf::VideoMode::getDesktopMode().width / 15);

	mBackground->SetPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
	mBackground->SetSize(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

	AttachToMessenger(mGame->GetMessenger("MouseEvents"));
	AttachToMessenger(mGame->GetMessenger("ButtonEvents"));

	mTimeBetweenMissiles = 3.0;
	mTimeSinceLastMissile = 0;
}

MainMenuWorld::~MainMenuWorld()
{
	return;
}

/// <summary> 
/// Calls RenderTick on graphics scenegraph.
/// </summary>
void MainMenuWorld::RenderTick(sf::RenderWindow* _RenderWindow)
{
	// render Background
	mBackground->RenderTick(_RenderWindow);

	// Render Missiles outbound
	for (int i = 0; i < mButtons.size(); i++)
	{
		mButtons[i]->RenderTick(_RenderWindow);
	}
}

/// <summary> 
/// Ticks all objects in traditional scene graph.
/// </summary>
void MainMenuWorld::Tick(sf::Time _DeltaTime)
{
	// render Background
	mBackground->Tick(_DeltaTime);

	// Render Missiles outbound
	mButtonsMutex.lock();
	for (int i = 0; i < mButtons.size(); i++)
	{
		mButtons[i]->Tick(_DeltaTime);
	}
	mButtonsMutex.unlock();
}

/// <summary> 
/// Checks controls and ticks all controllers.
/// </summary>
void MainMenuWorld::ControllerTick(sf::Time _DeltaTime)
{
	CheckControls();

	// render Background
	mBackground->ControllerTick(_DeltaTime);

	// Render Missiles outbound
	mButtonsMutex.lock();
	for (int i = 0; i < mButtons.size(); i++)
	{
		mButtons[i]->ControllerTick(_DeltaTime);
	}
	mButtonsMutex.unlock();
}

/// <summary> 
/// Checks only for controls expected by the world.
/// </summary>
void MainMenuWorld::CheckControls(int _OverrideControl)
{
	if (_OverrideControl == sf::Keyboard::Escape)
	{
		mGame->QueueMessage("GlobalEvents", std::make_unique<Message>(MESSAGE_TYPE_QUIT, std::string("Escape key pressed.")));
	}
}

/// <summary> 
/// Interprets messages passed.
/// </summary>
void MainMenuWorld::ReadMessage(Message* _Message)
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
		if (_Message->GetMessageDouble() == COLLISION_WITH_SELF)
		{
			mGame->QueueMessage("GlobalEvents", std::make_unique<Message>(MESSAGE_TYPE_DOUBLE, (double)RESTART_LEVEL));
		}
		break;
	case MESSAGE_TYPE_STRING:

		break;
	case MESSAGE_TYPE_BUTTON_EVENT:
		if (_Message->GetMessageString().compare("StartButton") == 0)
		{
			// Queue Message
			if (mGame != nullptr)
			{
				mGame->QueueMessage("GlobalEvents", std::make_unique<Message>(MESSAGE_TYPE_FULL, std::string("BeginGame")));
			}
		}
		if (_Message->GetMessageString().compare("QuitButton") == 0)
		{
			// Queue Message
			if (mGame != nullptr)
			{
				mGame->QueueMessage("GlobalEvents", std::make_unique<Message>(MESSAGE_TYPE_QUIT, std::string("Escape key pressed.")));
			}
		}
		break;
		// If message is a mouse event
	case MESSAGE_TYPE_MOUSE:
		if (_Message->GetMessageString().compare("LeftPressed") == 0)
		{
			GameThreadUnsafeScope ScopeLock(mGame);
			std::pair<double, double>* MousePosition = &_Message->GetMessageDoublePair();

			/*// Normalize difference
			double TotalDistance = abs(ObjectPosition->first - MousePosition->first) + abs(ObjectPosition->second - MousePosition->second);
			NormalizedUnitVector.first = (ObjectPosition->first - MousePosition->first) / TotalDistance;
			NormalizedUnitVector.second = (ObjectPosition->second - MousePosition->second) / TotalDistance;

			double Rotation = atan2(NormalizedUnitVector.second, NormalizedUnitVector.first) * 180.0 / 3.141592;
			std::shared_ptr<MissileObject> NewMissile = std::make_shared<MissileObject>(mGame, 0.5, *ObjectPosition, *MousePosition);
			NewMissile->mCollisionLayerMask = COLLISION_LAYER_1;
			NewMissile->SetRotation(Rotation);
			mOutboundMissilesMutex.lock();
			mOutboundMissiles.push_back(NewMissile);
			mOutboundMissilesMutex.unlock();*/

			// Queue Message
			if (mGame != nullptr)
			{
				//mGame->QueueMessage("GameEvents", std::make_unique<Message>(MESSAGE_TYPE_FULL, "FireBullet", Rotation, NormalizedUnitVector));
			}
		}
		break;
	default:

		break;
	}
}