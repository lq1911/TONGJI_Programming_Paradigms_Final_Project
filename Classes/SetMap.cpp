#include "SetMap.h"

#define Derivation 243

USING_NS_CC;

Scene* SetMap::createScene() {
    return SetMap::create();
}

bool SetMap::init() {
    if (!Scene::init()) {
        return false;
    }

    IsMicroMapVisible = false;    //初始化小地图状态变量

    //添加键盘监听器，按下M打开小地图
    auto KeyListener = EventListenerKeyboard::create();
    KeyListener->onKeyPressed = CC_CALLBACK_2(SetMap::KeyPressedForMicroMap, this);
	KeyListener->onKeyReleased = CC_CALLBACK_2(SetMap::KeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(KeyListener, this);

	//获取屏幕尺寸
	visibleSize = Director::getInstance()->getVisibleSize();

    /*初始化主地图摄像机和小地图摄像机*/
	this->InitialCamera();

	// lq加的调试小人
	PLAYER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, visibleSize.width / 2, visibleSize.height / 2, 0.5f, 100, 50, 20, 50, 10, 192, 1);
	// 加怪
	monster_respawn = new MonsterRespawn(PLAYER, this);
	// 将怪导入角色
	PLAYER->InitMonster(monster_respawn->GetMonster());

	// 加个npc
	npc1 = new NPC("npc1", visibleSize.width / 2, visibleSize.height / 2 - 200, 1.0f, this, PLAYER);
	
	// 背包
	BagManager* bagManager = BagManager::getInstance();
	if (bagManager->getParent() == nullptr)
		this->addChild(bagManager);
	///////////////////////

	this->MainCameraFollowPlayer();    //注册主地图摄像机跟随玩家的函数

    return true;
}

void SetMap::createKeyboardListenerForCamera(Camera* camera, float MaxWidth, float MinWidth, float MaxHeigth, float MinHeigth, float moveSpeed) {
	auto keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		Vec3 currentPosition = camera->getPosition3D();

		// 根据WASD控制摄像机的平移
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			currentPosition.y += moveSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			currentPosition.y -= moveSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			currentPosition.x -= moveSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			currentPosition.x += moveSpeed;
			break;
		default:
			break;
		}

		// 限制摄像机的移动边界（防止越界）
		currentPosition.x = std::min(currentPosition.x, MaxWidth);    // 限制最大宽度
		currentPosition.x = std::max(currentPosition.x, MinWidth);    // 限制最小宽度

		currentPosition.y = std::min(currentPosition.y, MaxHeigth);    // 限制最大长度
		currentPosition.y = std::max(currentPosition.y, MinHeigth);     // 限制最小长度

		// 更新摄像机位置
		camera->setPosition3D(currentPosition);
		};

	// 将监听器添加到事件调度器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

EventListenerMouse* SetMap::createMouseListenerForCameraScroll(Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed) {
	auto listener = EventListenerMouse::create();
	listener->onMouseScroll = [=](EventMouse* event) {
		Vec3 cameraPosition = camera->getPosition3D();
		float ScrollY = event->getScrollY();

		//通过滚轮输入，调整摄像机高度
		cameraPosition.z += ScrollY * ScrollSpeed;
        
		// 限制 Z 值范围
		cameraPosition.z = std::min(cameraPosition.z, MaxHeight); // 最大高度
		cameraPosition.z = std::max(cameraPosition.z, MinHeight); // 最小高度
		camera->setPosition3D(cameraPosition);
		};
	return listener;
}

void SetMap::CameraFollowController() {
	// 清除现有监听器
	if (mainMapListener) {
		_eventDispatcher->removeEventListener(mainMapListener);
		mainMapListener = nullptr;
	}
	if (microMapListener) {
		_eventDispatcher->removeEventListener(microMapListener);
		microMapListener = nullptr;
	}

	if (IsMicroMapVisible) {
		this->MicroCameraFollowPlayer();    //注册小地图摄像机跟随玩家的函数
	}
	else {
		this->MainCameraFollowPlayer();    //注册主地图摄像机跟随玩家的函数
	}
}

void SetMap::MainCameraFollowPlayer() {
	// 设置摄像机的初始位置
	float InitCameraZinMainMap = 600.0f;

	//每次进入主地图时，将主摄像机的位置设置为玩家位置
	Vec2 playPosition = PLAYER->mySprite->getPosition();
	UpdateCameraPosition(camera, playPosition, InitCameraZinMainMap);
	// 则创建并绑定主地图监听器
	mainMapListener = createMouseListenerForCameraScroll(camera, 600.0f, 200.0f, ScrollSpeed);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mainMapListener, this);    // 获取事件调度器并添加监听器

	// 设置主摄像机的实时跟随任务
	schedule([=](float dt) {
		float updatedCameraZ = camera->getPosition3D().z;    //获取摄像机的高度
		Vec2 playerPosition = PLAYER->mySprite->getPosition();    //获取玩家位置
		this->UpdateCameraPosition(camera, playerPosition, updatedCameraZ);    //更新摄像机位置
		}, "camera_update_key");
}

