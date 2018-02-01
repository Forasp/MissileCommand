#pragma once
#include "GameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"

class ButtonObject : public GameObject
{
public:
	ButtonObject(Game* _Game, std::string _Identity, GameObject* _Parent = nullptr) : mIdentity(_Identity), GameObject(_Game, _Parent)
	{
		InitializeGameObject();
	}

	void RenderTick(sf::RenderWindow* _RenderWindow);
	void InitializeGameObject();
	void HandleMessage(Message* _Message) {};
	void Tick(sf::Time _DeltaTime);
	void ReadMessage(Message* _Message);
protected:
	sf::Texture mRenderTexture;
	bool bDrawSprite;
	sf::RectangleShape mRenderShape;
	std::string mIdentity;
};
