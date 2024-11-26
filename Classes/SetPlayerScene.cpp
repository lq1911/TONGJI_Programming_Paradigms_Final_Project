#include "SetPlayerScene.h"


USING_NS_CC;

Scene* SetPlayerScene::createScene() {
    return SetPlayerScene::create();
}

bool SetPlayerScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // ¾ßÌåÂß¼­´ıÌí¼Ó
    auto label = Label::createWithTTF("Welcome to Game Scene", "fonts/Marker Felt.ttf", 24);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(label);

    return true;
}
