#include "CameraFollowScene.h"

Scene* CameraFollowScene::createScene() {
    return CameraFollowScene::create();
}

bool CameraFollowScene::init(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 加载地图
    TMXTiledMap* tileMap = TMXTiledMap::create("Maps/RebirthTemple/RebirthTemple.tmx");
    Size mapSize = tileMap->getContentSize(); // 获取地图大小

    // 将地图添加到场景中
    tileMap->setAnchorPoint(Vec2(0.5, 0.5));
    tileMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));  // 将地图放在屏幕中央
    this->addChild(tileMap);

    

    // 创建玩家精灵
    Sprite* player = Sprite::create("pama.png");
    player->setScale(0.1);
    player->setAnchorPoint(Vec2(0.5, 0.5));
    player->setPosition(Vec2(600, 620));  // 设置玩家初始位置
    this->addChild(player);

    
    // 获取默认摄像机
    Camera* camera = getDefaultCamera();


    // 设置摄像机的初始位置
    float cameraZ = 300;
    Vec3 cameraPosition(player->getPosition().x, player->getPosition().y, cameraZ);
    camera->setPosition3D(cameraPosition);
    //camera->lookAt(Vec3(player->getPosition().x, player->getPosition().y, 0));

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
        cameraPosition.z = std::min(cameraPosition.z, 600.0f);  // 最大高度
        cameraPosition.z = std::max(cameraPosition.z, 200.0f);  // 最小高度

        // 设置摄像机的位置
        camera->setPosition3D(cameraPosition);
        
        CCLOG("Camera Position: %f, %f, %f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
        };

    // 获取事件调度器并添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    // 在每一帧更新时更新摄像机位置并限制其范围
    schedule([=](float dt) {
        // 获取当前摄像机的位置
            Vec3 cameraPosition = camera->getPosition3D();
        
        // 根据玩家位置更新摄像机的位置
        camera->setPosition3D(Vec3(player->getPosition().x, player->getPosition().y, cameraPosition.z));
        }, "camera_update_key");
    return true;
}