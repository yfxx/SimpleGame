#pragma once
#include "cocos2d.h"
class GameEndScene:public cocos2d::Layer
{
public:
	GameEndScene();
	~GameEndScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuReplay(cocos2d::Ref* pSender);
	void memuBack(cocos2d::Ref* pSender);
	CREATE_FUNC(GameEndScene);
};

