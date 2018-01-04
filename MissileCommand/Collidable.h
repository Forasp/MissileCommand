#pragma once
#include <utility>
#include "Listener.h"
#include "SFML/Graphics/Sprite.hpp"
#include <math.h>

class Message;

class Collidable : public virtual Listener
{
public:
	Collidable() {
		mPositionPtr = nullptr;
		mSizePtr = nullptr;
		mRotationPtr = nullptr;
	}

	virtual void Collide(Collidable* _Collidable) = 0;
	virtual void CheckCollision(Collidable* _Collidable);
	void CreateCollider(std::pair<double, double>* _PositionPtr, std::pair<double, double>* _SizePtr, double* _RotationPtr);
	void CollisionTick();
	void ReadMessage(Message* _Message);
	virtual void CollisionBroadcast() = 0;
	virtual void PopulateCollisionAreas(sf::Sprite* _Sprite);

	std::pair<double, double>* mPositionPtr;
	std::pair<double, double>* mSizePtr;
	double* mRotationPtr;
	std::pair<double, double> mPastPosition;
	std::pair<double, double> mPastSize;
	double mPastRotation;

	bool mCollisionAreaXL[2][2];
	bool mCollisionAreaL[4][4];
	bool mCollisionAreaM[8][8];
	bool mCollisionAreaS[16][16];
	bool mCollisionAreaXS[32][32];


};

inline double DistanceBetweenPoints(const std::pair<double, double>* _Position1, const std::pair<double, double>* _Position2)
{
	return sqrt((_Position1->first - _Position2->first)*(_Position1->first - _Position2->first) + (_Position1->second - _Position2->second)*(_Position1->second - _Position2->second));
}

inline double RadiusFromSize(const std::pair<double, double>* _Size)
{
	return sqrt(((_Size->first / 2) * (_Size->first / 2)) + ((_Size->second / 2) * (_Size->second / 2)));
}

inline std::pair<double, double> RotateVector(std::pair<double, double>* _InVector, double _RotationInDegrees)
{
	double RadianRotation = _RotationInDegrees * 0.0174533;
	double Sine = sin(RadianRotation);
	double Cosine = cos(RadianRotation);

	return std::make_pair(double(_InVector->first * Cosine - _InVector->second * Sine), double(_InVector->first * Sine + _InVector->second * Cosine));
}