#pragma once
#include "Listener.h"

class GameObject;
class Game;

class Controller : public Listener
{
public:
	Controller(GameObject* _Object, Game* _Game = nullptr) { mObject = _Object; mGame = _Game; }
	~Controller() {};

	virtual void ControllerTick() = 0;

protected:
	GameObject* mObject;
	Game* mGame;
};