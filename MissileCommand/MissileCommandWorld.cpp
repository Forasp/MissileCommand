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
		switch (i)
		{
		case 0:
			mCities[i]->SetPosition((sf::VideoMode::getDesktopMode().width * 0.1), sf::VideoMode::getDesktopMode().height / 10 * 8);
			break;
		case 1:
			mCities[i]->SetPosition((sf::VideoMode::getDesktopMode().width * 0.3), sf::VideoMode::getDesktopMode().height / 10 * 8);
			break;
		case 2:
			mCities[i]->SetPosition((sf::VideoMode::getDesktopMode().width * 0.7), sf::VideoMode::getDesktopMode().height / 10 * 8);
			break;
		case 3:
			mCities[i]->SetPosition((sf::VideoMode::getDesktopMode().width * 0.9), sf::VideoMode::getDesktopMode().height / 10 * 8);
			break;
		}

		mCities[i]->SetSize(sf::VideoMode::getDesktopMode().width / 6, sf::VideoMode::getDesktopMode().height / 6);
	}
	
	mTurret = std::move(std::make_shared<TurretObject>(TurretObject(mGame)));

	// Position assets

	mTurret->SetPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 10 * 9);
	mTurret->SetSize(sf::VideoMode::getDesktopMode().width / 15, sf::VideoMode::getDesktopMode().width / 15);

	mBackground->SetPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
	mBackground->SetSize(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);

	AttachToMessenger(mGame->GetMessenger("MouseEvents"));

	mTimeBetweenMissiles = 3.0;
	mTimeSinceLastMissile = 0;
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

	mTimeSinceLastMissile += _DeltaTime.asSeconds();

	if (mTimeSinceLastMissile > mTimeBetweenMissiles)
	{
		// Spawn Missile with random city target, and random starting location.
		std::pair<double, double> ObjectPosition = std::pair<double, double>((double)(rand() % (int)(sf::VideoMode::getDesktopMode().width * 1.5)) - sf::VideoMode::getDesktopMode().width / 4.0,
																			  0.0 - (double)(rand() % (sf::VideoMode::getDesktopMode().height / 10)));// Random Location
		int IndexOfCity = rand() % 4;
		std::pair<double, double> DestPosition = std::pair<double, double>(mCities[IndexOfCity]->GetPosition().first, mCities[IndexOfCity]->GetPosition().second);// Random City's location 
		std::pair<double, double> NormalizedUnitVector;

		// Normalize difference
		double TotalDistance = abs(ObjectPosition.first - DestPosition.first) + abs(ObjectPosition.second - DestPosition.second);
		NormalizedUnitVector.first = (ObjectPosition.first - DestPosition.first) / TotalDistance;
		NormalizedUnitVector.second = (ObjectPosition.second - DestPosition.second) / TotalDistance;

		double Rotation = atan2(NormalizedUnitVector.second, NormalizedUnitVector.first) * 180.0 / 3.141592;
		std::shared_ptr<MissileObject> NewMissile = std::make_shared<MissileObject>(mGame, mTimeBetweenMissiles * 2.0, ObjectPosition, DestPosition);
		NewMissile->mCollisionLayerMask = COLLISION_LAYER_1;
		NewMissile->SetRotation(Rotation);
		mInboundMissilesMutex.lock();
		mInboundMissiles.push_back(NewMissile);
		mInboundMissilesMutex.unlock();

		mTimeSinceLastMissile = 0.0;
		mTimeBetweenMissiles *= 0.98;
	}

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
						std::shared_ptr<ExplosionObject> NewExplosion = std::make_shared<ExplosionObject>(mGame, mInboundMissiles[i]->GetPosition());
						NewExplosion->mCollisionLayerMask = COLLISION_LAYER_1;
						mExplosionsMutex.lock();
						mExplosions.push_back(NewExplosion);
						mExplosionsMutex.unlock();
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