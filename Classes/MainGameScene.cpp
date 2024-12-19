#include "MainGameScene.h"

#define Derivation 243

USING_NS_CC;

Scene* MainGameScene::createScene() {
    return MainGameScene::create();
}

bool MainGameScene::init() {
    if (!Scene::init()) {
        return false;
    }

	this->LoadMapToScene();    //加载地图到场景
	this->LoadCameraToScene();    //初始化摄像机
	this->LoadPlayerToScene();    //加载玩家到场景
	this->LoadBagToScene();    //加载背包到场景
	this->LoadMonsterRespawnToScene();    //加载怪物刷新点到场景
	this->LoadNPCToScene();    //加载npc到场景

	//添加键盘监听器，检测键盘活动
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(MainGameScene::KeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(MainGameScene::KeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

	//添加鼠标监听器，检测鼠标活动
	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseUp = CC_CALLBACK_1(MainGameScene::MouseClicked, this);
	_mouseListener->onMouseScroll = CC_CALLBACK_1(MainGameScene::MouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	this->MainCameraFollowPlayer();    //注册主地图摄像机跟随玩家的函数

    return true;
}

/****************************************************************/
////////////////以下为本场景所有用到的初始化函数/////////////////
MainGameScene::MainGameScene() {
	//获取屏幕尺寸
	VisibleSize = Director::getInstance()->getVisibleSize();

	_cameraManager = CameraManager::create();  // 初始化摄像机管理器
	_mapManager = MapManager::create();  // 初始化地图管理器
}

void MainGameScene::LoadCameraToScene() {
	// 将摄像机管理器添加到场景中
	this->addChild(_cameraManager); 

	// 初始化主地图摄像机，并添加摄像机至场景中
	_cameraManager->InitialMainCamera(this);

	// 初始化小地图摄像机，并添加摄像机至场景中
	_cameraManager->InitialMicroCamera(this);
}

void MainGameScene::LoadMapToScene() {
	//地图的长度与宽度均为50，每个图块像素大小为32，所以地图大小为1600
	const int MapSize = 1600;

	// 将地图管理器添加到场景中
	this->addChild(_mapManager);

	// 将复苏神庙地图加载至场景中
	_mapManager->InitialMap("Maps/RebirthTemple/RebirthTemple.tmx", Vec2(VisibleSize.width / 2, VisibleSize.height / 2), this);

	//将火山地图加载至场景中
	_mapManager->InitialMap("Maps/volcano/volcano.tmx", Vec2(VisibleSize.width / 2 - MapSize - Derivation, VisibleSize.height / 2 + MapSize + Derivation), this);

	//将雪地地图加载至场景中
	_mapManager->InitialMap("Maps/SnowyWinter/SnowyWinter.tmx", Vec2(VisibleSize.width / 2 + MapSize + Derivation, VisibleSize.height / 2 + MapSize + Derivation), this);

	//将沙漠地图加载至场景中
	_mapManager->InitialMap("Maps/DeathDesert/DeathDesert.tmx", Vec2(VisibleSize.width / 2 + MapSize + Derivation, VisibleSize.height / 2 - MapSize - Derivation), this);

	//将森林地图加载至场景中
	_mapManager->InitialMap("Maps/BrightForest/BrightForest.tmx", Vec2(VisibleSize.width / 2 - MapSize - Derivation, VisibleSize.height / 2 - MapSize - Derivation), this);

	//将火山雪地边界加载至场景中
	_mapManager->InitialMap("Maps/Vol_Snow_Ecotonal/Vol_Snow_Ecotonal.tmx", Vec2(VisibleSize.width / 2, VisibleSize.height / 2 + MapSize + Derivation), this);

	//将火山森林边界加载至场景中
	_mapManager->InitialMap("Maps/Vol_Forest_Ecotonal/Vol_Forest_Ecotonal.tmx", Vec2(VisibleSize.width / 2 - MapSize - Derivation, VisibleSize.height / 2), this);

	//将沙漠雪地边界加载至场景中
	_mapManager->InitialMap("Maps/Desert_Snow_Ecotonal/Desert_Snow_Ecotonal.tmx", Vec2(VisibleSize.width / 2 + MapSize + Derivation, VisibleSize.height / 2), this);

	//将森林沙漠边界加载至场景中
	_mapManager->InitialMap("Maps/Forest_Desert_Ecotonal/Forest_Desert_Ecotonal.tmx", Vec2(VisibleSize.width / 2, VisibleSize.height / 2 - MapSize - Derivation), this);

	//初始化小地图中黑色雾的显示
	_mapManager->SetBlackFogInMicroMap();    
}

void MainGameScene::LoadBagToScene() {
	_bagManager = BagManager::getInstance();
	if (_bagManager->getParent() == nullptr)
	{
		PLAYER->addChild(_bagManager);
	}
}

void MainGameScene::LoadPlayerToScene() {
	// 玩家
	PLAYER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, VisibleSize.width / 2, VisibleSize.height / 2, 0.5f, 100, 50, 20, 50, 10, 192, 1);
}

void MainGameScene::LoadMonsterRespawnToScene() {
	// 加怪
	_monsterRespawn = new MonsterRespawn(PLAYER, this);

	// 将怪导入角色
	PLAYER->InitMonster(_monsterRespawn->GetMonster());
}

void MainGameScene::LoadNPCToScene() {
	// NPC管理器
	_npcManager = new NPCManager(PLAYER, _bagManager);

	// 在地图中加入npc
	_npcManager->addNPC("npc1", VisibleSize.width / 2, VisibleSize.height / 2, 1.0f, this);

	// 监测npc是否在有效触发范围内
	this->schedule([=](float dt) {
		for (auto npc : _npcManager->visitNPC()) {
			npc->update();
		}
		}, 0.2f, "npc_check_scheduler");
}

/****************************************************************/
	////////////////以下为本场景声明的本场景特有功能函数/////////////////
void MainGameScene::CameraFollowController() {
	// 注册鼠标事件，用于控制摄像机跟随
	if (_cameraManager->IsInMicroMap()) {
		this->MicroCameraFollowPlayer();    //注册小地图摄像机跟随玩家的函数
	}
	else {
		this->MainCameraFollowPlayer();    //注册主地图摄像机跟随玩家的函数
	}
}

void MainGameScene::MainCameraFollowPlayer() {
	// 设置摄像机的初始位置
	float InitCameraZinMainMap = 600.0f;

	//每次进入主地图时，将主摄像机的位置设置为玩家位置
	Vec2 playPosition = PLAYER->mySprite->getPosition();
	_cameraManager->UpdateCameraPosition(_cameraManager->GetMainCamera(), playPosition, InitCameraZinMainMap);

	// 设置主摄像机的实时跟随任务
	this->schedule([=](float dt) {
		float updatedCameraZ = _cameraManager->GetMainCamera()->getPosition3D().z;    //获取摄像机的高度
		Vec2 playerPosition = PLAYER->mySprite->getPosition();    //获取玩家位置
		_mapManager->PlayerPositionInWhichMap(playerPosition);    //获取玩家所在地图
		_cameraManager->UpdateCameraPosition(_cameraManager->GetMainCamera(), playerPosition, updatedCameraZ);    //更新摄像机位置
		CCLOG("Player Position: %f, %f", playerPosition.x, playerPosition.y);
		}, "camera_update_key");
}

void MainGameScene::MicroCameraFollowPlayer() {
	// 设置摄像机的初始位置
	float InitCameraZinMicroMap = 2000.0f;

	// 每次进入小地图时，将小摄像机的位置设置中心位置
	Vec2 centerPosition(1200, 1200);
	_cameraManager->UpdateCameraPosition(_cameraManager->GetMicroCamera(), centerPosition, InitCameraZinMicroMap);
}

void MainGameScene::UnlockMapTeleport() {
	// 解锁传送门
	if (PLAYER->isTrigger(_mapManager->GetTeleportPosition(_mapManager->GetPlayerInWhichMap()))) {
		_mapManager->SetIsRegionRevealedTrue();
	}
}

void MainGameScene::TeleportPlayer(int MapID) {
	// 传送玩家
	if (_mapManager->GetTeleportPosition(MapID) != Vec2(0, 0)) {
		PLAYER->mySprite->stopAllActions();  // 停止当前的所有动作
		this->unscheduleAllCallbacks();  // 停止所有定时器
		PLAYER->mySprite->setPosition(_mapManager->GetTeleportPosition(MapID));
	}
}

/**********************************************************************/
////////////////以下为本场景所有与监视器相关的回调函数/////////////////
void MainGameScene::KeyPressedForRevealMicroMap(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_M) {
		//小地图中显示黑色雾效果的判断数组反转
		_mapManager->ReverseIsBlackFogVisible();
		// 更新小地图中黑色雾的显示
		_mapManager->SetBlackFogInMicroMap();

		/*此处切换小地图显示，进入小地图时首先隐藏初始地图，退出小地图之后再显示初始地图
		  让玩家在进入小地图之前就暂停游戏，退出小地图之后再恢复游戏，防止玩家在打开地图的时候发生意外*/
		if (_cameraManager->IsInMicroMap()) {
			// 恢复主地图响应和摄像机逻辑
			Director::getInstance()->resume();    //退出小地图恢复游戏
			_cameraManager->SwitchToMainCamera();    //切换到主摄像机
		}
		else {
			//进入小地图暂停游戏
			_cameraManager->SwitchToMicroCamera();    //切换到小摄像机
			Director::getInstance()->pause();     // 暂停游戏	
		}

		this->CameraFollowController();    //注册摄像机跟随玩家的函数
	}
}

void MainGameScene::KeyPressedForBag(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_B) {
		if (BagManager::getInstance()->isBagVisible())
			// 隐藏背包
			BagManager::getInstance()->hideBag(*PLAYER);
		else
			// 打开背包
			BagManager::getInstance()->showBag(*PLAYER);
	}
}

