#pragma once
#include "cocos2d.h"

USING_NS_CC;
class MapLayer:public Layer
{
public:
	MapLayer();
	~MapLayer();
	static MapLayer* create();
	bool init();
	Vector<Sprite *> _bricks;
	TMXTiledMap* _map;
	TMXLayer* _brickLayer;
	TMXLayer* _hideLayer;
	Vector<Sprite *> getAllBricks() { return _bricks; }
};

