#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "SFML/Graphics/RectangleShape.hpp"

class CityObject : public GameObject
{
public:
	CityObject(Game* _Game, int _CityIndex, GameObject* _Parent = nullptr) : GameObject(_Game, _Parent), mCityIndex(_CityIndex) { CityObject::InitializeGameObject(); }
	void RenderTick(sf::RenderWindow* _RenderWindow);
	void Collide(Collidable* _Collidable) {};
	void InitializeGameObject() ;
	void HandleMessage(Message* _Message) {};
	void Tick(sf::Time _DeltaTime);
	void ReadMessage(Message* _Message);
	virtual void CollisionBroadcast() {};

protected:
	sf::Texture mRenderTexture;
	bool bDrawSprite;
	sf::RectangleShape mRenderShape;
	std::string mIdentity;
	std::string mResourceLocation;
	int mCityIndex;
	int mCityState;
};
