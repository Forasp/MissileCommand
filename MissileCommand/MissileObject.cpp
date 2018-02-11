#include "MissileObject.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GlobalDefines.h"
#include "GameThreadUnsafeScope.h"
#include "World.h"

void MissileObject::RenderTick(sf::RenderWindow* _RenderWindow)
{
	if (bDrawSprite)
	{
		mSprite.setScale(mSize.first / mSprite.getTextureRect().width, mSize.second / mSprite.getTextureRect().height);
		mSprite.setRotation(mRotation + 90);
		mSprite.setPosition(mPosition.first, mPosition.second);
		_RenderWindow->draw(mSprite);
	}
	else
	{
		mRenderShape.setScale(sf::Vector2f(mSize.first, mSize.second));
		mRenderShape.setRotation(mRotation + 90);
		mRenderShape.setPosition(mPosition.first, mPosition.second);
		_RenderWindow->draw(mRenderShape);
	}
}

void MissileObject::Tick(sf::Time _DeltaTime)
{
	if (!mAddedToRenderer)
	{
		mAddedToRenderer = true;
		mGame->AddObjectToRenderer(this, mLayer);
		AttachToMessenger(mGame->GetMessenger("MouseEvents"));

		if (mRenderTexture.loadFromFile(mIsEnemyMissile ? "Resources\\EnemyMissile.png" : "Resources\\AlliedMissile.png"))
		{
			mRenderTexture.setSmooth(true);
			mSprite.setTexture(mRenderTexture);
			mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2);
			bDrawSprite = true;
		}
	}

	GameObject::Tick(_DeltaTime);
	double PercentageOfTravelTime = _DeltaTime.asSeconds() / mTravelTime;
	mPosition.first = mPosition.first + ((mEndPosition.first - mStartPosition.first) * PercentageOfTravelTime);
	mPosition.second = mPosition.second + ((mEndPosition.second - mStartPosition.second) * PercentageOfTravelTime);
	
	if (abs(mEndPosition.first - mStartPosition.first) <= abs(mPosition.first - mStartPosition.first) && !mEnded)
	{
		mEnded = true;
		mGame->QueueMessage("GameEvents", std::make_unique<Message>(Message(MESSAGE_TYPE_COLLISION_EVENT, (double)EXPLODE_MISSILE, mPosition, dynamic_cast<GameObject*>(this))));
		if (mIsEnemyMissile)
		{
			mGame->QueueMessage("GameEvents", std::make_unique<Message>(MESSAGE_TYPE_CITY_DESTRUCTION, (double)mTargetCity));
		}
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
	CreateCollider(&mPosition, &mSize, &mRotation);
	mSize = std::pair<double, double>(12, 100);
	mPosition = mStartPosition;
	mEnded = false;
}


void MissileObject::CollisionBroadcast()
{
	mGame->QueueMessage("Collision", std::make_unique<Message>(Message(MESSAGE_TYPE_COLLISION_PTR, dynamic_cast<GameObject*>(this))));
}