#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "SFML/Graphics/RectangleShape.hpp"

class MissileObject : public GameObject, public Collidable
{
public:
	MissileObject(Game* _Game, 
				  double _TravelTime,
			      std::pair<double, double> _StartPosition, 
				  std::pair<double,double> _EndPosition,
				  GameObject* _Parent = nullptr) : GameObject(_Game, _Parent), mStartPosition(_StartPosition), mEndPosition(_EndPosition), mTravelTime(_TravelTime) { InitializeGameObject(); }
	void RenderTick(sf::RenderWindow* _RenderWindow);
	void Collide(Collidable* _Collidable);
	void InitializeGameObject();
	void HandleMessage(Message* _Message) {};
	void Tick(sf::Time _DeltaTime);
	void ReadMessage(Message* _Message) { GameObject::ReadMessage(_Message); Collidable::ReadMessage(_Message); }
	virtual void CollisionBroadcast();
protected:
	sf::RectangleShape mRenderShape;
	std::pair<double, double> mStartPosition;
	std::pair<double, double> mEndPosition;
	double mTravelTime;

};