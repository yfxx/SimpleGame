#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

bool Player::init() {
	if (!Sprite::initWithFile("player.png")) return false;
	_speed = 100;
	_direction = Vec2(0, 1);
	_isMoving = false;
	return true;
}

void Player::respawn() {
	this->setPosition(16, 16);
	//SimpleAudioEngine::getInstance()->playEffect("respawn.wav");
}