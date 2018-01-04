#include "Collidable.h"
#include "Message.h"
#include <math.h>
#include "GameObject.h"

void Collidable::CheckCollision(Collidable* _Collidable)
{
	if (mSizePtr == nullptr || mPositionPtr == nullptr || _Collidable->mSizePtr == nullptr || _Collidable->mPositionPtr == nullptr || _Collidable == this)
	{
		return;
	}

 	double ThisRadius = RadiusFromSize(mSizePtr);
	double OtherRadius = RadiusFromSize(_Collidable->mSizePtr);

	// If distance is greater than the two radii, then there can be no collision.
	if (DistanceBetweenPoints(mPositionPtr, _Collidable->mPositionPtr) > ThisRadius + OtherRadius)
	{
		return;
	}

	_Collidable->Collide(this);

	// Collide can be implemented to delete pointers, always check again.
	// include check for all invalid pointers TODO 
  	Collide(_Collidable != nullptr ? _Collidable : nullptr);
}

void Collidable::CreateCollider(std::pair<double, double>* _PositionPtr, std::pair<double, double>* _SizePtr, double* _RotationPtr)
{
	mPositionPtr = _PositionPtr;
	mSizePtr = _SizePtr;
	mRotationPtr = _RotationPtr;
}

void Collidable::CollisionTick()
{
	if (mPastPosition.first != mPositionPtr->first ||
		mPastPosition.second != mPositionPtr->second ||
		mPastSize.first != mSizePtr->first ||
		mPastSize.second != mSizePtr->second ||
		mPastRotation != *mRotationPtr)
	{
		CollisionBroadcast();
		mPastPosition = *mPositionPtr;
		mPastSize = *mSizePtr;
		mPastRotation = *mRotationPtr;
	}
}

void Collidable::ReadMessage(Message* _Message)
{
	if (_Message->GetMessageType() == MESSAGE_TYPE_EVENT && _Message->GetMessageDouble() == TICK_EVENT)
	{
		CollisionTick();
	}
	else if (_Message->GetMessageType() == MESSAGE_TYPE_COLLISION_PTR)
	{
		Collidable* CollidablePtr = dynamic_cast<Collidable*>(static_cast<GameObject*>(_Message->GetMessageVoidPtr()));
		CheckCollision(CollidablePtr);
	}
}

void Collidable::PopulateCollisionAreas(sf::Sprite* _Sprite)
{
	sf::Image TempImage;
	TempImage = _Sprite->getTexture()->copyToImage();

	for (unsigned int x = 0; x < TempImage.getSize().x; x++)
	{
		for (unsigned int y = 0; y < TempImage.getSize().y; y++)
		{
			unsigned int ImageWidth = TempImage.getSize().x;
			unsigned int ImageHeight = TempImage.getSize().y;

			bool PixelCollidable = bool(TempImage.getPixel(x, y).a == 0u);

			mCollisionAreaXS[x / (ImageWidth / 32)][y / (ImageHeight / 32)] |= PixelCollidable;
			mCollisionAreaS[ x / (ImageWidth / 16)][y / (ImageHeight / 16)] |= PixelCollidable;
			mCollisionAreaM[ x / (ImageWidth / 8)][ y / (ImageHeight / 8)]  |= PixelCollidable;
			mCollisionAreaL[ x / (ImageWidth / 4)][ y / (ImageHeight / 4)]  |= PixelCollidable;
			mCollisionAreaXL[x / (ImageWidth / 2)][ y / (ImageHeight / 2)]  |= PixelCollidable;
		}

	}
}
