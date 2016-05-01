#include "HelloWorldScene.h"
#include "GameScene.h"
#include "MapLayer.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object

	auto bg = Sprite::create("background.png");
	bg->setContentSize(visibleSize);
	bg->setAnchorPoint(Vec2::ZERO);
	this->addChild(bg);
	
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	auto* item1 = MenuItemImage::create("btn-play-normal.png", "btn-play-selected.png", this, menu_selector(HelloWorld::menuPlay));
	auto* item2 = MenuItemImage::create("btn-highscores-normal.png", "btn-highscores-selected.png", this, menu_selector(HelloWorld::memuScore));
	auto* item3 = MenuItemImage::create("btn-about-normal.png", "btn-about-selected.png", this, menu_selector(HelloWorld::menuAbout));
	item1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/6*4));
	item2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/6*3));
	item3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/6*2));

	auto pMenu = Menu::create(item1, item2, item3, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 2);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Little Game", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuPlay(cocos2d::Ref* pSender)
{
	Director* pDirector = Director::sharedDirector();
	Scene *pScene = GameScene::createScene();
	pDirector->replaceScene(TransitionFade::create(0.5, pScene));
}
void HelloWorld::memuScore(cocos2d::Ref* pSender)
{

}
void HelloWorld::menuAbout(cocos2d::Ref* pSender)
{
}
