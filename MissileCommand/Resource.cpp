#include "Resource.h"

/*
Resource::Resource(Resources* _ResourceCtrl, std::string _ResourceName, std::string _ResourceLocation, double _Width, double _Height, double _X, double _Y, double _Rotation)
{
	mResourceCtrl = _ResourceCtrl;
	mResourceName = _ResourceName;
	mResourceLocation = _ResourceLocation;
	mX = _X;
	mY = _Y;
	mWidth = _Width;
	mHeight = _Height;
	mRotation = _Rotation;
	mEnabled = false;

	if (mResourceCtrl && _ResourceName.length() > 0 && _ResourceLocation.length() > 0)
	{
		mResourceCtrl->AddTexture(_ResourceLocation);
	}
}

Resource::~Resource()
{

}

Resource::Resource(const Resource& _Resource)
{
	mResourceName = _Resource.mResourceName;
	mResourceLocation = _Resource.mResourceLocation;
	mResourceCtrl = _Resource.mResourceCtrl;

	mX = _Resource.mX;
	mY = _Resource.mY;
	mWidth = _Resource.mWidth;
	mHeight = _Resource.mHeight;
	mRotation = _Resource.mRotation;

	mEnabled = _Resource.mEnabled;
}*/