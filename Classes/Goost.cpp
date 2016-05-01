#include "Goost.h"



Goost::Goost()
{
}


Goost::~Goost()
{
}

bool Goost::init(std::string path) {
	if (!GoostBase::initWithFile(path)) return false;

	_nextDecisionTime = CCRANDOM_MINUS1_1() + 1;
	_decisionTimeCounter = 0;
	srand(time(NULL));
	auto i = rand() % 3 - 1;
	_direction = Vec2(i, i != 0 ? 0 : -1);

	this->schedule(schedule_selector(Goost::move), 1 / 60.0f);
	this->schedule(schedule_selector(Goost::ai), 1 / 30.0f);

	return true;
}

void Goost::ai(float t) {	// 转向
								// 决策
	if (_decisionTimeCounter > _nextDecisionTime) {
		// 转向
		Vec2 v = _direction;
		auto i = rand() % 3 - 1;
		_direction = Vec2(i, i != 0 ? 0 : (rand() % 2 == 0 ? 1 : -1));
		_nextDecisionTime = CCRANDOM_MINUS1_1() + 1;
		_decisionTimeCounter = 0;
	}
	else {
		_decisionTimeCounter += t;
	}
}


bool GoostOne::init() {
	if (!Goost::init("goost1.png")) return false;

	_speed = 70;

	return true;
}

bool GoostTwo::init() {
	if (!Goost::init("goost2.png")) return false;

	_speed = 100;

	return true;
}

bool GoostTwo::isDesiredPositionValid()
{
	auto vsize = Director::getInstance()->getVisibleSize();
	if (_desiredPosition.x > vsize.width - this->getBoundingBox().size.width/2 || _desiredPosition.x < this->getBoundingBox().size.width / 2
		|| _desiredPosition.y > vsize.height - 80 - this->getBoundingBox().size.height/ 2 || _desiredPosition.y < this->getBoundingBox().size.height / 2) {
		return false;
	}
	return true;
}