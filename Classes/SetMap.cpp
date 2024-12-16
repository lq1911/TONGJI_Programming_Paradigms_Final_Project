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

    PlayerInWhichMap = 0;     //初始化玩家位置在初始神庙

	/*
    //创建并添加小地图至地图场景
    MicroMap = MicroMap::create();
    MicroMap->setVisible(false);    //初始隐藏小地图
    MicroMap->setScale(1.0f);    //设置小地图缩放比例
    this->addChild(MicroMap, 100);     //添加小地图至场景,小地图的图层优先级最高
	*/

    IsMicroMapVisible = false;    //初始化小地图状态变量

    //添加键盘监听器，按下M打开小地图
    auto KeyListener = EventListenerKeyboard::create();
    KeyListener->onKeyPressed = CC_CALLBACK_2(SetMap::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(KeyListener, this);

	//获取屏幕尺寸
	visibleSize = Director::getInstance()->getVisibleSize();

    /*初始化主地图摄像机和小地图摄像机*/
	this->InitalCamera();

    /*加载初始地图*/
    this->LoadMap();
  
    ///////////////////////
    // 键盘监听
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(SetMap::KeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(SetMap::KeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // lq加的调试小人
    PLAYER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, visibleSize.width / 2, visibleSize.height / 2, 0.5f, 100, 50, 20, 50, 10, 80, 1);

	// lq加的调试小人
	PLAYER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, visibleSize.width / 2, visibleSize.height / 2, 0.5f, 100, 50, 20, 50, 10, 500, 1);

	// 加个npc
	npc1 = new NPC("npc1", visibleSize.width / 2, visibleSize.height / 2 - 200, 1.0f, this, PLAYER);

	Bonus b;
	// 加个树妖
	Monster1 = new Monster("Monster1", 100000, 600, 20, 20, 20, 100, 2, 50, 100, 0, b, PLAYER, 1000, 1, this);
	this->addChild(Monster1);
	// 加个Monster2
	Monster2 = new Monster("Monster2", 100000, 600, 20, 20, 20, 100, 2, 1000, 100, 0, b, PLAYER, 1000, 1, this);
	this->addChild(Monster2);
	// 背包
	BagManager* bagManager = BagManager::getInstance();
	if (bagManager->getParent() == nullptr)
		this->addChild(bagManager);
	///////////////////////

	this->MainCameraFollowPlayer();    //注册主地图摄像机跟随玩家的函数

    return true;
}

void SetMap::InitalCamera() {
	//创建主地图摄像机
	camera = getDefaultCamera();

	//创建小地图摄像机
	camera_in_micro_map = Camera::createPerspective(60.0f,visibleSize.width / visibleSize.height, 100.0f, 4000.0f);
	
	// 将小地图摄像机添加至场景
	camera_in_micro_map->setVisible(false);    //初始隐藏小地图摄像机
	this->addChild(camera_in_micro_map);
}

EventListenerMouse* SetMap::createMouseListener(Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed) {
	auto listener = EventListenerMouse::create();
	listener->onMouseMove = [=](EventMouse* event) {
		float ScrollY = event->getScrollY();
		Vec3 cameraPosition = camera->getPosition3D();

		//通过滚轮输入，调整摄像机高度
		cameraPosition.z += ScrollY * ScrollSpeed;

		// 限制 Z 值范围
		cameraPosition.z = std::min(cameraPosition.z, MaxHeight); // 最大高度
		cameraPosition.z = std::max(cameraPosition.z, MinHeight); // 最小高度

		camera->setPosition3D(cameraPosition);
		CCLOG("cameraPosition.z = %f", cameraPosition.z);
		};
	return listener;
}

void SetMap::UpdateCameraPosition(Camera* camera, Vec2& TargetPos, float Height) {
	camera->setPosition3D(Vec3(TargetPos.x, TargetPos.y, Height));
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
	mainMapListener = createMouseListener(camera, 600.0f, 200.0f, ScrollSpeed);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mainMapListener, camera);    // 获取事件调度器并添加监听器

	// 设置主摄像机的实时跟随任务
	schedule([=](float dt) {
		float updatedCameraZ = camera->getPosition3D().z;    //获取摄像机的高度
		Vec2 playerPosition = PLAYER->mySprite->getPosition();    //获取玩家位置
		this->UpdateCameraPosition(camera, playerPosition, updatedCameraZ);    //更新摄像机位置
		}, "camera_update_key");
}

