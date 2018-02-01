#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "SFML/Graphics/RectangleShape.hpp"

class CityObject : public GameObject//, public Collidable
{
public:
	CityObject(Game* _Game, GameObject* _Parent = nullptr) : GameObject(_Game, _Parent) { InitializeGameObject(); }
	void RenderTick(sf::RenderWindow* _RenderWindow);
	void Collide(Collidable* _Collidable) {};
	void InitializeGameObject() ;
	void HandleMessage(Message* _Message) {};
	void Tick(sf::Time _DeltaTime);
	void ReadMessage(Message* _Message) { GameObject::ReadMessage(_Message);}// Collidable::ReadMessage(_Message); }
	virtual void CollisionBroadcast() {};

protected:
	sf::Texture mRenderTexture;
	bool bDrawSprite;
	sf::RectangleShape mRenderShape;
	std::string mIdentity;
	std::string mResourceLocation;
};
