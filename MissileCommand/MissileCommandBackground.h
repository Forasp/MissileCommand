#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "SFML/Graphics/RectangleShape.hpp"

class MissileCommandBackground : public GameObject
{
public:
	MissileCommandBackground(Game* _Game, GameObject* _Parent = nullptr) : GameObject(_Game, _Parent) { InitializeGameObject(); }
	void RenderTick(sf::RenderWindow* _RenderWindow);
	void InitializeGameObject();
	void HandleMessage(Message* _Message) {};
	void Tick(sf::Time _DeltaTime);
	void ReadMessage(Message* _Message) { GameObject::ReadMessage(_Message); }
protected:
	sf::RectangleShape mRenderShape;
};
