#include "GameScene.h"
#include "GameEndScene.h"

#define BORNPLACE1 Vec2(visibleSize.width/2,visibleSize.height-80 - 32)
#define BORNPLACE2 Vec2(32,visibleSize.height-200 - 32)
#define BORNPLACE3 Vec2(visibleSize.width - 32, visibleSize.height-80 - 32)
#define BORNPLACE4 Vec2(visibleSize.width - 200, 260)
#define BORNPLACE5 Vec2(visibleSize.width - 500, 30)

USING_NS_CC;
GameScene* GameScene::_instance = NULL;

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

GameScene* GameScene::getInstance() {
	if (_instance == NULL) {
		_instance = GameScene::create();
	}
	return _instance;
}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::getInstance();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_playLifeNum = 3;
	_eatGems = 0;
	_curTime = 0.0;
	_totalTime = 120.0;
	bornVec[0] = BORNPLACE1;
	bornVec[1] = BORNPLACE2;
	bornVec[2] = BORNPLACE3;
	bornVec[3] = BORNPLACE4;
	bornVec[4] = BORNPLACE5;
	//添加地图
	_mapLayer = MapLayer::create();
	if (_mapLayer) {
		//_mapLayer->retain();
		this->addChild(_mapLayer);
	}
	
	//创建玩家
	player = Player::create();
	player->setPosition(ccp(16,16));
	_mapLayer->_map->addChild(player,0);


	//创建宝石

	TMXObjectGroup* objects = _mapLayer->_map->objectGroupNamed("objects");
	_totalGems = objects->getObjects().size();
	
	for (int i = 0; i < _totalGems; i++)
	{
		auto diamond = Sprite::create("gem.png");
		//string 转 int
		char t[10];
		sprintf(t, "%d", i);
		std::string gem = "gem";
		Point tankPoint = this->objectPosition(objects, gem.append(t));
		diamond->setPosition(ccp(tankPoint.x + diamond->boundingBox().size.width / 2, tankPoint.y + diamond->boundingBox().size.height / 2));
		_mapLayer->_map->addChild(diamond);
		gemVec.pushBack(diamond);
	}

	//创建幽灵
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		auto goost1 = GoostOne::create();
		auto r = rand() % 5;
		goost1->setPosition(bornVec[i]);
		_mapLayer->_map->addChild(goost1);
		goostVec.pushBack(goost1);
	}
	for (int i = 0; i < 3; i++)
	{
		auto goost2 = GoostTwo::create();
		goost2->setPosition(randomPosition());
		_mapLayer->_map->addChild(goost2);
		goostVec.pushBack(goost2);
	}
	//创建道具
	auto heart = Sprite::create("heart.png");
	heart->setPosition(randomPosition());
	heart->setTag(20);
	_mapLayer->_map->addChild(heart);

	auto sun = Sprite::create("sun.png");
	sun->setPosition(randomPosition());
	sun->setTag(30);
	_mapLayer->_map->addChild(sun);
	//添加文本
	Label * lifeLabel = Label::createWithSystemFont(StringUtils::format(" LIFE : %d", _playLifeNum), "Arial", 20);
	lifeLabel->setPosition(100, visibleSize.height-40);
	lifeLabel->setName("lifeLabel");
	this->addChild(lifeLabel);

	Label * scoreLabel = Label::createWithSystemFont(StringUtils::format(" Gem : %d / %d", _eatGems,_totalGems), "Arial", 20);
	scoreLabel->setPosition(300, visibleSize.height - 40);
	scoreLabel->setName("scoreLabel");
	this->addChild(scoreLabel);
	
	//添加进度条
	Label * timeLabel = Label::createWithSystemFont(StringUtils::format(" Time : %d / %d", (int)_curTime, (int)_totalTime), "Arial", 20);
	timeLabel->setPosition(550, visibleSize.height - 40);
	timeLabel->setTag(100);
	this->addChild(timeLabel);

	Sprite* pbg = Sprite::create("jindu1.png");
	pbg->setPosition(780, visibleSize.height - 40);//进度条的背景
	pbg->setScaleY(0.5);
	pbg->setScaleX(0.7);
	this->addChild(pbg);
	auto loadingBar = ProgressTimer::create(Sprite::create("jindu2.png"));
	loadingBar->setTag(101);
	loadingBar->setScaleY(0.5);
	loadingBar->setScaleX(0.7);
	loadingBar->setType(kCCProgressTimerTypeBar);
	loadingBar->setPosition(780, visibleSize.height - 40);
	loadingBar->setMidpoint(ccp(0, 0));   //设置进度条走的开始位置。 
	loadingBar->setBarChangeRate(ccp(1, 0));//  用来设置进度条动画方向的，（1,0）表示横方向，（0,1）表示纵方向。
	loadingBar->setPercentage(0);
	this->addChild(loadingBar);

	//添加键盘事件
	_presskeyNum = 0;
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	//游戏主循环，每帧调用
	scheduleUpdate();
	this->schedule(schedule_selector(GameScene::collisionDetection), 1 / 60.0f);
	this->schedule(schedule_selector(GameScene::timeDctection), 1);
	return true;
}