void MainGameScene::KeyPressedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event) {
	//int speed = 10;
	int speed = PLAYER->getSpeed();
	/* 移动:W/S/A/D */
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		HandlePlayerMove(Vec2(0, speed), 0, "MoveUP", UP);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		HandlePlayerMove(Vec2(0, -speed), 1, "MoveDOWN", DOWN);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		HandlePlayerMove(Vec2(-speed, 0), 2, "MoveLEFT", LEFT);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		HandlePlayerMove(Vec2(speed, 0), 3, "MoveRIGHT", RIGHT);
	}

	Vec2 playerPosition = PLAYER->mySprite->getPosition();
	_cameraManager->UpdateCameraPosition(_cameraManager->GetMainCamera(), playerPosition, _cameraManager->GetMainCamera()->getPosition3D().z);
}
void MainGameScene::KeyReleasedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		if (isKeyPressed[0]) {
			isKeyPressed[0] = false;
			PLAYER->mySprite->stopAllActions();  // 停止当前的所有动作
			this->unschedule("MoveUP");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		if (isKeyPressed[1]) {
			isKeyPressed[1] = false;
			PLAYER->mySprite->stopAllActions();  // 停止当前的所有动作
			this->unschedule("MoveDOWN");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		if (isKeyPressed[2]) {
			isKeyPressed[2] = false;
			PLAYER->mySprite->stopAllActions();  // 停止当前的所有动作
			this->unschedule("MoveLEFT");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		if (isKeyPressed[3]) {
			isKeyPressed[3] = false;
			PLAYER->mySprite->stopAllActions();  // 停止当前的所有动作
			this->unschedule("MoveRIGHT");
		}
	}
}
void MainGameScene::HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction) {
	Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;

	// 检查目标位置是否可移动
	/*if (IsMoveable(targetPosition))*/ {
		CCLOG("Move  first %d", direction);
		if (!isKeyPressed[keyIndex]) {
			isKeyPressed[keyIndex] = true;
			PLAYER->Move(direction);
			this->schedule([=](float dt) {
				PLAYER->Move(direction);
				}, 0.8f, scheduleKey);
			CCLOG("Move %d", direction);
		}
	}
}