void SetMap::MicroCameraFollowPlayer() {
	// 设置摄像机的初始位置
	float InitCameraZinMicroMap = 2000.0f;

	// 每次进入小地图时，将小摄像机的位置设置中心位置
	Vec2 centerPosition(1200, 1200);
	UpdateCameraPosition(camera_in_micro_map, centerPosition, InitCameraZinMicroMap);

	// 则创建并绑定小地图监听器
	microMapListener = createMouseListener(camera_in_micro_map, 3000.0f, 1200.0f, ScrollSpeed);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(microMapListener, camera_in_micro_map);    	// 获取事件调度器并添加监听器
}

void SetMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        // 切换小地图显示状态
        IsMicroMapVisible = !IsMicroMapVisible;
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
}

void SetMap::InitialObstacle(cocos2d::TMXTiledMap* tileMap) {
    TMXObjectGroup* objectLayer = tileMap->getObjectGroup("Obstacles");    //获取障碍物组
    if (objectLayer) {
        //遍历障碍物组，获取障碍物的位置信息
        auto obstacles = objectLayer->getObjects();

        for (const auto& obj : obstacles) {
            ValueMap obstacle = obj.asValueMap();

            // 根据对象类型读取其属性
            // 障碍物全为矩形
            float x = obstacle["x"].asFloat();
            float y = obstacle["y"].asFloat();
            float width = obstacle["width"].asFloat();
            float height = obstacle["height"].asFloat();

            // 创建矩形区域
            Rect obstacleRect(x, y, width, height);

            // 这里可以存储或使用这个区域来进行碰撞检测
            // 比如添加到一个障碍物列表中
            ObstacleList.push_back(obstacleRect);
        }
    }
}

bool SetMap::IsMoveable(cocos2d::Vec2& pos) {
    for (const auto& obstacle : ObstacleList) {
        if (obstacle.containsPoint(pos))     //判断是否与障碍物发生碰撞
        {
            CCLOG("Can't move to this position");
            return false;
        }
    }
    CCLOG("Can move to this position");
    return true;
}

