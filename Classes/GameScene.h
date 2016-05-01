#pragma once

#include "cocos2d.h"
#include "MapLayer.h"
#include "Player.h"
#include "Goost.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	Player *player;
	MapLayer * _mapLayer;
	int _presskeyNum;
	Vector<Sprite*>goostVec;
	Vector<Sprite*>gemVec;
	Vec2 bornVec[5];
	int _playLifeNum;	//玩家生命数
	int _eatGems;		//吃掉的宝石数
	int _totalGems;		//宝石总数
	float _curTime;		//当前时间
	float _totalTime;		//总时间
public:
	
	~GameScene(); 
	static GameScene* getInstance();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameScene);
	void update(float delta);
	void collisionDetection(float);
	void timeDctection(float);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*event);
	Point objectPosition(TMXObjectGroup *group, std::string object);
	Vec2  GameScene::randomPosition();
	void gameOver(bool);
private:
	GameScene();
	static GameScene * _instance;
};



