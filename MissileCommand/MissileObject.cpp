#include "MissileObject.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GlobalDefines.h"
#include "GameThreadUnsafeScope.h"
#include "World.h"

void MissileObject::RenderTick(sf::RenderWindow* _RenderWindow)
{
	mRenderShape.setScale(sf::Vector2f(mSize.first, mSize.second));
	mRenderShape.setRotation(mRotation);
	mRenderShape.setPosition(mPosition.first, mPosition.second);
	_RenderWindow->draw(mRenderShape);
}

void MissileObject::Tick(sf::Time _DeltaTime)
{
	GameObject::Tick(_DeltaTime);
	double PercentageOfTravelTime = _DeltaTime.asSeconds() / mTravelTime;
	mPosition.first = mPosition.first + ((mEndPosition.first - mStartPosition.first) * PercentageOfTravelTime);
	mPosition.second = mPosition.second + ((mEndPosition.second - mStartPosition.second) * PercentageOfTravelTime);
	
	if (abs(mEndPosition.first - mStartPosition.first) < abs(mPosition.first - mStartPosition.first))
	{
		mGame->QueueMessage("GameEvents", std::make_unique<Message>(Message(MESSAGE_TYPE_COLLISION_EVENT, (double)EXPLODE_MISSILE, mPosition, dynamic_cast<GameObject*>(this))));
	}
}

void MissileObject::Collide(Collidable* _Collidable)
{
	mGame->QueueMessage("GameEvents", std::make_unique<Message>(Message(MESSAGE_TYPE_COLLISION_EVENT, (double)EXPLODE_MISSILE, mPosition, dynamic_cast<GameObject*>(this))));
}

void MissileObject::InitializeGameObject()
{
	mRenderShape = sf::RectangleShape(sf::Vector2f(1, 1));
	mRenderShape.setFillColor(sf::Color(255, 0, 0, 255));
	mRenderShape.setOrigin(0.5f, 0.5f);
	mRenderShape.setScale(1, 1);
	mLayer = LAYER_GAME_SHIP;
	mGame->AddObjectToRenderer(this, mLayer);
	mAddedToRenderer = true;
	CreateCollider(&mPosition, &mSize, &mRotation);
	mSize = std::pair<double, double>(32, 8);
	mPosition = mStartPosition;
}


void MissileObject::CollisionBroadcast()
{
	mGame->QueueMessage("Collision", std::make_unique<Message>(Message(MESSAGE_TYPE_COLLISION_PTR, dynamic_cast<GameObject*>(this))));
}