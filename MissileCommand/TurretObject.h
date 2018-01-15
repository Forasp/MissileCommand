#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "SFML/Graphics/RectangleShape.hpp"

class TurretObject : public GameObject
{
public:
	TurretObject(Game* _Game, GameObject* _Parent = nullptr) : GameObject(_Game, _Parent) { InitializeGameObject(); }
	void RenderTick(sf::RenderWindow* _RenderWindow);
	void InitializeGameObject();
	void HandleMessage(Message* _Message);
	void Tick(sf::Time _DeltaTime);
	void ReadMessage(Message* _Message) { GameObject::ReadMessage(_Message); }
	virtual void CollisionBroadcast() {};
protected:
	sf::RectangleShape mRenderShape;
};
