#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "SFML/Graphics/CircleShape.hpp"

class ExplosionObject : public GameObject, public Collidable
{
public:
	ExplosionObject(Game* _Game,
		std::pair<double, double> _StartPosition,
		GameObject* _Parent = nullptr) : GameObject(_Game, _Parent), mStartPosition(_StartPosition)
	{
		InitializeGameObject();
	}

	void RenderTick(sf::RenderWindow* _RenderWindow);
	void Collide(Collidable* _Collidable);
	void InitializeGameObject();
	void HandleMessage(Message* _Message) {};
	void Tick(sf::Time _DeltaTime);
	void ReadMessage(Message* _Message) { GameObject::ReadMessage(_Message); Collidable::ReadMessage(_Message); }
	virtual void CollisionBroadcast();
protected:
	std::pair<double, double> mStartPosition;
	sf::CircleShape mRenderShape;
	double mPassedTime;
	bool mEnded;
};
