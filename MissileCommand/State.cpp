#include "State.h"

/*
State::State(Resources* _TextureCtrl)
{
	mTextureCtrl = _TextureCtrl;
}

State::~State()
{

}

State::State(State& _State)
{
	mResources = *_State.GetResources();
	mTextureCtrl = _State.GetTextureCtrl();
}

*/
/*void State::AddResource(Resource _Resource)
{
	// Check if resource already exists, ignore if so.
	for (std::vector<Resource>::iterator it = mResources.begin(); it != mResources.end(); ++it)
	{
		if (it->GetResourceName() == _Resource.GetResourceName())
		{
			return;
		}
	}

	mResources.push_back(_Resource);
}

void State::RemoveResource(Resource _Resource)
{
	// Check if resource already exists, remove it if so.
	for (std::vector<Resource>::iterator it = mResources.begin(); it != mResources.end(); ++it)
	{
		if (it->GetResourceName() == _Resource.GetResourceName())
		{
			mResources.erase(it);
			return;
		}
	}
}

std::vector<Resource>* State::GetResources()
{
	return &mResources;
}*/

void State::PreTick()
{

}

void State::Tick()
{

}

// All rendering
void State::PostTick()
{

}

void State::EnterState()
{

}

void State::ExitState()
{

}