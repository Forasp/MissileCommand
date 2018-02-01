#pragma once
#include "World.h"
#include <mutex>

class Message;
class CityObject;
class TurretObject;
class MissileObject;
class MissileCommandBackground;
class ExplosionObject;
class ButtonObject;

class MissileCommandWorld : public World
{
public:
	MissileCommandWorld(Game* _Game) : World(_Game)
	{
		mGame = _Game;
		Initialize();
	};

	~MissileCommandWorld();

	void Tick(sf::Time _DeltaTime);
	void RenderTick(sf::RenderWindow* _RenderWindow);
	void ControllerTick(sf::Time _DeltaTime);

	void ReadMessage(Message* _Message);

	std::shared_ptr<GameObject> GetWorldRoot() { return mWorldRoot; }
	std::shared_ptr<ResourceHolder> GetResourceHolder() { return mResourceHolder; }

protected:
	void Initialize();

	void CheckControls(int _OverrideControl = -1);

	std::shared_ptr<MissileCommandBackground> mBackground;
	std::shared_ptr<CityObject> mCities[4];
	std::shared_ptr<TurretObject> mTurret;
	std::vector<std::shared_ptr<ButtonObject>> mButtons;
	std::vector<std::shared_ptr<MissileObject>> mOutboundMissiles;
	std::vector<std::shared_ptr<MissileObject>> mInboundMissiles;
	std::vector<std::shared_ptr<ExplosionObject>> mExplosions;
	std::mutex mOutboundMissilesMutex;
	std::mutex mInboundMissilesMutex;
	std::mutex mExplosionsMutex;
	std::mutex mButtonsMutex;

	std::shared_ptr<ResourceHolder> mResourceHolder;

	double mTimeBetweenMissiles;
	double mTimeSinceLastMissile;
};
