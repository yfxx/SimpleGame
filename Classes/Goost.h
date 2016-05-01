#pragma once
#include "GoostBase.h"
#include "cocos2d.h"
using  namespace cocos2d;

class Goost:public GoostBase
{
public:
	virtual bool init(std::string path);
	void ai(float);
private:
	int _count;
	float _nextDecisionTime;	// 下次决策时间
	float _decisionTimeCounter;
public:
	Goost();
	~Goost();
};

class GoostOne :public Goost {
public:
	virtual bool init();
	CREATE_FUNC(GoostOne);
};

class GoostTwo :public Goost {
public:
	virtual bool init();
	CREATE_FUNC(GoostTwo);
	bool isDesiredPositionValid();
};
