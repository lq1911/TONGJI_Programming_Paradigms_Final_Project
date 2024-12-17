#include "Indoor.h"

Indoor::Indoor(Player* origin_player) {
	player = origin_player;
}

Scene* Indoor::createScene() {
	return Indoor::create();
}

bool Indoor::init() {
	if (!Scene::init()) {
		return false;
	}

	//获取屏幕尺寸
	visibleSize = Director::getInstance()->getVisibleSize();

	//初始化室内地图
	this->LoadMap();

	//初始化玩家位置
	player->setPosition(0, 0);


	//设置相机跟随玩家
	this->MainCameraFollowPlayer();

	return true;
}

void Indoor::LoadMap() {
	auto IndoorMap = TMXTiledMap::create("Maps/Indoors/InDoors.tmx");
	IndoorMap->setScale(1.0f);
	IndoorMap->setAnchorPoint(Vec2(0.5f, 0.5f));
	InitialObstacle(IndoorMap);

	this->addChild(IndoorMap);
}

void Indoor::InitialCamera() {
	camera = getDefaultCamera();    //获取默认相机
}