void SetMap::LoadMap() {
    /*****************************************在这里对各个地图进行加载处理********************************************/
    // 加载初始地图
    auto RebirthTemple = TMXTiledMap::create("Maps/RebirthTemple/RebirthTemple.tmx");
    float RebirthTempleWidth = RebirthTemple->getTileSize().width * RebirthTemple->getMapSize().width;
    float RebirthTempleHeight = RebirthTemple->getTileSize().height * RebirthTemple->getMapSize().height;
    CCLOG("RebirthTempleWidth:  %f RebirthTempleHeight: %f",RebirthTempleWidth, RebirthTempleHeight);
    RebirthTemple->setAnchorPoint(Vec2(0.5f, 0.5f));    ////设置地图锚点为中心
    //InitialObstacle(RebirthTemple);    //初始化障碍物

    // 加载火山地图
    auto Volcano = TMXTiledMap::create("Maps/volcano/volcano.tmx");
    //InitialObstacle(Volcano);    //初始化障碍物

    // 加载雪地地图
    auto SnowyWinter= TMXTiledMap::create("Maps/SnowyWinter/SnowyWinter.tmx");
    //InitialObstacle(SnowyWinter);    //初始化障碍物

    // 加载沙漠地图
    auto DeathDesert = TMXTiledMap::create("Maps/DeathDesert/DeathDesert.tmx");
    //InitialObstacle(DeathDesert);    //初始化障碍物

    // 加载森林地图
    auto BrightForest = TMXTiledMap::create("Maps/BrightForest/BrightForest.tmx");
    //InitialObstacle(BrightForest);    //初始化障碍物

    //加载火山雪地边界
    auto Vol_Snow= TMXTiledMap::create("Maps/Vol_Snow_Ecotonal/Vol_Snow_Ecotonal.tmx");
    //InitialObstacle(Vol_Snow);    //初始化障碍物

    //加载火山森林边界
    auto Vol_Forest= TMXTiledMap::create("Maps/Vol_Forest_Ecotonal/Vol_Forest_Ecotonal.tmx");
    //InitialObstacle(Vol_Forest);    //初始化障碍物

    //加载森林雪地边界
    auto Desert_Snow= TMXTiledMap::create("Maps/Desert_Snow_Ecotonal/Desert_Snow_Ecotonal.tmx");
    //InitialObstacle(Forest_Snow);    //初始化障碍物

    //加载森林沙漠边界
    auto Forest_Desert= TMXTiledMap::create("Maps/Forest_Desert_Ecotonal/Forest_Desert_Ecotonal.tmx");
    //InitialObstacle(Forest_Desert);    //初始化障碍物

    /************************************开始对各个地图进行显示处理******************************************/
    //初始化初始地图位置
	RebirthTemple->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	RebirthTemple->setScale(1.0f);
	RebirthTemple->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(RebirthTemple);

	//设置火山地图为初始地图左上角
	Volcano->setPosition(Vec2(visibleSize.width / 2 - RebirthTempleWidth - Derivation, visibleSize.height / 2 + RebirthTempleHeight + Derivation));
	Volcano->setScale(1.0f);
	Volcano->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(Volcano);

	//设置雪地为初始地图右上角
	SnowyWinter->setPosition(Vec2(visibleSize.width / 2 + RebirthTempleWidth + Derivation, visibleSize.height / 2 + RebirthTempleHeight + Derivation));
	SnowyWinter->setScale(1.0f);
	SnowyWinter->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(SnowyWinter);

	//设置死亡沙漠为初始地图右下角
	DeathDesert->setPosition(Vec2(visibleSize.width / 2 + RebirthTempleWidth + Derivation, visibleSize.height / 2 - RebirthTempleHeight - Derivation));
	DeathDesert->setScale(1.0f);
	DeathDesert->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(DeathDesert);

	//设置明亮森林为初始地图左下角
	BrightForest->setPosition(Vec2(visibleSize.width / 2 - RebirthTempleWidth - Derivation, visibleSize.height / 2 - RebirthTempleHeight - Derivation));
	BrightForest->setScale(1.0f);
	BrightForest->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(BrightForest);


	/********************************设置分界地图的位置**************************************/
	//设置火山雪地边界
	Vol_Snow->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + RebirthTempleHeight + Derivation));
	Vol_Snow->setScale(1.0f);
	Vol_Snow->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(Vol_Snow);

	//设置火山森林边界
    Vol_Forest->setPosition(Vec2(visibleSize.width / 2 - RebirthTempleWidth - Derivation, visibleSize.height / 2));
	Vol_Forest->setScale(1.0f);
	Vol_Forest->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(Vol_Forest);

	//设置森林雪地边界,看上去是森林雪地实则是沙漠和雪地
	Desert_Snow->setPosition(Vec2(visibleSize.width / 2 + RebirthTempleWidth + Derivation, visibleSize.height / 2));
	Desert_Snow->setScale(1.0f);
	Desert_Snow->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(Desert_Snow);

	//设置森林沙漠边界
	Forest_Desert->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - RebirthTempleHeight - Derivation));
	Forest_Desert->setScale(1.0f);
	Forest_Desert->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(Forest_Desert);
}

