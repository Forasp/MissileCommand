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
				  bool _EnemyMissile,
				  int _TargetCity = -1,
				  GameObject* _Parent = nullptr) : GameObject(_Game, _Parent), mIsEnemyMissile(_EnemyMissile), mTargetCity(_TargetCity), mStartPosition(_StartPosition), mEndPosition(_EndPosition), mTravelTime(_TravelTime) { InitializeGameObject(); }
	void RenderTick(sf::RenderWindow* _RenderWindow);
	void Collide(Collidable* _Collidable);
	void InitializeGameObject();
	void HandleMessage(Message* _Message) {};
	void Tick(sf::Time _DeltaTime);
	void ReadMessage(Message* _Message) { GameObject::ReadMessage(_Message); Collidable::ReadMessage(_Message); }
	virtual void CollisionBroadcast();
protected:
	sf::RectangleShape mRenderShape;
	sf::Texture mRenderTexture;
	bool bDrawSprite;
	bool mIsEnemyMissile;
	std::pair<double, double> mStartPosition;
	std::pair<double, double> mEndPosition;
	double mTravelTime;
	int mTargetCity;
	bool mEnded;
};