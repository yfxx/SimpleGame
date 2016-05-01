#include "MapLayer.h"



MapLayer::MapLayer()
{
}


MapLayer::~MapLayer()
{
}

MapLayer* MapLayer::create() {
	auto ml = new MapLayer();
	if (ml && ml->init()) {
		ml->autorelease();
		return ml;
	}
	CC_SAFE_DELETE(ml);
	return NULL;
}

bool MapLayer::init() {
	if (!Layer::init()) return false;
	_map = TMXTiledMap::create("map_1.tmx");
	
	_brickLayer = _map->getLayer("backgound");
	_hideLayer = _map->getLayer("hidelayer");
	_brickLayer->setZOrder(0);
	_hideLayer->setZOrder(2);
	this->addChild(_map);

	for (int i = 0; i < _map->getMapSize().width; i++) {
		for (int j = 0; j < _map->getMapSize().height; j++) {
			auto tile = _brickLayer->getTileAt(Vec2(i, j));
			if (tile != NULL) {
				auto gid = _brickLayer->getTileGIDAt(Vec2(i, j));
				if (gid == 1) {
					_bricks.pushBack(tile);
				}
			}
		}
	}
	return true;
}

