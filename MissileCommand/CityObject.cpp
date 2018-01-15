#include "CityObject.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GlobalDefines.h"
#include "GameThreadUnsafeScope.h"
#include "World.h"

void CityObject::RenderTick(sf::RenderWindow* _RenderWindow)
{
	mRenderShape.setScale(sf::Vector2f(mSize.first, mSize.second));
	mRenderShape.setRotation(mRotation);
	mRenderShape.setPosition(mPosition.first, mPosition.second);
	_RenderWindow->draw(mRenderShape);
}

void CityObject::Tick(sf::Time _DeltaTime)
{
	if (!mAddedToRenderer)
	{
		mAddedToRenderer = true;
		mGame->AddObjectToRenderer(this, mLayer);
	}
	GameObject::Tick(_DeltaTime);
}

void CityObject::InitializeGameObject()
{
	mRenderShape = sf::RectangleShape(sf::Vector2f(1, 1));
	mRenderShape.setFillColor(sf::Color(255, 255, 255, 255));
	mRenderShape.setOrigin(0.5f, 0.5f);
	mRenderShape.setScale(1, 1);
	mLayer = LAYER_GAME_STATION;
	mSize = std::pair<double, double>(4, 4);
	CreateCollider(&mPosition, &mSize, &mRotation);
}