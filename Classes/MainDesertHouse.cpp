#include "WinterHouse.h"

USING_NS_CC;

Scene* WinterHouse::createScene(Player* origin_player) {
	return WinterHouse::create();
}

bool MainGameScene::init() {
	if (!Scene::init()) {
		return false;
	}

	this->LoadMapToScene();    //加载地图到场景
	this->LoadCameraToScene();    //初始化摄像机
	this->LoadPlayerToScene();    //加载玩家到场景
	this->LoadMonsterRespawnToScene();    //加载怪物刷新点到场景
	this->LoadNPCToScene();    //加载npc到场景
	this->LoadBagToScene();    //加载背包到场景
	this->LoadBackgroundMusicToScene();    //加载背景音乐到场景

	//添加键盘监听器，检测键盘活动
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(MainGameScene::KeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(MainGameScene::KeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

	//添加鼠标监听器，检测鼠标活动
	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseScroll = CC_CALLBACK_1(MainGameScene::MouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	this->MainCameraFollowPlayer();    //注册主地图摄像机跟随玩家的函数

	return true;
}

/****************************************************************/
////////////////以下为本场景所有用到的初始化函数/////////////////
WinterHouse::WinterHouse(Player* origin_player) {
	//获取屏幕尺寸
	VisibleSize = Director::getInstance()->getVisibleSize();

	PLAYER = origin_player;    //保存玩家实例

	_cameraManager = CameraManager::create();    // 初始化摄像机管理器
	_mapManager = MapManager::create();    // 初始化地图管理器
	_bagManager = BagManager::getInstance();     // 初始化背包管理器
	_musicManager = music::getInstance();    // 初始化背景音乐管理器
}

void WinterHouse::LoadMapToScene() {
	// 将地图管理器添加到场景中
	this->addChild(_mapManager);

	// 初始化室内地图，并添加地图至场景中
	_mapManager->InitialMap("Maps/Indoors/InDoors.tmx", Vec2(VisibleSize.width / 2, VisibleSize.height / 2), this);
}

void WinterHouse::LoadPlayerToScene() {
	// 将人物添加到场景中
	this->addChild(PLAYER);

	// 设置人物初始位置
	PLAYER->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 2));
}

void WinterHouse::LoadMonsterRespawnToScene() {
	// 加怪
	_monsterRespawn = new MonsterRespawn(PLAYER, this);

	// 将怪导入角色
	PLAYER->Init(_monsterRespawn->GetMonster(), _mapManager);
}

void WinterHouse::LoadNPCToScene() {
	// NPC管理器
	_npcManager = new NPCManager(PLAYER, _bagManager);

	// 监测npc是否在有效触发范围内
	this->schedule([=](float dt) {
		for (auto npc : _npcManager->visitNPC()) {
			npc->update();
		}
		}, 0.2f, "npc_check_scheduler");
}