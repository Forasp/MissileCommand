#pragma once
#include "GameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"

class ButtonObject : public GameObject
{
public:
	ButtonObject(Game* _Game, std::string _Identity, std::string _ResourceLocation, GameObject* _Parent = nullptr) : mIdentity(_Identity), mResourceLocation(_ResourceLocation), GameObject(_Game, _Parent)
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
	std::string mResourceLocation;
};
