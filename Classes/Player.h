#pragma once
#include "GoostBase.h"
class Player : public GoostBase
{
public:
	virtual bool init();
	CREATE_FUNC(Player);
	void respawn();
	bool _isMoving;
public:
	Player();
	~Player();
};

