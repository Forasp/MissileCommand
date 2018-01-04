#pragma once
#include "GlobalDefines.h"
#include <vector>
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <memory>
#include "Listener.h"

class Game;
class GameObject;
class ResourceHolder;
class Controller;
class Message;

class World : public Listener
{
public:
	World(Game* _Game);
	~World();
	
	virtual void Tick(sf::Time _DeltaTime);
	virtual void RenderTick(sf::RenderWindow* _RenderWindow);
	virtual void ControllerTick(sf::Time _DeltaTime);

	virtual void ReadMessage(Message* _Message);

	virtual std::shared_ptr<GameObject> GetWorldRoot() { return mWorldRoot; }
	virtual std::shared_ptr<ResourceHolder> GetResourceHolder() { return mResourceHolder; }

protected:
	void Initialize() {};

	virtual void CheckControls(int _OverrideControl = -1);
	
	Game* mGame;

	std::shared_ptr<GameObject> mWorldRoot;

	std::shared_ptr<ResourceHolder> mResourceHolder;

};