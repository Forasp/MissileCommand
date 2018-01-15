#include "MissileCommandWorld.h"
#include "Game.h"
#include "GameObject.h"
#include "Controller.h"
#include "Messenger.h"
#include "Message.h"
#include "GameThreadUnsafeScope.h"
#include "TurretObject.h"
#include "CityObject.h"
#include "MissileObject.h"
#include "MissileCommandBackground.h"
#include "ExplosionObject.h"

void MissileCommandWorld::Initialize()
{
	// Construct our world here.
	mBackground = std::make_shared<MissileCommandBackground>(MissileCommandBackground(mGame));
	
	for (int i = 0; i < 4; i++)
	{
		mCities[i] = std::make_shared<CityObject>(CityObject(mGame));;
		mCities[i]->SetPosition((sf::VideoMode::getDesktopMode().width / 5 * (i + 1)), sf::VideoMode::getDesktopMode().height / 10*8);
		mCities[i]->SetSize(sf::VideoMode::getDesktopMode().width / 10, sf::VideoMode::getDesktopMode().height / 10);
	}
	
	mTurret = std::move(std::make_shared<TurretObject>(TurretObject(mGame)));

	// Position assets

	mTurret->SetPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 10 * 9);
	mTurret->SetSize(sf::VideoMode::getDesktopMode().width / 15, sf::VideoMode::getDesktopMode().width / 15);

	mBackground->SetPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
	mBackground->SetSize(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

	AttachToMessenger(mGame->GetMessenger("MouseEvents"));
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
	mOutboundMissilesMutex.lock();
	for (int i = 0; i < mOutboundMissiles.size(); i++)
	{
		mOutboundMissiles[i]->Tick(_DeltaTime);
	}
	mOutboundMissilesMutex.unlock();

	// Render Missiles inbound
	mInboundMissilesMutex.lock();
	for (int i = 0; i < mInboundMissiles.size(); i++)
	{
		mInboundMissiles[i]->Tick(_DeltaTime);
	}
	mInboundMissilesMutex.unlock();

	// Render Explosions
	mExplosionsMutex.lock();
	for (int i = 0; i < mExplosions.size(); i++)
	{
		mExplosions[i]->Tick(_DeltaTime);
	}
	mExplosionsMutex.unlock();
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
	mOutboundMissilesMutex.lock();
	for (int i = 0; i < mOutboundMissiles.size(); i++)
	{
		mOutboundMissiles[i]->ControllerTick(_DeltaTime);
	}
	mOutboundMissilesMutex.unlock();

	// Render Missiles inbound
	mInboundMissilesMutex.lock();
	for (int i = 0; i < mInboundMissiles.size(); i++)
	{
		mInboundMissiles[i]->ControllerTick(_DeltaTime);
	}
	mInboundMissilesMutex.unlock();

	// Render Explosions
	mExplosionsMutex.lock();
	for (int i = 0; i < mExplosions.size(); i++)
	{
		mExplosions[i]->ControllerTick(_DeltaTime);
	}
	mExplosionsMutex.unlock();
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
						GameThreadUnsafeScope ScopeLock(mGame);
						std::shared_ptr<ExplosionObject> NewExplosion = std::make_shared<ExplosionObject>(mGame, mOutboundMissiles[i]->GetPosition());
						NewExplosion->mCollisionLayerMask = COLLISION_LAYER_1;
						mExplosionsMutex.lock();
						mExplosions.push_back(NewExplosion);
						mExplosionsMutex.unlock();
						mOutboundMissilesMutex.lock();
						mOutboundMissiles.erase(mOutboundMissiles.begin() + i);
						mOutboundMissilesMutex.unlock();
					}
				}

				// Render Missiles inbound
				for (int i = 0; i < mInboundMissiles.size(); i++)
				{
					if (mInboundMissiles[i].get() == _Message->GetMessageVoidPtr())
					{
						// Remove this child and create an explosion here.
						GameThreadUnsafeScope ScopeLock(mGame);
						mInboundMissilesMutex.lock();
						mInboundMissiles.erase(mInboundMissiles.begin() + i);
						mInboundMissilesMutex.unlock();
					}
				}
			}
			if (_Message->GetMessageDouble() == END_EXPLOSION)
			{
				for (int i = 0; i < mExplosions.size(); i++)
				{
					if (mExplosions[i].get() == _Message->GetMessageVoidPtr())
					{
						// Remove this child and create an explosion here.
						GameThreadUnsafeScope ScopeLock(mGame);
						mExplosionsMutex.lock();
						mExplosions.erase(mExplosions.begin() + i);
						mExplosionsMutex.unlock();
					}
				}
			}
			
			break;
			// If message is a mouse event
		case MESSAGE_TYPE_MOUSE:
			if(_Message->GetMessageString().compare("LeftPressed") == 0)
			{
				GameThreadUnsafeScope ScopeLock(mGame);
				std::pair<double, double>* ObjectPosition = &mTurret->GetPosition();
				std::pair<double, double>* MousePosition = &_Message->GetMessageDoublePair();
				std::pair<double, double> NormalizedUnitVector;

				// Normalize difference
				double TotalDistance = abs(ObjectPosition->first - MousePosition->first) + abs(ObjectPosition->second - MousePosition->second);
				NormalizedUnitVector.first = (ObjectPosition->first - MousePosition->first) / TotalDistance;
				NormalizedUnitVector.second = (ObjectPosition->second - MousePosition->second) / TotalDistance;

				double Rotation = atan2(NormalizedUnitVector.second, NormalizedUnitVector.first) * 180.0 / 3.141592;
				std::shared_ptr<MissileObject> NewMissile = std::make_shared<MissileObject>(mGame, 0.5, *ObjectPosition, *MousePosition);
				NewMissile->mCollisionLayerMask = COLLISION_LAYER_1;
				NewMissile->SetRotation(Rotation);
				mOutboundMissilesMutex.lock();
				mOutboundMissiles.push_back(NewMissile);
				mOutboundMissilesMutex.unlock();

				// Queue Message
				if (mGame != nullptr)
				{
					//mGame->QueueMessage("GameEvents", std::make_unique<Message>(MESSAGE_TYPE_FULL, "FireBullet", Rotation, NormalizedUnitVector));
				}
			}
		default:

			break;
	}
}