#include "MainMenuBackgroundObject.h"
#include "GlobalDefines.h"
#include "Game.h"
#include "Message.h"
#include "GameThreadUnsafeScope.h"
#include "World.h"

void MainMenuBackgroundObject::RenderTick(sf::RenderWindow* _RenderWindow)
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

MainMenuBackgroundObject::MainMenuBackgroundObject(Game* _Game, GameObject* _Parent) : GameObject(_Game, _Parent)
{
	InitializeGameObject();
}

void MainMenuBackgroundObject::Tick(sf::Time _DeltaTime)
{
	if (!mAddedToRenderer)
	{
		mAddedToRenderer = true;
		mGame->AddObjectToRenderer(this, mLayer);

		if (mRenderTexture.loadFromFile("Resources\\mainmenu.png"))
		{
			mSprite.setTexture(mRenderTexture);
			mSprite.setOrigin(mSprite.getTextureRect().width / 2, mSprite.getTextureRect().height / 2);
			bDrawSprite = true;
		}
	}
	GameObject::Tick(_DeltaTime);
}

void MainMenuBackgroundObject::InitializeGameObject()
{
	mRenderShape = sf::RectangleShape(sf::Vector2f(1, 1));
	mRenderShape.setFillColor(sf::Color(255, 0, 0, 255));
	mRenderShape.setOrigin(0.5f, 0.5f);
	mRenderShape.setScale(1, 1);
	mLayer = LAYER_GAME_SHIP;
	mSize = std::pair<double, double>(1, 1);
}