#include "GameEndScene.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

GameEndScene::GameEndScene()
{
}


GameEndScene::~GameEndScene()
{
}

Scene* GameEndScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameEndScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameEndScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("background.png");
	bg->setContentSize(visibleSize);
	bg->setAnchorPoint(Vec2::ZERO);
	this->addChild(bg);

	auto *item1 = MenuItemFont::create("Replay",this, menu_selector(GameEndScene::menuReplay));
	auto* item2 = MenuItemFont::create( "Back", this, menu_selector(GameEndScene::memuBack));
	item1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5 * 3));
	item2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5 * 2));

	auto pMenu = Menu::create(item1, item2, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);

	return true;
}

void GameEndScene::menuReplay(cocos2d::Ref* pSender)
{
	auto gameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5,gameScene));
}
void GameEndScene::memuBack(cocos2d::Ref* pSender)
{
	auto hello = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, hello));
}

