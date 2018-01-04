#include "MissileCommandWorld.h"
#include "Game.h"
#include "GameObject.h"
#include "Controller.h"
#include "Messenger.h"
#include "Message.h"
#include "GameThreadUnsafeScope.h"
#include "TurretObject.h"
#include "CityObject.h"

void MissileCommandWorld::Initialize()
{
	// Construct our world here.
	//mWorldRoot = std::make_shared<SnakeHead>(mGame);
	mBackground = std::make_shared<GameObject>(GameObject(mGame));
	
	for (int i = 0; i < 4; i++)
	{
		mCities[i] = std::make_shared<GameObject>(CityObject(mGame));;
	}
	
	mTurret = std::make_shared<GameObject>(TurretObject(mGame));
}

MissileCommandWorld::~MissileCommandWorld()
{

}

/// <summary> 
/// Calls RenderTick on graphics scenegraph.
/// </summary>
void MissileCommandWorld::RenderTick(sf::RenderWindow* _RenderWindow)
{
	// render Background
	mBackground->RenderTick(_RenderWindow);

	// Render Cities
	for (int i = 0; i < 4; i++)
	{
		mCities[i]->RenderTick(_RenderWindow);
	}

	// Render Turret
	mTurret->RenderTick(_RenderWindow);

	// Render Missiles outbound
	for (int i = 0; i < mOutboundMissiles.size(); i++)
	{
		mOutboundMissiles[i]->RenderTick(_RenderWindow);
	}

	// Render Missiles inbound
	for (int i = 0; i < mInboundMissiles.size(); i++)
	{
		mInboundMissiles[i]->RenderTick(_RenderWindow);
	}

	// Render Explosions
	for (int i = 0; i < mExplosions.size(); i++)
	{
		mExplosions[i]->RenderTick(_RenderWindow);
	}
}

/// <summary> 
/// Ticks all objects in traditional scene graph.
/// </summary>
void MissileCommandWorld::Tick(sf::Time _DeltaTime)
{
	// render Background
	mBackground->Tick(_DeltaTime);

	// Render Cities
	for (int i = 0; i < 4; i++)
	{
		mCities[i]->Tick(_DeltaTime);
	}

	// Render Turret
	mTurret->Tick(_DeltaTime);

	// Render Missiles outbound
	for (int i = 0; i < mOutboundMissiles.size(); i++)
	{
		mOutboundMissiles[i]->Tick(_DeltaTime);
	}

	// Render Missiles inbound
	for (int i = 0; i < mInboundMissiles.size(); i++)
	{
		mInboundMissiles[i]->Tick(_DeltaTime);
	}

	// Render Explosions
	for (int i = 0; i < mExplosions.size(); i++)
	{
		mExplosions[i]->Tick(_DeltaTime);
	}
}

/// <summary> 
/// Checks controls and ticks all controllers.
/// </summary>
void MissileCommandWorld::ControllerTick(sf::Time _DeltaTime)
{
	CheckControls();

	// render Background
	mBackground->ControllerTick(_DeltaTime);

	// Render Cities
	for (int i = 0; i < 4; i++)
	{
		mCities[i]->ControllerTick(_DeltaTime);
	}

	// Render Turret
	mTurret->ControllerTick(_DeltaTime);

	// Render Missiles outbound
	for (int i = 0; i < mOutboundMissiles.size(); i++)
	{
		mOutboundMissiles[i]->ControllerTick(_DeltaTime);
	}

	// Render Missiles inbound
	for (int i = 0; i < mInboundMissiles.size(); i++)
	{
		mInboundMissiles[i]->ControllerTick(_DeltaTime);
	}

	// Render Explosions
	for (int i = 0; i < mExplosions.size(); i++)
	{
		mExplosions[i]->ControllerTick(_DeltaTime);
	}
}

/// <summary> 
/// Checks only for controls expected by the world.
/// </summary>
void MissileCommandWorld::CheckControls(int _OverrideControl)
{
	if (_OverrideControl == sf::Keyboard::Escape)
	{
		mGame->QueueMessage("GlobalEvents", std::make_unique<Message>(MESSAGE_TYPE_QUIT, std::string("Escape key pressed.")));
	}
}

/// <summary> 
/// Interprets messages passed.
/// </summary>
void MissileCommandWorld::ReadMessage(Message* _Message)
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
		case MESSAGE_TYPE_COLLISION_EVENT:
			if (_Message->GetMessageDouble() == EXPLODE_MISSILE)
			{
				for (int i = 0; i < mOutboundMissiles.size(); i++)
				{
					if (mOutboundMissiles[i].get() == _Message->GetMessageVoidPtr())
					{
						// Remove this child and create an explosion here.
						mOutboundMissiles.erase(mOutboundMissiles.begin() + i);
					}
				}

				// Render Missiles inbound
				for (int i = 0; i < mInboundMissiles.size(); i++)
				{
					if (mInboundMissiles[i].get() == _Message->GetMessageVoidPtr())
					{
						// Remove this child and create an explosion here.
						mInboundMissiles.erase(mInboundMissiles.begin() + i);
					}
				}
			}
			
			break;
		default:

			break;
	}
}