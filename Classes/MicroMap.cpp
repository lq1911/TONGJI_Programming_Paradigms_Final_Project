#include "MicroMap.h"

USING_NS_CC;

bool MicroMap::init() {
	if (!Layer::init()) {
		return false;
	}

	// 获取屏幕尺寸
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//创建大地图精灵
	auto WorldMap= Sprite::create("Maps/MicroMap/WorldMap.png");

	//设置大地图精灵的位置和大小
	WorldMap->setPosition(visibleSize/2);
	WorldMap->setScale(3.0f);
		
	//添加大地图精灵到层
	this->addChild(WorldMap);

	Director::getInstance()->resume();

	return true;
}

void MicroMap::UpdatePlayerPos(Vec2& pos) {
	// 更新玩家在小地图上的位置
	PlayerPos = pos;

	// 删除上一次创建的玩家图标（如果有的话）
	if (PlayerSprite) {
		PlayerSprite->removeFromParent();
	}

	// 创建新的玩家图标
	PlayerSprite = Sprite::create("Maps/MicroMap/PlayerMark.png");
	PlayerSprite->setPosition(PlayerPos);
	PlayerSprite->setScale(0.8f);

	//将玩家图标添加到层
	this->addChild(PlayerSprite);
}