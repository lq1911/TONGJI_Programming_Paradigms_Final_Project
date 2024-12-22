#include <iostream>
#include "ui/CocosGUI.h"
#include "SetPlayerScene.h"
#include "Player.h"
#include "LoadingScene.h"


USING_NS_CC;
// 定义静态成员变量
int SetPlayerScene::who = 0;  // 给静态成员变量初始化

Scene* SetPlayerScene::createScene() {
    return SetPlayerScene::create();
}

/* 初始化:输入玩家姓名 */
bool SetPlayerScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    // 预先定义
    auto visibleSize = Director::getInstance()->getVisibleSize();

    /* 加载背景图 */
    auto background = Sprite::create("Scene/SelectRoleScene.png");
    if (background) {
        background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        background->setScale(visibleSize.width / background->getContentSize().width,
            visibleSize.height / background->getContentSize().height);
        this->addChild(background, -10);
    }

    /* 文字提示选择角色 */
    auto ChooseRoleTxt = Label::createWithTTF("Choose your role!", "fonts/Lacquer.ttf", 130);
    ChooseRoleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 300));
    ChooseRoleTxt->setTextColor(Color4B(211, 211, 211, 245));
    this->addChild(ChooseRoleTxt, 0);

    /* 选择角色 */
    // Player1按钮
    auto P1Button = ui::Button::create("UI/Border1.png", "UI/Border1Clicked.png");
    P1Button->ignoreContentAdaptWithSize(false);
    P1Button->setContentSize(Size(300, 300));
    P1Button->setPosition(Vec2((visibleSize.width / 6) * 1, visibleSize.height / 2));
    this->addChild(P1Button, 0);
    // Player1图像
    auto P1Sprite = Sprite::create("Role/Player1/1.png");
    P1Sprite->setPosition(Vec2((visibleSize.width / 6) * 1, visibleSize.height / 2 + 30));
    P1Sprite->setScale(1.2f);
    this->addChild(P1Sprite);
    // Player2按钮
    auto P2Button = ui::Button::create("UI/Border1.png", "UI/Border1Clicked.png");
    P2Button->ignoreContentAdaptWithSize(false);
    P2Button->setContentSize(Size(300, 300));
    P2Button->setPosition(Vec2((visibleSize.width / 6) * 2, visibleSize.height / 2));
    this->addChild(P2Button, 0);
    // Player2图像
    auto P2Sprite = Sprite::create("Role/Player2/1.png");
    P2Sprite->setPosition(Vec2((visibleSize.width / 6) * 2, visibleSize.height / 2 + 30));
    P2Sprite->setScale(1.2f);
    this->addChild(P2Sprite);
    // Player3按钮
    auto P3Button = ui::Button::create("UI/Border1.png", "UI/Border1Clicked.png");
    P3Button->ignoreContentAdaptWithSize(false);
    P3Button->setContentSize(Size(300, 300));
    P3Button->setPosition(Vec2((visibleSize.width / 6) * 3, visibleSize.height / 2));
    this->addChild(P3Button, 0);
    // Player3图像
    auto P3Sprite = Sprite::create("Role/Player3/1.png");
    P3Sprite->setPosition(Vec2((visibleSize.width / 6) * 3, visibleSize.height / 2 + 30));
    P3Sprite->setScale(1.2f);
    this->addChild(P3Sprite);
    // Player4按钮
    auto P4Button = ui::Button::create("UI/Border1.png", "UI/Border1Clicked.png");
    P4Button->ignoreContentAdaptWithSize(false);
    P4Button->setContentSize(Size(300, 300));
    P4Button->setPosition(Vec2((visibleSize.width / 6) * 4, visibleSize.height / 2));
    this->addChild(P4Button, 0);
    // Player4图像
    auto P4Sprite = Sprite::create("Role/Player4/1.png");
    P4Sprite->setPosition(Vec2((visibleSize.width / 6) * 4, visibleSize.height / 2 + 30));
    P4Sprite->setScale(1.2f);
    this->addChild(P4Sprite);
    // Player5按钮
    auto P5Button = ui::Button::create("UI/Border1.png", "UI/Border1Clicked.png");
    P5Button->ignoreContentAdaptWithSize(false);
    P5Button->setContentSize(Size(300, 300));
    P5Button->setPosition(Vec2((visibleSize.width / 6) * 5, visibleSize.height / 2));
    this->addChild(P5Button, 0);
    // Player5图像
    auto P5Sprite = Sprite::create("Role/Player5/1.png");
    P5Sprite->setPosition(Vec2((visibleSize.width / 6) * 5, visibleSize.height / 2 + 30));
    P5Sprite->setScale(1.2f);
    this->addChild(P5Sprite);

    /* 跳转 */
    P1Button->addClickEventListener([=](Ref* sender) mutable {
        CCLOG("Choose Player1");
        who = Player1;
        auto scene = LoadingScene::createScene(0);
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B::BLACK));
        });
    P2Button->addClickEventListener([=](Ref* sender) mutable {
        CCLOG("Choose Player2");
        who = Player2;
        auto scene = LoadingScene::createScene(0);
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B::BLACK));
        });
    P3Button->addClickEventListener([=](Ref* sender) mutable {
        CCLOG("Choose Player3");
        who = Player3;
        auto scene = LoadingScene::createScene(0);
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B::BLACK));
        });
    P4Button->addClickEventListener([=](Ref* sender) mutable {
        CCLOG("Choose Player4");
        who = Player4;
        auto scene = LoadingScene::createScene(0);
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B::BLACK));
        });
    P5Button->addClickEventListener([=](Ref* sender) mutable {
        CCLOG("Choose Player5");
        who = Player5;
        auto scene = LoadingScene::createScene(0);
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B::BLACK));
        });

    return true;
}