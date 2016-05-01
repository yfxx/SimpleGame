#pragma once
#include "cocos2d.h";
using namespace cocos2d;
class GoostBase:public Sprite
{
public:
	float _speed;
	Vect _direction;
	Vec2 _desiredPosition;
public:
	GoostBase();
	~GoostBase();
	virtual void move(float t);
	virtual bool isDesiredPositionValid();
};

