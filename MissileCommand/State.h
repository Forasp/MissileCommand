#pragma once
#include <string>
#include <vector>
//#include "Resource.h"
#include "Resources.h"
#include <SFML/Graphics.hpp>

class State
{
protected:
	//std::vector<Resource> mResources;
	//Resources* mTextureCtrl;
	sf::RenderWindow& mWindow;

public:
	State(sf::RenderWindow& _RenderWindow) : mWindow(_RenderWindow) { EnterState(); }
	~State() { ExitState(); }

	//void AddResource(Resource _Resource);
	//void RemoveResource(Resource _Resource);

	//std::vector<Resource>* GetResources();

	//Resources* GetTextureCtrl() { return mTextureCtrl; }

	void EnterState();
	void ExitState();

	void PreTick();
	void Tick();
	void PostTick();
};
