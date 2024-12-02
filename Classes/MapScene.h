
#ifndef __MapScene_H__
#define __MapScene_H__

#include "cocos2d.h"

USING_NS_CC;
class MapScene : public Scene {
public:
    static Scene* createScene() {
        return MapScene::create();
    }

    virtual bool init() override {
        // 加载 TMX 文件
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

  
        // 加载 TMX 文件
        auto tileMap = TMXTiledMap::create("D:/cocos2d-x-4.0/project/Zelda/Resources/Maps/RebirthTemple/RebirthTemple.tmx");
        tileMap->setAnchorPoint(Vec2(0.5, 0.5));
        tileMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        tileMap->setRotation3D(Vec3(-30, 0, 0));
        tileMap->setScale(1.0f);

        // 将地图添加到场景中
        this->addChild(tileMap);

        // 可以在这里做一些额外的设置，例如添加背景音乐、UI 控件等
        
        return true;
    }
    CREATE_FUNC(MapScene);
};
#endif // __MapScene_H__