//点击屏幕所得坐标转换测试======================================================================================================
void SetMap::onMouseUp(cocos2d::EventMouse* event) {

	// 鼠标点击事件
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	// 获取测试鼠标点击位置
	cocos2d::Vec2 TestclickPos = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
	// 获取鼠标点击位置（窗口坐标系）
	cocos2d::Vec2 clickPos = mouseEvent->getLocation();
	// 获取玩家位置（场景坐标系）
	Vec2 playerPosition = PLAYER->mySprite->getPosition();
	// 获得玩家位置（世界坐标系）
	Vec2 playerPositionInWorld = convertToWorldSpace(playerPosition);
	// 获得玩家位置（窗口坐标系）
	Vec2 playerPositionInWindow = convertToWindowSpace(playerPositionInWorld);
	// 将鼠标点击位置转换为场景坐标系
	//Vec2 clickPosInScene = this->camera->convertToNodeSpace(TestclickPos);
	CCLOG("TestMouse click position (window coordinates): (%f, %f)", TestclickPos.x, TestclickPos.y);
	CCLOG("Mouse click position (window coordinates): (%f, %f)", clickPos.x, clickPos.y);
	CCLOG("Player position (scene coordinates): (%f, %f)", playerPosition.x, playerPosition.y);
	CCLOG("Player position (window coordinates): (%f, %f)", playerPositionInWindow.x, playerPositionInWindow.y);
	//CCLOG("Mouse click position (scene coordinates): (%f, %f)", clickPosInScene.x, clickPosInScene.y);
	CCLOG("Player position (world coordinates): (%f, %f)", playerPositionInWorld.x, playerPositionInWorld.y);

}
//=======================================================================================================

void SetMap::MicroCameraFollowPlayer() {
	// 设置摄像机的初始位置
	float InitCameraZinMicroMap = 2000.0f;

	// 每次进入小地图时，将小摄像机的位置设置中心位置
	Vec2 centerPosition(1200, 1200);
	UpdateCameraPosition(camera_in_micro_map, centerPosition, InitCameraZinMicroMap);

	// 则创建并绑定小地图监听器
	microMapListener = createMouseListenerForCameraScroll(camera_in_micro_map, 3600.0f, 1200.0f, ScrollSpeed );
	_eventDispatcher->addEventListenerWithSceneGraphPriority(microMapListener, camera_in_micro_map);    	// 获取事件调度器并添加监听器

	//==========================================================================

	// 注册鼠标点击事件
	auto listener = cocos2d::EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(SetMap::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//================================================================================

	// 设置键盘监听，控制摄像机移动
	createKeyboardListenerForCamera(camera_in_micro_map, 2400.0f, -2400.0f, 2400.0f, -2400.0f, ScrollSpeed * 10);
}

void SetMap::KeyPressedForMicroMap(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_M) {
		// 切换小地图显示状态
		IsMicroMapVisible = !IsMicroMapVisible;

		//小地图中显示黑色雾效果的判断数组反转
		for (int i = 0; i < IsBlackFogVisible.size(); i++) {
			IsBlackFogVisible[i] = !IsBlackFogVisible[i];         
		}
		// 更新小地图中黑色雾的显示
		SetBlackFogInMicroMap();

		CameraFollowController();    //注册摄像机跟随玩家的函数
		/*此处切换小地图显示，进入小地图时首先隐藏初始地图，退出小地图之后再显示初始地图
		  让玩家在进入小地图之前就暂停游戏，退出小地图之后再恢复游戏，防止玩家在打开地图的时候发生意外*/
		if (IsMicroMapVisible) {
			//进入小地图暂停游戏
			Director::getInstance()->pause();     // 暂停游戏
			camera_in_micro_map->setVisible(true);     //将小地图摄像机显示
			camera->setVisible(false);    //将初始摄像机隐藏

			// MicroMap->setVisible(IsMicroMapVisible);    //切换显示小地图
		}
		else {
			//MicroMap->setVisible(IsMicroMapVisible);    //切换显示小地图

			// 恢复主地图响应和摄像机逻辑
			camera_in_micro_map->setVisible(false);    //将小地图摄像机隐藏
			camera->setVisible(true);    //将初始摄像机显示
			Director::getInstance()->resume();    //退出小地图恢复游戏
		}
	}

	//int speed = 10;
	int speed = PLAYER->getSpeed();
	/* 攻击:I/K/J/L */
	if (keyCode == EventKeyboard::KeyCode::KEY_I) {
		PLAYER->Attack(UP, monster_respawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_K) {
		PLAYER->Attack(DOWN, monster_respawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		PLAYER->Attack(LEFT, monster_respawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_L) {
		PLAYER->Attack(RIGHT, monster_respawn->GetMonster());
	}
	/* 移动:W/S/A/D */
	else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
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
	/* npc交互 */
	else if (keyCode == EventKeyboard::KeyCode::KEY_C) {
		npc1->Chat();
	}
	/* 背包系统 */
	else if (keyCode == EventKeyboard::KeyCode::KEY_B) {
		if (BagManager::getInstance()->isBagVisible())
			// 隐藏背包
			BagManager::getInstance()->hideBag(*PLAYER);
		else
			// 打开背包
			BagManager::getInstance()->showBag(*PLAYER);
	}
}

void SetMap::HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction) {
	Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
	
	// 检查目标位置是否可移动
	if (IsMoveable(targetPosition)) {
		if (!isKeyPressed[keyIndex]) {
			log("success&&&&&&&&&&&&&&&&");
			isKeyPressed[keyIndex] = true;
			PLAYER->Move(direction);
			this->schedule([=](float dt) {
				PLAYER->Move(direction);
				}, 0.8f, scheduleKey);
		}
		//@cbx 
		/*if (BagManager::getInstance()->getItemsNum() % 5 == 4)
		{
			shoes* it5 = new shoes(_goods.boots);
			BagManager::getInstance()->addItem(it5);
			return;
		}*/
	}
}

void SetMap::KeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
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