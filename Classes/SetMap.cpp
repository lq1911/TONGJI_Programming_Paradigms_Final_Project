#include "SetMap.h"
#include "Player.h"
#include "SetPlayerScene.h"

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

    // 加载 TMX 文件
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*加载初始地图*/
    auto InitialMap = TMXTiledMap::create("Maps/RebirthTemple/RebirthTemple.tmx");
    InitialMap->setAnchorPoint(Vec2(0.5, 0.5));
    InitialMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    InitialMap->setScale(1.0f);

    //添加初始地图至场景
    this->addChild(InitialMap);

    ///////////////////////
    // lq加的调试小人
    
    PLAYER = new Player("Player"+std::to_string(SetPlayerScene::who+1), this, visibleSize.width / 2, visibleSize.height / 2, 1.0f, 100, 50, 20, 50, 10, 50, 1);
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(SetMap::KeyPressed, this); 
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    // 加个npc
    npc1 = new Player("npc1", this, 600, 300, 1.0f, 0, 0, 0, 0, 0, 50, 0);
    //加个树妖
    Monster1 = new Player("Monster1", this, 1000, 600, 1.0f, 0, 0, 0, 100, 0, 50, 0);
    //加个哥布林
    Monster2 = new Player("Monster2", this, 1500, 800, 3.0f, 0, 0, 0, 100, 0, 50, 0);
    ///////////////////////


    return true;
}



void SetMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        // 切换小地图显示状态
        IsMicroMapVisible = !IsMicroMapVisible;

        /*此处切换小地图显示，进入小地图时首先隐藏初始地图，退出小地图之后再显示初始地图
          让玩家在进入小地图之前就暂停游戏，退出小地图之后再恢复游戏，防止玩家在打开地图的时候发生意外*/
        if (IsMicroMapVisible) {
            //进入小地图暂停游戏
            Director::getInstance()->pause();
            MicroMap->setVisible(IsMicroMapVisible);    //切换显示小地图
        }   
        else {
			MicroMap->setVisible(IsMicroMapVisible);    //切换显示小地图
			Director::getInstance()->resume();    //退出小地图恢复游戏
		}
    }
}