Point GameScene::objectPosition(TMXObjectGroup *group, std::string object)
{
	Point point;
	ValueMap dic = group->objectNamed(object);
	point.x = dic["x"].asFloat();
	point.y = dic["y"].asFloat();
	return point;


}

void GameScene::update(float delta)
{
	if (player->_isMoving) 
	{
		player->move(delta);		// 移动英雄
	}
}

void GameScene::timeDctection(float t)
{
	_curTime += t;
	ProgressTimer* loadingBar = static_cast<ProgressTimer*>(this->getChildByTag(101));
	float progress = 100 * (_curTime / _totalTime);
	loadingBar->setPercentage(progress);
	Label* timeLabel = static_cast<Label*>(this->getChildByTag(100));
	timeLabel->setString(StringUtils::format(" Time : %d / %d", (int)_curTime, (int)_totalTime));
	if (_curTime >= _totalTime)
	{
		gameOver(false);
	}
}

void GameScene::collisionDetection(float t) 
{
	Sprite* gem;
	for (int i = 0; i < gemVec.size(); i++)
	{
		//enemyS = dynamic_cast<CCSprite*>(enemyO);
		gem = gemVec.at(i);
		if (player->getBoundingBox().intersectsRect(gem->getBoundingBox()))
		{
			CCLOG("BOOM!");
			gem->removeFromParentAndCleanup(true);
			gemVec.eraseObject(gem);
			_eatGems++;
			Label* scoreLabel = static_cast<Label*>(this->getChildByName("scoreLabel"));
			scoreLabel->setString(StringUtils::format(" Gem : %d / %d", _eatGems, _totalGems));
			break;
		}
	}
	if (_eatGems == _totalGems)
		gameOver(true);
	Sprite* goost;
	for (int i = 0; i < goostVec.size(); i++)
	{
		//enemyS = dynamic_cast<CCSprite*>(enemyO);
		goost = goostVec.at(i);
		if (player->getBoundingBox().intersectsRect(goost->getBoundingBox()))
		{
			CCLOG("BOOM!");
			_playLifeNum--;
			Label* lifeLabel = static_cast<Label*>(this->getChildByName("lifeLabel"));
			lifeLabel->setString(StringUtils::format(" LIFE : %d", _playLifeNum));
			if (_playLifeNum == 0)
				gameOver(false);
			player->respawn();
			break;
		}
	}
	Sprite* heart = static_cast<Sprite*>(_mapLayer->_map->getChildByTag(20));
	if (heart&&player->getBoundingBox().intersectsRect(heart->getBoundingBox()))
	{
		heart->removeFromParentAndCleanup(true);
		_playLifeNum++;
		Label* lifeLabel = static_cast<Label*>(this->getChildByName("lifeLabel"));
		lifeLabel->setString(StringUtils::format(" LIFE : %d", _playLifeNum));
	}
	Sprite* sun = static_cast<Sprite*>(_mapLayer->_map->getChildByTag(30));
	if (sun&&player->getBoundingBox().intersectsRect(sun->getBoundingBox()))
	{
		sun->removeFromParentAndCleanup(true);
		_totalTime += 20;
	}	
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with keycode %d pressed", keyCode);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		player->_direction = Vec2(-1, 0);
		player->_isMoving = true;
		_presskeyNum++;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		player->_direction = Vec2(1, 0);
		player->_isMoving = true;
		_presskeyNum++;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		player->_direction = Vec2(0, 1);
		player->_isMoving = true;
		_presskeyNum++;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		player->_direction = Vec2(0, -1);
		player->_isMoving = true;
		_presskeyNum++;
		break;
	default:
		break;
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with keycode %d released", keyCode);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (!--_presskeyNum) {
			player->_direction = Vec2::ZERO;
			player->_isMoving = false;
		}
		break;
	default:
		break;
	}
}


Vec2  GameScene::randomPosition() {
	Size size = Director::getInstance()->getVisibleSize();
	float x = CCRANDOM_0_1()* (size.width-16);
	float y = CCRANDOM_0_1()* (size.height-80-16);
	if (x < 16)x = 16;
	if (y < 16)y = 16;
	return  Vec2(x, y);
}

void GameScene::gameOver(bool isWin)
{
	player->setVisible(false);
	this->unscheduleAllSelectors();	// 取消所有定时器

	auto over = Sprite::create("over.png");
	over->setPosition(Director::getInstance()->getVisibleSize() / 2 + Size(0, 400));
	auto gameOverLayer = Layer::create();
	gameOverLayer->addChild(over);
	this->addChild(gameOverLayer);

	auto move = MoveBy::create(2, Vec2(0, -400));
	auto delay = DelayTime::create(1);
	auto cal = CallFunc::create([=]() {
		if (!isWin){
			auto gameEndScene = GameEndScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameEndScene));
		}
		else {
			auto gameEndScene = GameEndScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameEndScene));
		}
		//清空GameScene
		GameScene::getInstance()->removeAllChildrenWithCleanup(true);
		GameScene::_instance = NULL;
	});
	over->runAction(Sequence::create(move, delay, cal, NULL));
}