void MainGameScene::KeyPressedForPlayerAttack(EventKeyboard::KeyCode keyCode, Event* event) {
	/* 攻击:I/K/J/L */
	if (keyCode == EventKeyboard::KeyCode::KEY_I) {
		PLAYER->Attack(UP, _monsterRespawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_K) {
		PLAYER->Attack(DOWN, _monsterRespawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		CCLOG("into attack");
		PLAYER->Attack(LEFT, _monsterRespawn->GetMonster());
		CCLOG("out attack");
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_L) {
		PLAYER->Attack(RIGHT, _monsterRespawn->GetMonster());
	}
}

void MainGameScene::KeyPressedForNPCInteract(EventKeyboard::KeyCode keyCode, Event* event) {
	if (_npcManager->getChattingStates())
		return;
	/* npc交互 */
	if (keyCode == EventKeyboard::KeyCode::KEY_C) {
		_npcManager->checkTriggers();
	}
}

void MainGameScene::KeyPressedForMicroMapMove(EventKeyboard::KeyCode keyCode, Event* event, Camera* camera, float MaxHeight, float MinHeight, float MaxWidth, float MinWidth, float ScrollSpeed) {
	Vec3 currentPosition = camera->getPosition3D();

	// 根据方向键控制摄像机的平移
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		currentPosition.y += ScrollSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		currentPosition.y -= ScrollSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		currentPosition.x -= ScrollSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		currentPosition.x += ScrollSpeed;
	}

	// 限制摄像机的移动边界（防止越界）
	currentPosition.x = std::min(currentPosition.x, MaxWidth);    // 限制最大宽度
	currentPosition.x = std::max(currentPosition.x, MinWidth);    // 限制最小宽度

	currentPosition.y = std::min(currentPosition.y, MaxHeight);    // 限制最大长度
	currentPosition.y = std::max(currentPosition.y, MinHeight);     // 限制最小长度

	// 更新摄像机位置
	camera->setPosition3D(currentPosition);
}

void MainGameScene::KeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	// 处理不同的按键
	if (keyCode == EventKeyboard::KeyCode::KEY_M) {
		KeyPressedForRevealMicroMap(keyCode, event);
	}
	if (!_cameraManager->IsInMicroMap()) {
		if (keyCode == EventKeyboard::KeyCode::KEY_B) {
			KeyPressedForBag(keyCode, event);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_W ||
			keyCode == EventKeyboard::KeyCode::KEY_A ||
			keyCode == EventKeyboard::KeyCode::KEY_S ||
			keyCode == EventKeyboard::KeyCode::KEY_D) {
			KeyPressedForPlayerMove(keyCode, event);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_I ||
			keyCode == EventKeyboard::KeyCode::KEY_J ||
			keyCode == EventKeyboard::KeyCode::KEY_K ||
			keyCode == EventKeyboard::KeyCode::KEY_L) {
			KeyPressedForPlayerAttack(keyCode, event);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_C) {
			KeyPressedForNPCInteract(keyCode, event);
		}
	}
	else {
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			KeyPressedForMicroMapMove(keyCode, event, _cameraManager->GetMicroCamera(), 2400.0f, -2400.0f, 2400.0f, -2400.0f, 400.0f);
		}
	}
}

