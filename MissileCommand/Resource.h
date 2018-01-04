#pragma once
#include <string>
#include "Resources.h"

class Resource
{
protected:
	//Resources* mResourceCtrl;

	std::string mResourceName;
	std::string mResourceLocation;

	double mX;
	double mY;
	double mWidth;
	double mHeight;
	double mRotation;

	bool mEnabled;
public:
	//Resource(Resources* _ResourceCtrl = NULL, std::string _ResourceName = "", std::string _ResourceLocation = "", double _Width = 0.0, double _Height = 0.0, double _X = 0.0, double _Y = 0.0, double _Rotation = 0.0);
	//~Resource();
	//Resource(const Resource& _Resource);

	//Resources* GetResourceCtrl() { return mResourceCtrl; }

	std::string GetResourceName() { return mResourceName; }
	std::string GetResourceLocation() { return mResourceLocation; }

	double GetX() { return mX; }
	double GetY() { return mY; }
	double GetWidth() { return mWidth; }
	double GetHeight() { return mHeight; }
	double GetRotation() { return mRotation; }

	bool GetEnabled() { return mEnabled; }

	//void SetResourceCtrl(Resources* _ResourceCtrl) { mResourceCtrl = _ResourceCtrl; }
	void SetResourceName(std::string _ResourceName) { mResourceName = _ResourceName; }
	void SetResourceLocation(std::string _ResourceLocation) { mResourceLocation = _ResourceLocation; }
	void SetX(double _X) { mX = _X; }
	void SetY(double _Y) { mY = _Y; }
	void SetWidth(double _Width) { mWidth = _Width; }
	void SetHeight(double _Height) { mHeight = _Height; }
	void SetRotation(double _Rotation) { mRotation = _Rotation; }
	void SetEnabled(bool _Enabled) { mEnabled = _Enabled; }
};