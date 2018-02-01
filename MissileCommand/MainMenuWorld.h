#pragma once
#include "World.h"
#include <mutex>

class Message;
class ButtonObject;
class MainMenuBackgroundObject;

class MainMenuWorld : public World
{
public:
	MainMenuWorld(Game* _Game) : World(_Game)
	{
		mGame = _Game;
		Initialize();
	};

	~MainMenuWorld();

	void Tick(sf::Time _DeltaTime);
	void RenderTick(sf::RenderWindow* _RenderWindow);
	void ControllerTick(sf::Time _DeltaTime);

	void ReadMessage(Message* _Message);

	std::shared_ptr<GameObject> GetWorldRoot() { return mWorldRoot; }
	std::shared_ptr<ResourceHolder> GetResourceHolder() { return mResourceHolder; }

protected:
	void Initialize();

	void CheckControls(int _OverrideControl = -1);

	std::shared_ptr<MainMenuBackgroundObject> mBackground;
	std::vector<std::shared_ptr<ButtonObject>> mButtons;
	std::mutex mButtonsMutex;

	std::shared_ptr<ResourceHolder> mResourceHolder;

	double mTimeBetweenMissiles;
	double mTimeSinceLastMissile;
};
