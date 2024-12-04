#include "CameraFollowScene.h"

Scene* CameraFollowScene::createScene() {
    return CameraFollowScene::create();
}

bool CameraFollowScene::init(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 1. 加载地图
    TMXTiledMap* tileMap = TMXTiledMap::create("Maps/RebirthTemple/RebirthTemple.tmx");
    Size mapSize = tileMap->getContentSize(); // 获取地图大小

    // 2. 将地图添加到场景中
    tileMap->setAnchorPoint(Vec2(0.5, 0.5));
    tileMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));  // 将地图放在屏幕中央
    this->addChild(tileMap);

    

    // 3. 创建玩家精灵
    Sprite* player = Sprite::create("pama.png");
    player->setScale(0.1);
    player->setAnchorPoint(Vec2(0.5, 0.5));
    player->setPosition(Vec2(450, 620));  // 将玩家放在屏幕中央
    this->addChild(player);

    
    // 4. 获取默认摄像机
    Camera* camera = getDefaultCamera();


    // 5. 设置摄像机的初始位置
    Vec3 cameraPosition(player->getPosition().x, player->getPosition().y, 200);
    camera->setPosition3D(cameraPosition);
    camera->lookAt(Vec3(player->getPosition().x, player->getPosition().y, 0));/**/

    
    
    // 6. 在每一帧更新时更新摄像机位置并限制其范围（待解决）
    /*schedule([=](float dt) {
        // 获取玩家的当前位置
        Vec3 playerPos = player->getPosition3D();

        // 计算摄像机的新位置
        float cameraX = std::min(std::max(playerPos.x, Director::getInstance()->getVisibleSize().width / 2),
            mapSize.width - Director::getInstance()->getVisibleSize().width / 2);
        float cameraY = std::min(std::max(playerPos.y, Director::getInstance()->getVisibleSize().height / 2),
            mapSize.height - Director::getInstance()->getVisibleSize().height / 2);

        // 更新摄像机位置
        camera->setPosition3D(Vec3(cameraX, cameraY, cameraPosition.z));

       // 让摄像机始终看向玩家
         camera->lookAt(Vec3(playerPos.x, playerPos.y, 0));
        }, "camera_update_key");*/
    return true;
}