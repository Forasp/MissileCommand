#include "CityObject.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GlobalDefines.h"
#include "GameThreadUnsafeScope.h"
#include "World.h"
#include "Message.h"

void CityObject::RenderTick(sf::RenderWindow* _RenderWindow)
{
	if (bDrawSprite)
	{
		mSprite.setScale((mSize.first / mSprite.getTextureRect().width), (mSize.second / mSprite.getTextureRect().height));
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

void CityObject::Tick(sf::Time _DeltaTime)
{
	if (!mAddedToRenderer)
	{
		mAddedToRenderer = true;
		mGame->AddObjectToRenderer(this, mLayer);
		AttachToMessenger(mGame->GetMessenger("GameEvents"));

		if (mRenderTexture.loadFromFile(mResourceLocation))
		{
			mRenderTexture.setSmooth(true);
			mSprite.setTexture(mRenderTexture);
			mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2);
			bDrawSprite = true;
		}
	}
	GameObject::Tick(_DeltaTime);
}

/// <summary> 
/// Interprets messages passed.
/// </summary>
void CityObject::ReadMessage(Message* _Message)
{
	switch (_Message->GetMessageType())
	{
		case MESSAGE_TYPE_CITY_DESTRUCTION:
			if (mCityIndex == _Message->GetMessageDouble())
			{
				if (mCityState > 0)
				{
					mCityState--;
					mGame->QueueMessage("GameEvents", std::make_unique<Message>(MESSAGE_TYPE_CITY_STATE, std::pair<double,double>(mCityIndex, mCityState)));

					switch (mCityState)
					{
						case 0:
							mResourceLocation = "Resources\\CityV1_3.png";
							break;
						case 1:
							mResourceLocation = "Resources\\CityV1_2.png";
							break;
						default:
						case 2:
							mResourceLocation = "Resources\\CityV1_1.png";
							break;
					}

					if (mRenderTexture.loadFromFile(mResourceLocation))
					{
						mRenderTexture.setSmooth(true);
						mSprite.setTexture(mRenderTexture);
						mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2);
						bDrawSprite = true;
					}
					else
					{
						bDrawSprite = false;
					}
				}
			}
			break;
	}

	GameObject::ReadMessage(_Message);
}

void CityObject::InitializeGameObject()
{
	mResourceLocation = "Resources\\CityV1_1.png";
	mRenderShape = sf::RectangleShape(sf::Vector2f(1, 1));
	mRenderShape.setFillColor(sf::Color(255, 255, 255, 255));
	mRenderShape.setOrigin(0.5f, 0.5f);
	mRenderShape.setScale(1, 1);
	mLayer = LAYER_GAME_STATION;
	mSize = std::pair<double, double>(4, 4);
	mCityState = 2;
	//CreateCollider(&mPosition, &mSize, &mRotation);
}