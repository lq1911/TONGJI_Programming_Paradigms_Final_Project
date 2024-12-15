#include "SetMap.h"
#include "Player.h"
#include "SetPlayerScene.h"

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

    //创建并添加小地图至地图场景
    MicroMap = MicroMap::create();
    MicroMap->setVisible(false);    //初始隐藏小地图
    MicroMap->setScale(1.0f);    //设置小地图缩放比例
    this->addChild(MicroMap, 100);     //添加小地图至场景,小地图的图层优先级最高

    IsMicroMapVisible = false;    //初始化小地图状态变量

    //添加键盘监听器，按下M打开小地图
    auto KeyListener = EventListenerKeyboard::create();
    KeyListener->onKeyPressed = CC_CALLBACK_2(SetMap::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(KeyListener, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建小地图摄像机
	camera_in_micro_map = Camera::createOrthographic(visibleSize.width, visibleSize.height, 1.0f, 10000.0f);
	camera_in_micro_map->setVisible(false);    //初始隐藏小地图摄像机
	this->addChild(camera_in_micro_map);

    /*加载初始地图*/
    this->LoadMap();
  
    ///////////////////////
    // 键盘监听
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(SetMap::KeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(SetMap::KeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // lq加的调试小人
    PLAYER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, visibleSize.width / 2, visibleSize.height / 2, 0.5f, 100, 50, 20, 50, 10, 500, 1);

    // 加个npc
    npc1 = new NPC("npc1", visibleSize.width / 2, visibleSize.height / 2 - 200, 1.0f, this, PLAYER);
  
        Bonus b;
    // 加个树妖
    Monster1 = new Monster("Monster1",100000, 600, 20,20,20, 100, 2, 50, 100, 0, b, PLAYER,1000,1,this);
    this->addChild(Monster1);
    // 加个Monster2
    Monster2 = new Monster("Monster2", 100000, 600, 20, 20, 20, 100, 2, 1000, 100, 0, b, PLAYER, 1000, 1, this);
    this->addChild(Monster2);
    // 背包
    BagManager* bagManager = BagManager::getInstance();
    if(bagManager->getParent()==nullptr)
        this->addChild(bagManager);
    ///////////////////////

    this->CameraFollowPlayer();    //注册摄像机跟随玩家的函数

    return true;
}

void SetMap::CameraFollowPlayer() {
    // 设置摄像机的初始位置
    float cameraZ = 600;

    Vec2 playerPosition = PLAYER->mySprite->getPosition();
    Vec3 cameraPosition(playerPosition.x, playerPosition.y, cameraZ);
    camera->setPosition3D(cameraPosition);

    // 注册鼠标滚轮事件
    auto listener = EventListenerMouse::create();
    listener->onMouseScroll = [=](EventMouse* event) {
        // 获取滚轮的滚动方向
        float scrollY = event->getScrollY();

        // 获取当前摄像机的位置
        Vec3 cameraPosition = camera->getPosition3D();

        // 根据滚轮的方向改变摄像机的Z轴高度
        // 向上滚动，Z轴值增加，摄像机向前
        // 向下滚动，Z轴值减少，摄像机向后
        cameraPosition.z += scrollY * 10.0f;  // 10.0f是控制滚动灵敏度的系数，可以调整

        // 限制摄像机的高度（Z轴范围）
        cameraPosition.z = std::min(cameraPosition.z, 2000.0f);  // 最大高度
        cameraPosition.z = std::max(cameraPosition.z, 200.0f);  // 最小高度

        // 设置摄像机的位置
        camera->setPosition3D(cameraPosition);

        CCLOG("Camera Position: %f, %f, %f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
        };

    // 获取事件调度器并添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 在每一帧更新时更新摄像机位置并限制其范围
    schedule([=](float dt) {
        Vec3 cameraPosition = camera->getPosition3D();     // 获取当前摄像机的位置
        Vec2 playerPosition = PLAYER->mySprite->getPosition();    //获取玩家位置
       
        // 根据玩家位置更新摄像机的位置
        camera->setPosition3D(Vec3(playerPosition.x, playerPosition.y, cameraPosition.z));
        }, "camera_update_key");
}

void SetMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        // 切换小地图显示状态
        IsMicroMapVisible = !IsMicroMapVisible;
		
		// 设置摄像机的初始位置
		float cameraZ = 6000.0f;

		Vec3 camera_in_micro_map_Position(0, 0, cameraZ);
		camera_in_micro_map->setPosition3D(camera_in_micro_map_Position);


		auto microMapMouseListener = EventListenerMouse::create();
        /*此处切换小地图显示，进入小地图时首先隐藏初始地图，退出小地图之后再显示初始地图
          让玩家在进入小地图之前就暂停游戏，退出小地图之后再恢复游戏，防止玩家在打开地图的时候发生意外*/
        if (IsMicroMapVisible) {
            //进入小地图暂停游戏
            Director::getInstance()->pause();
			camera_in_micro_map->setVisible(true);//将小地图添加至小地图摄像机
			camera->setVisible(false);    //将初始摄像机隐藏

			// 启用小地图监听器
			if (!microMapMouseListener) {
				microMapMouseListener->onMouseScroll = [=](EventMouse* event) {
					float scrollY = event->getScrollY();
					Vec3 cameraPosition_in_micro_map = camera_in_micro_map->getPosition3D();
					cameraPosition_in_micro_map.z += scrollY * 10.0f;
					
					camera_in_micro_map->setPosition3D(cameraPosition_in_micro_map);
					CCLOG("Micro Map Camera Position: %f, %f, %f", cameraPosition_in_micro_map.x, cameraPosition_in_micro_map.y, cameraPosition_in_micro_map.z);
					};
				_eventDispatcher->addEventListenerWithSceneGraphPriority(microMapMouseListener, this);
			}
			/////////////////////////////////////////////////////

           // MicroMap->setVisible(IsMicroMapVisible);    //切换显示小地图
        }   
        else {
			//MicroMap->setVisible(IsMicroMapVisible);    //切换显示小地图

			camera_in_micro_map->setVisible(false);    //将小地图摄像机隐藏
			camera->setVisible(true);    //将小地图摄像机恢复至初始位置
			Director::getInstance()->resume();    //退出小地图恢复游戏

			_eventDispatcher->removeEventListener(microMapMouseListener);
			microMapMouseListener = nullptr;	
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
    //获取屏幕尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();

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
				this->schedule([&](float dt) {
					PLAYER->Move(UP);
					}, 0.34f, "MoveUP");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		moveBy = Vec2(0, -speed);
		Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
		if (IsMoveable(targetPosition)) {
			if (!isKeyPressed[1]) {
				isKeyPressed[1] = true;
				this->schedule([&](float dt) {
					PLAYER->Move(DOWN);
					}, 0.34f, "MoveDOWN");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		moveBy = Vec2(-speed, 0);
		Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
		if (IsMoveable(targetPosition)) {
			if (!isKeyPressed[2]) {
				isKeyPressed[2] = true;
				this->schedule([&](float dt) {
					PLAYER->Move(LEFT);
					}, 0.34f, "MoveLEFT");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		moveBy = Vec2(speed, 0);
		Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
		if (IsMoveable(targetPosition)) {
			if (!isKeyPressed[3]) {
				isKeyPressed[3] = true;
				this->schedule([&](float dt) {
					PLAYER->Move(RIGHT);
					}, 0.34f, "MoveRIGHT");
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

	// 按下B键之后的逻辑:背包
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