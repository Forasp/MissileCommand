#include "MissileObject.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GlobalDefines.h"
#include "GameThreadUnsafeScope.h"
#include "World.h"

void MissileObject::RenderTick(sf::RenderWindow* _RenderWindow)
{
	mRenderShape.setRotation(mRotation - 90);
	mRenderShape.setPosition(mPosition.first, mPosition.second);
	_RenderWindow->draw(mRenderShape);
}

void MissileObject::Tick(sf::Time _DeltaTime)
{
	GameObject::Tick(_DeltaTime);
}

void MissileObject::Collide(Collidable* _Collidable)
{
	mGame->QueueMessage("GameEvents", std::make_unique<Message>(Message(MESSAGE_TYPE_COLLISION_EVENT, (double)EXPLODE_MISSILE, mPosition, dynamic_cast<GameObject*>(this))));
}

void MissileObject::InitializeGameObject()
{
	mRenderShape = sf::CircleShape(2, 4);
	mRenderShape.setFillColor(sf::Color(0, 255, 255, 255));
	mRenderShape.setOutlineColor(sf::Color(0, 255, 255, 255));
	mRenderShape.setOutlineThickness(2);
	mRenderShape.setOrigin(2, 2);
	mRenderShape.setScale(1, 3);
	mLayer = LAYER_GAME_TOP;
	mGame->AddObjectToRenderer(this, mLayer);
	CreateCollider(&mPosition, &mSize, &mRotation);
	mSize = std::pair<double, double>(4, 4);
}


void MissileObject::CollisionBroadcast()
{
	mGame->QueueMessage("Collision", std::make_unique<Message>(Message(MESSAGE_TYPE_COLLISION_PTR, dynamic_cast<GameObject*>(this))));
}