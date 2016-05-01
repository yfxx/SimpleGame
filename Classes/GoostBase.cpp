#include "GoostBase.h"
#include  "GameScene.h"

#define GOOST_CENTER_TO_SIDE 14.5

GoostBase::GoostBase()
{
}


GoostBase::~GoostBase()
{
}

void GoostBase::move(float t) {
	Vec2 position = this->getPosition();
	float friction = 1;//摩擦系数
	//求出当前player位置在tmx地图中的位置
	Point tileCoord;
	tileCoord.x = position.x / 16;
	tileCoord.y = (Director::getInstance()->getVisibleSize().height - 80 - position.y) / 16;
	int tiled = GameScene::getInstance()->_mapLayer->_brickLayer->getTileGIDAt(tileCoord);
	if (tiled == 7)
		friction = 0.5;
	else if (tiled == 14)
		friction = 2;
	Size _size = Director::getInstance()->getVisibleSize();
	Size _tankSize = this->getContentSize();

	_desiredPosition = this->getPosition() + _direction * t * _speed*friction;
	if (isDesiredPositionValid())
		this->setPosition(_desiredPosition);

	// 转向
	//if (_direction == Vec2(0, 1)) {				// 向上
	//	this->setRotation(0);
	//}
	//else if (_direction == Vec2(0, -1)) {		// 向下
	//	this->setRotation(180);
	//}
	//else if (_direction == Vec2(-1, 0)) {		// 向左
	//	this->setRotation(-90);
	//}
	//else if (_direction == Vec2(1, 0)) {		// 向右
	//	this->setRotation(90);
	//}
}

bool GoostBase::isDesiredPositionValid() {
	Rect box;
	box.origin = this->getBoundingBox().origin + (_desiredPosition - this->getPosition());
	box.size = Size(GOOST_CENTER_TO_SIDE * 2, GOOST_CENTER_TO_SIDE * 2);

	// detect boundary collision
	auto vsize = Director::getInstance()->getVisibleSize();
	if (_desiredPosition.x > vsize.width - GOOST_CENTER_TO_SIDE || _desiredPosition.x < GOOST_CENTER_TO_SIDE
		|| _desiredPosition.y > vsize.height-80 - GOOST_CENTER_TO_SIDE || _desiredPosition.y < GOOST_CENTER_TO_SIDE) {
		return false;
	}

	// detect brick collision
	auto bricks = GameScene::getInstance()->_mapLayer->getAllBricks();
	for (int i = 0; i < bricks.size(); i++) {
		auto brick = bricks.at(i);
		if (brick->getBoundingBox().intersectsRect(box)) {
			return false;
		}
	}

	return true;
}