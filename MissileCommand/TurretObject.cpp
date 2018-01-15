#include "TurretObject.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GlobalDefines.h"
#include "GameThreadUnsafeScope.h"
#include "World.h"

void TurretObject::RenderTick(sf::RenderWindow* _RenderWindow)
{
	mRenderShape.setScale(sf::Vector2f(mSize.first, mSize.second));
	mRenderShape.setRotation(mRotation);
	mRenderShape.setPosition(mPosition.first, mPosition.second);
	_RenderWindow->draw(mRenderShape);
}

void TurretObject::Tick(sf::Time _DeltaTime)
{
	if (!mAddedToRenderer)
	{
		mAddedToRenderer = true;
		mGame->AddObjectToRenderer(this, mLayer);
		AttachToMessenger(mGame->GetMessenger("MouseEvents"));
	}
	GameObject::Tick(_DeltaTime);
}

void TurretObject::InitializeGameObject()
{
	mRenderShape = sf::RectangleShape(sf::Vector2f(1, 1));
	mRenderShape.setFillColor(sf::Color(0, 255, 0, 255));
	mRenderShape.setOrigin(0.5f, 0.5f);
	mRenderShape.setScale(1, 1);
	mLayer = LAYER_GAME_TOP;
	mSize = std::pair<double, double>(1, 1);
}

void TurretObject::HandleMessage(Message* _Message)
{
	// If message is a mouse event
	if (_Message->GetMessageType() == MESSAGE_TYPE_MOUSE && _Message->GetMessageString().compare("LeftPressed") == 0)
	{
		std::pair<double, double>* ObjectPosition = &GetPosition();
		std::pair<double, double>* MousePosition = &_Message->GetMessageDoublePair();
		std::pair<double, double> NormalizedUnitVector;

		// Normalize difference
		double TotalDistance = abs(ObjectPosition->first - MousePosition->first) + abs(ObjectPosition->second - MousePosition->second);
		NormalizedUnitVector.first = (ObjectPosition->first - MousePosition->first) / TotalDistance;
		NormalizedUnitVector.second = (ObjectPosition->second - MousePosition->second) / TotalDistance;

		double Rotation = atan2(NormalizedUnitVector.second, NormalizedUnitVector.first) * 180.0 / 3.141592;
		SetRotation(Rotation);

		// Queue Message
		if (mGame != nullptr)
		{
			//mGame->QueueMessage("GameEvents", std::make_unique<Message>(MESSAGE_TYPE_FULL, "FireBullet", Rotation, NormalizedUnitVector));
		}
	}
};