void MainGameScene::KeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	// 控制玩家移动
	if (keyCode == EventKeyboard::KeyCode::KEY_W ||
		keyCode == EventKeyboard::KeyCode::KEY_A ||
		keyCode == EventKeyboard::KeyCode::KEY_S ||
		keyCode == EventKeyboard::KeyCode::KEY_D) {
		KeyReleasedForPlayerMove(keyCode, event);
	}
}

void MainGameScene::MouseScrollForCameraZoom(EventMouse* event, Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed) {
	Vec3 cameraPosition = camera->getPosition3D();
	float ScrollY = event->getScrollY();

	//通过滚轮输入，调整摄像机高度
	cameraPosition.z += ScrollY * ScrollSpeed;

	// 限制 Z 值范围
	cameraPosition.z = std::min(cameraPosition.z, MaxHeight); // 最大高度
	cameraPosition.z = std::max(cameraPosition.z, MinHeight); // 最小高度
	camera->setPosition3D(cameraPosition);
}

void MainGameScene::MouseClickedForTeleport(EventMouse* event) {
	// 处理小地图中的传送门

	int MapID = _mapManager->GetPlayerInWhichMap();
			// 传送玩家
			TeleportPlayer(MapID);

}

void MainGameScene::MouseScroll(EventMouse* event) {
	if (_cameraManager->IsInMicroMap()) {
		MouseScrollForCameraZoom(event, _cameraManager->GetMicroCamera(), 3600.0f, 1200.0f, 400.0f);
	}
	else {
		MouseScrollForCameraZoom(event, _cameraManager->GetMainCamera(), 600.0f, 200.0f, 40.0f);
	}
}

void MainGameScene::MouseClicked(EventMouse* event) {
	if (_cameraManager->IsInMicroMap()) {
		MouseClickedForTeleport(event);
	}
}