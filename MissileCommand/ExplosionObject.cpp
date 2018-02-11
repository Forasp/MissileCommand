#include "ExplosionObject.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GlobalDefines.h"
#include "GameThreadUnsafeScope.h"
#include "World.h"

void ExplosionObject::RenderTick(sf::RenderWindow* _RenderWindow)
{
	if (bDrawSprite)
	{
		mSprite.setScale((mSize.first / mSprite.getTextureRect().width) * 3.0, (mSize.second / mSprite.getTextureRect().height) * 3.0);
		mSprite.setRotation(mRotation);
		mSprite.setPosition(mPosition.first, mPosition.second);
		_RenderWindow->draw(mSprite);
	}
	else
	{
		mRenderShape.setScale(sf::Vector2f(mSize.first, mSize.second));
		mRenderShape.setRotation(mRotation);
		mRenderShape.setPosition(mPosition.first, mPosition.second);
		_RenderWindow->draw(mRenderShape);
	}
}

void ExplosionObject::Tick(sf::Time _DeltaTime)
{
	if (!mAddedToRenderer)
	{
		mAddedToRenderer = true;
		mGame->AddObjectToRenderer(this, mLayer);

		if (mRenderTexture.loadFromFile("Resources\\explosions.png", sf::Rect<int>(0,0,238,238)))
		{
			mRenderTexture.setSmooth(true);
			mSprite.setTexture(mRenderTexture);
			mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2);
			bDrawSprite = true;
		}
	}
	GameObject::Tick(_DeltaTime);
	mPassedTime += _DeltaTime.asSeconds();
	
	if (mPassedTime > 3.0)
	{
		if (!mEnded)
		{
			mGame->QueueMessage("GameEvents", std::make_unique<Message>(Message(MESSAGE_TYPE_COLLISION_EVENT, (double)END_EXPLOSION, mPosition, dynamic_cast<GameObject*>(this))));
			mEnded = true;
		}
	}
	else if (mPassedTime > 2.0)
	{
		mSize.first -= _DeltaTime.asSeconds() * 200.0;
		mSize.second -= _DeltaTime.asSeconds() * 200.0;
	}
	else if (mPassedTime < 1.0)
	{
		mSize.first += _DeltaTime.asSeconds() * 200.0;
		mSize.second += _DeltaTime.asSeconds() * 200.0;
	}
}

void ExplosionObject::Collide(Collidable* _Collidable)
{
	//mGame->QueueMessage("GameEvents", std::make_unique<Message>(Message(MESSAGE_TYPE_COLLISION_EVENT, (double)EXPLODE_MISSILE, mPosition, dynamic_cast<GameObject*>(this))));
}

void ExplosionObject::InitializeGameObject()
{
	mEnded = false;
	mRenderShape = sf::CircleShape(0.5);
	mRenderShape.setFillColor(sf::Color(255, 127, 0, 255));
	mRenderShape.setOutlineColor(sf::Color(255, 127, 0, 255));
	mRenderShape.setOutlineThickness(0.25);
	mRenderShape.setOrigin(0.5f, 0.5f);
	mRenderShape.setScale(1, 1);
	mLayer = LAYER_GAME_SHIP;
	CreateCollider(&mPosition, &mSize, &mRotation);
	mSize = std::pair<double, double>(1, 1);
	mPosition = mStartPosition;
	mPassedTime = 0;
}


void ExplosionObject::CollisionBroadcast()
{
	mGame->QueueMessage("Collision", std::make_unique<Message>(Message(MESSAGE_TYPE_COLLISION_PTR, dynamic_cast<GameObject*>(this))));
}