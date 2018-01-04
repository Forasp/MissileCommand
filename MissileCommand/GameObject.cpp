#include "GameObject.h"
#include "Game.h"
#include "Message.h"
#include "GameThreadUnsafeScope.h"
#include "Controller.h"

GameObject::~GameObject()
{
	if (mGame != nullptr && mAddedToRenderer)
	{
		GameThreadUnsafeScope ScopeLock(mGame);
		mGame->RemoveObjectFromRenderer(this, mLayer);
		mAddedToRenderer = false;
	}
}

void GameObject::RenderTick(sf::RenderWindow* _RenderWindow)
{
	if (!mAddedToRenderer)
	{
		if (!mSprite.getTexture())
		{
			return;
		}
		mGame->AddObjectToRenderer(this, mLayer);
		mAddedToRenderer = true;
	}

	mRenderStates.transform = getTransform();
	_RenderWindow->draw(mSprite, mRenderStates);
}

void GameObject::SetTexResources(TextureResources* _ResourceHolder)
{
	mResourceHolder = _ResourceHolder;
}

void GameObject::Tick(sf::Time _DeltaTime)
{
	float TimeMult = _DeltaTime.asSeconds();
	mPosition.first += mVelocity.first * TimeMult;
	mPosition.second += mVelocity.second * TimeMult;

	for (std::shared_ptr<GameObject> it : mChildren)
	{
		it->Tick(_DeltaTime);
	}
}

void GameObject::ReadMessage(Message* _Message)
{
	HandleMessage(_Message);
	if (mController != nullptr)
	{
		mController->ReadMessage(_Message);
	}
}


void GameObject::ControllerTick(sf::Time _DeltaTime)
{
	if (mController != nullptr)
	{
		mController->ControllerTick();
	}
}

void GameObject::RemoveChild(GameObject* _GameObject)
{
	for (int i = 0; i < mChildren.size(); i++)
	{
		if (mChildren[i].get() == _GameObject)
		{
			GameThreadUnsafeScope ScopeLock(mGame);
			mChildren.erase(mChildren.begin() + i);
			return;
		}
	}

	if (mParent != nullptr)
	{
		mParent->RemoveChild(_GameObject);
	}
}

void GameObject::AddChild(std::shared_ptr<GameObject> _GameObject)
{
	mChildren.push_back(_GameObject);
}