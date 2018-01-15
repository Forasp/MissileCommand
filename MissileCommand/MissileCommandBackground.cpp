#include "MissileCommandBackground.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GlobalDefines.h"
#include "GameThreadUnsafeScope.h"
#include "World.h"

void MissileCommandBackground::RenderTick(sf::RenderWindow* _RenderWindow)
{
	mRenderShape.setScale(sf::Vector2f(mSize.first, mSize.second));
	mRenderShape.setRotation(mRotation);
	mRenderShape.setPosition(mPosition.first, mPosition.second);
	_RenderWindow->draw(mRenderShape);
}

void MissileCommandBackground::Tick(sf::Time _DeltaTime)
{
	if (!mAddedToRenderer)
	{
		mAddedToRenderer = true;
		mGame->AddObjectToRenderer(this, mLayer);
	}
	GameObject::Tick(_DeltaTime);
}

void MissileCommandBackground::InitializeGameObject()
{
	mRenderShape = sf::RectangleShape(sf::Vector2f(1,1));
	mRenderShape.setFillColor(sf::Color(125, 125, 125, 255));
	mRenderShape.setOrigin(0.5f, 0.5f);
	mRenderShape.setScale(1, 1);
	mLayer = LAYER_GAME_BACKGROUND;
	mSize = std::pair<double, double>(1, 1);
}