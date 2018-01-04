#pragma once
#include "World.h"

class Message;

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

	std::shared_ptr<GameObject> mBackground;
	std::shared_ptr<GameObject> mCities[4];
	std::shared_ptr<GameObject> mTurret;
	std::vector<std::shared_ptr<GameObject>> mOutboundMissiles;
	std::vector<std::shared_ptr<GameObject>> mInboundMissiles;
	std::vector<std::shared_ptr<GameObject>> mExplosions;

	std::shared_ptr<ResourceHolder> mResourceHolder;
};
