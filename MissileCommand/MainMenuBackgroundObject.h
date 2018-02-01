#pragma once
#include "GameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"

class MainMenuBackgroundObject : public GameObject
{
public:

	MainMenuBackgroundObject(Game* _Game, GameObject* _Parent = nullptr);

	void RenderTick(sf::RenderWindow* _RenderWindow);
	void InitializeGameObject();
	void HandleMessage(Message* _Message) {};
	void Tick(sf::Time _DeltaTime);
	void ReadMessage(Message* _Message) { GameObject::ReadMessage(_Message); }
protected:
	sf::Texture mRenderTexture;
	bool bDrawSprite;
	sf::RectangleShape mRenderShape;
};