void SetMap::KeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	Vec2 moveBy;
	int speed = 30;
	/* 攻击:I/K/J/L */
	if (keyCode == EventKeyboard::KeyCode::KEY_I)
		PLAYER->Attack(UP);
	else if (keyCode == EventKeyboard::KeyCode::KEY_K)
		PLAYER->Attack(DOWN);
	else if (keyCode == EventKeyboard::KeyCode::KEY_J)
		PLAYER->Attack(LEFT);
	else if (keyCode == EventKeyboard::KeyCode::KEY_L)
		PLAYER->Attack(RIGHT);
	/* 移动:W/S/A/D */
	else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		moveBy = Vec2(0, speed);
		Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
		if (IsMoveable(targetPosition)) {
			if (!isKeyPressed[0]) {
				isKeyPressed[0] = true;
				PLAYER->Move(UP);
				this->schedule([&](float dt) {
					PLAYER->Move(UP);
					}, 0.8f, "MoveUP");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		moveBy = Vec2(0, -speed);
		Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
		if (IsMoveable(targetPosition)) {
			if (!isKeyPressed[1]) {
				isKeyPressed[1] = true;
				PLAYER->Move(DOWN);
				this->schedule([&](float dt) {
					PLAYER->Move(DOWN);
					}, 0.8f, "MoveDOWN");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		moveBy = Vec2(-speed, 0);
		Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
		if (IsMoveable(targetPosition)) {
			if (!isKeyPressed[2]) {
				isKeyPressed[2] = true;
				PLAYER->Move(LEFT);
				this->schedule([&](float dt) {
					PLAYER->Move(LEFT);
					}, 0.8f, "MoveLEFT");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		moveBy = Vec2(speed, 0);
		Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
		if (IsMoveable(targetPosition)) {
			if (!isKeyPressed[3]) {
				isKeyPressed[3] = true;
				PLAYER->Move(RIGHT);
				this->schedule([&](float dt) {
					PLAYER->Move(RIGHT);
					}, 0.8f, "MoveRIGHT");
			}
		}
	}

	// 测试Monster1攻击效果用，记得删
	else if (keyCode == EventKeyboard::KeyCode::KEY_T) {
		int dx = Monster1->mySprite->getPosition().x - PLAYER->mySprite->getPosition().x;
		int dy = Monster1->mySprite->getPosition().y - PLAYER->mySprite->getPosition().y;
		if (std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(Monster1->getAtkRange(), 2))
			Monster1->Attack();
		else
			Monster1->Attack();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_Y) {
		npc1->Chat();
		//Monster2->Attack(UP);
		//PLAYER->Heal();
		//PLAYER->Die();
	}
	/* B/P:背包 */
	else if (keyCode == EventKeyboard::KeyCode::KEY_B) {

		if (BagManager::getInstance()->isBagVisible())
			// 隐藏背包
			BagManager::getInstance()->hideBag(*PLAYER);
		else
			// 打开背包
			BagManager::getInstance()->showBag(*PLAYER);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_P) {
		goods _goods;
		if (BagManager::getInstance()->getItemsNum() % 5 == 0)
		{
			weapon* it1 = new weapon(_goods.icon_sword);
			BagManager::getInstance()->addItem(it1);
			return;
		}
		if (BagManager::getInstance()->getItemsNum() % 5 == 1)
		{
			consumable* it2 = new consumable(_goods.pumkin);
			BagManager::getInstance()->addItem(it2);
			return;
		}
		if (BagManager::getInstance()->getItemsNum() % 5 == 2)
		{
			accessories* it3 = new accessories(_goods.bomb);
			BagManager::getInstance()->addItem(it3);
			return;
		}
		if (BagManager::getInstance()->getItemsNum() % 5 == 3)
		{
			armor* it4 = new armor(_goods.icon_conselet);
			BagManager::getInstance()->addItem(it4);
			return;
		}
		if (BagManager::getInstance()->getItemsNum() % 5 == 4)
		{
			shoes* it5 = new shoes(_goods.boots);
			BagManager::getInstance()->addItem(it5);
			return;
		}
	}
}

void SetMap::KeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		if (isKeyPressed[0]) {
			isKeyPressed[0] = false;
			this->unschedule("MoveUP");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		if (isKeyPressed[1]) {
			isKeyPressed[1] = false;
			this->unschedule("MoveDOWN");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		if (isKeyPressed[2]) {
			isKeyPressed[2] = false;
			this->unschedule("MoveLEFT");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		if (isKeyPressed[3]) {
			isKeyPressed[3] = false;
			this->unschedule("MoveRIGHT");
		}
	}
}