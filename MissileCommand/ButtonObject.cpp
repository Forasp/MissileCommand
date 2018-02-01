#include "ButtonObject.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GameThreadUnsafeScope.h"
#include "World.h"

void ButtonObject::RenderTick(sf::RenderWindow* _RenderWindow)
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

void ButtonObject::Tick(sf::Time _DeltaTime)
{
	if (!mAddedToRenderer)
	{
		mAddedToRenderer = true;
		mGame->AddObjectToRenderer(this, mLayer);

		if (mRenderTexture.loadFromFile("Resources\\button.png", sf::Rect<int>(0, 0, 238, 238)))
		{
			mSprite.setTexture(mRenderTexture);
			mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2);
			bDrawSprite = true;
		}
	}
	GameObject::Tick(_DeltaTime);
}

void ButtonObject::InitializeGameObject()
{
	mRenderShape = sf::RectangleShape(sf::Vector2f(1, 1));
	mRenderShape.setFillColor(sf::Color(255, 0, 0, 255));
	mRenderShape.setOrigin(0.5f, 0.5f);
	mRenderShape.setScale(1, 1);
	mLayer = LAYER_GAME_SHIP;
	mSize = std::pair<double, double>(1, 1);
	AttachToMessenger(mGame->GetMessenger("MouseEvents"));
}

/// <summary> 
/// Interprets messages passed.
/// </summary>
void ButtonObject::ReadMessage(Message* _Message)
{
	switch (_Message->GetMessageType())
	{
		// If message is a mouse event
	case MESSAGE_TYPE_MOUSE:
		if (_Message->GetMessageString().compare("LeftPressed") == 0)
		{
			std::pair<double, double>* MousePosition = &_Message->GetMessageDoublePair();

			if ((MousePosition->first < mPosition.first - (mSize.first/2))		||
				(MousePosition->second < mPosition.second - (mSize.second / 2))	||
				(MousePosition->first > mPosition.first + (mSize.first / 2))	||
				(MousePosition->second > mPosition.second + (mSize.second / 2)))
			{

			}
			else
			{
				// Queue Message
				if (mGame != nullptr)
				{
					mGame->QueueMessage("ButtonEvents", std::make_unique<Message>(MESSAGE_TYPE_BUTTON_EVENT, mIdentity));
				}
			}
		}
		break;
	default:
		break;
	}

	GameObject::ReadMessage(_Message);
}